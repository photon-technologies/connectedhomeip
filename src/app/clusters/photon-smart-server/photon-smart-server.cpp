#include "photon-smart-server.h"

#include <app-common/zap-generated/attributes/Accessors.h>
#include <app/AttributeAccessInterfaceRegistry.h>
#include <app/data-model/Nullable.h>
#include <app/reporting/reporting.h>
#include <app/util/attribute-storage.h>
#include <app/util/config.h>
#include <app/util/util.h>
#include <protocols/interaction_model/StatusCode.h>
#include <src/platform/ESP32/FctryStoreManager.h>

using namespace chip;
using namespace chip::app;
using namespace chip::app::Clusters;
using chip::Protocols::InteractionModel::Status;

namespace chip {
namespace app {
namespace Clusters {
namespace PhotonSmart {

class StorageDelegate : public DeviceLayer::PersistedStorage::FctryStoreManager
{
public:
    CHIP_ERROR Put(const char * key, const void * value, size_t value_size)
    {
        return FctryStoreManager::Put(key, value, value_size);
    }

    CHIP_ERROR Get(const char * key, void * buffer, size_t buffer_size, size_t * read_bytes_size = nullptr, size_t offset_bytes = 0)
    {
        return FctryStoreManager::Get(key, buffer, buffer_size, read_bytes_size, offset_bytes);
    }
};

static StorageDelegate storageDelegate;

Instance::Instance(EndpointId aEndpointId) :
    AttributeAccessInterface(Optional<EndpointId>(aEndpointId), Id), mEndpointId(aEndpointId)
{}

Instance::~Instance()
{
    AttributeAccessInterfaceRegistry::Instance().Unregister(this);
}

CHIP_ERROR Instance::Init()
{
    // Check if the cluster has been selected in zap
    VerifyOrDie(emberAfContainsServer(mEndpointId, Id) == true);

    // Set ShouldReboot to false on init as Init is called only after boot;
    Attributes::ShouldReboot::Set(mEndpointId, false);

    ChipLogProgress(DeviceLayer, "Init MQTT config");
    VerifyOrDie(storageDelegate.Get(MQTT_HOST_NVS_KEY, &host, sizeof(host), &host_size) == CHIP_NO_ERROR);
    ChipLogProgress(DeviceLayer, "host_size: %d == strlen(host): %d, last character %d", host_size, strlen((char *) host), host[host_size]);

    if (storageDelegate.Get(MQTT_PORT_NVS_KEY, &port, sizeof(port)) != CHIP_NO_ERROR)
    {
        storageDelegate.Put(MQTT_PORT_NVS_KEY, &port, sizeof(port));
    }

    if (storageDelegate.Get(MQTT_TRANSPORT_NVS_KEY, &transport, sizeof(transport)) != CHIP_NO_ERROR)
    {
        storageDelegate.Put(MQTT_TRANSPORT_NVS_KEY, &transport, sizeof(transport));
    }

    if (storageDelegate.Get(MQTT_KEEP_ALIVE_NVS_KEY, &keepAlive, sizeof(keepAlive)) != CHIP_NO_ERROR)
    {
        storageDelegate.Put(MQTT_KEEP_ALIVE_NVS_KEY, &keepAlive, sizeof(keepAlive));
    }
    ChipLogProgress(DeviceLayer, "lastWellTopicLen before: %d", lastWellTopicLen);
    storageDelegate.Get(MQTT_LAST_WILL_TOPIC_NVS_KEY, &lastWellTopic, sizeof(lastWellTopic), &lastWellTopicLen);
    ChipLogProgress(DeviceLayer, "lastWellTopic: %.*s", lastWellTopicLen, lastWellTopic);
    ChipLogProgress(DeviceLayer, "lastWellTopicLen: after %d == strlen(lastWellTopic): %d, last character %d", lastWellTopicLen, strlen((char *) lastWellTopic), lastWellTopic[lastWellTopicLen]);

    ChipLogProgress(DeviceLayer, "lastWellMsgLen before: %d", lastWellMsgLen);
    storageDelegate.Get(MQTT_LAST_WILL_MSG_NVS_KEY, &lastWellMsg, sizeof(lastWellMsg), &lastWellMsgLen);
    ChipLogProgress(DeviceLayer, "lastWellMsg: %.*s", lastWellMsgLen, lastWellMsg);
    ChipLogProgress(DeviceLayer, "lastWellMsgLen: after %d == strlen(lastWellMsg): %d, last character %d", lastWellMsgLen, strlen((char *) lastWellMsg), lastWellMsg[lastWellMsgLen]);


    if (storageDelegate.Get(MQTT_LAST_WILL_QOS_NVS_KEY, &lastWellQOS, sizeof(lastWellQOS)) != CHIP_NO_ERROR)
    {
        storageDelegate.Put(MQTT_LAST_WILL_QOS_NVS_KEY, &lastWellQOS, sizeof(lastWellQOS));
    }

    if (storageDelegate.Get(MQTT_LAST_WILL_RETAIN_NVS_KEY, &lastWellRetain, sizeof(lastWellRetain)) != CHIP_NO_ERROR)
    {
        storageDelegate.Put(MQTT_LAST_WILL_RETAIN_NVS_KEY, &lastWellRetain, sizeof(lastWellRetain));
    }

    if (storageDelegate.Get(MQTT_CLEAN_SESSION_NVS_KEY, &cleanSession, sizeof(cleanSession)) != CHIP_NO_ERROR)
    {
        storageDelegate.Put(MQTT_CLEAN_SESSION_NVS_KEY, &cleanSession, sizeof(cleanSession));
    }

    if (storageDelegate.Get(MQTT_RECONNECT_TIMEOUT_NVS_KEY, &reconnectTimeoutMS, sizeof(reconnectTimeoutMS)) != CHIP_NO_ERROR)
    {
        storageDelegate.Put(MQTT_RECONNECT_TIMEOUT_NVS_KEY, &reconnectTimeoutMS, sizeof(reconnectTimeoutMS));
    }

    if (storageDelegate.Get(MQTT_NETWORK_TIMEOUT_NVS_KEY, &timeoutMS, sizeof(timeoutMS)) != CHIP_NO_ERROR)
    {
        storageDelegate.Put(MQTT_NETWORK_TIMEOUT_NVS_KEY, &timeoutMS, sizeof(timeoutMS));
    }

    if (storageDelegate.Get(MQTT_REFRESH_CONNECTION_AFTER_NVS_KEY, &refreshConnectionAfterMS, sizeof(refreshConnectionAfterMS)) !=
        CHIP_NO_ERROR)
    {
        storageDelegate.Put(MQTT_REFRESH_CONNECTION_AFTER_NVS_KEY, &refreshConnectionAfterMS, sizeof(refreshConnectionAfterMS));
    }

    storageDelegate.Get(MQTT_REPLY_TO_NVS_KEY, &replyTo, sizeof(replyTo), &replyToLen);

    VerifyOrReturnError(AttributeAccessInterfaceRegistry::Instance().Register(this), CHIP_ERROR_INCORRECT_STATE);

    return CHIP_NO_ERROR;
}

bool Instance::mqttConfigHasChanged(const Structs::PhotonMQTTStruct::Type & aNewMqttConfig)
{
    bool dataHasChanged = false;
    if (aNewMqttConfig.host.size() != host_size || memcmp(aNewMqttConfig.host.data(), host, host_size) != 0)
    {
        dataHasChanged = true;
    }
    if (aNewMqttConfig.port != port)
    {
        dataHasChanged = true;
    }
    uint8_t newTransport = aNewMqttConfig.transport == MqttTransport::kWss ? 4 : 2;
    if (newTransport != transport)
    {
        dataHasChanged = true;
    }
    if (aNewMqttConfig.keepAlive != keepAlive)
    {
        dataHasChanged = true;
    }
    if (aNewMqttConfig.lastWellTopic.size() != lastWellTopicLen || memcmp(aNewMqttConfig.lastWellTopic.data(), lastWellTopic, lastWellTopicLen) != 0)
    {
        dataHasChanged = true;
    }
    if (aNewMqttConfig.lastWellMsg.size() != lastWellMsgLen || memcmp(aNewMqttConfig.lastWellMsg.data(), lastWellMsg, lastWellMsgLen) != 0)
    {
        dataHasChanged = true;
    }
    if (aNewMqttConfig.lastWellQOS != lastWellQOS)
    {
        dataHasChanged = true;
    }
    if (aNewMqttConfig.lastWellRetain != lastWellRetain)
    {
        dataHasChanged = true;
    }
    if (aNewMqttConfig.cleanSession != cleanSession)
    {
        dataHasChanged = true;
    }
    if (aNewMqttConfig.reconnectTimeoutMS != reconnectTimeoutMS)
    {
        dataHasChanged = true;
    }
    if (aNewMqttConfig.timeoutMS != timeoutMS)
    {
        dataHasChanged = true;
    }
    if (aNewMqttConfig.refreshConnectionAfterMS != refreshConnectionAfterMS)
    {
        dataHasChanged = true;
    }
    if (aNewMqttConfig.replyTo.size() != replyToLen || memcmp(aNewMqttConfig.replyTo.data(), replyTo, replyToLen) != 0)
    {
        dataHasChanged = true;
    }
    return dataHasChanged;
}

CHIP_ERROR Instance::UpdateMqttConfig(Structs::PhotonMQTTStruct::Type aNewMqttConfig)
{
    ChipLogProgress(DeviceLayer, "Updating MQTT config");
    if (!aNewMqttConfig.host.size())
    {
        return CHIP_ERROR_INVALID_ARGUMENT;
    }
    ChipLogProgress(DeviceLayer, "Data: Host: %.*s, Port: %" PRIu16 ", Transport: %" PRIu8 ", KeepAlive: %" PRIu16,
                    aNewMqttConfig.host.size(), aNewMqttConfig.host.data(), aNewMqttConfig.port, aNewMqttConfig.transport,
                    aNewMqttConfig.keepAlive);

    if(mqttConfigHasChanged(aNewMqttConfig))
    {
       chip::Protocols::InteractionModel::Status status = Attributes::ShouldReboot::Set(mEndpointId, true);
       ChipLogProgress(DeviceLayer, "Requesting reboot: %d", status);
       if (status != chip::Protocols::InteractionModel::Status::Success)
       {
           return CHIP_ERROR_INCORRECT_STATE;
       }
    }

    memcpy(host, aNewMqttConfig.host.data(), aNewMqttConfig.host.size());
    storageDelegate.Put(MQTT_HOST_NVS_KEY, aNewMqttConfig.host.data(), aNewMqttConfig.host.size());
    port = aNewMqttConfig.port;
    storageDelegate.Put(MQTT_PORT_NVS_KEY, &port, sizeof(port));
    transport = aNewMqttConfig.transport == MqttTransport::kWss ? 4 : 2;
    storageDelegate.Put(MQTT_TRANSPORT_NVS_KEY, &transport, sizeof(transport));
    keepAlive = aNewMqttConfig.keepAlive;
    storageDelegate.Put(MQTT_KEEP_ALIVE_NVS_KEY, &keepAlive, sizeof(keepAlive));
    lastWellTopicLen = aNewMqttConfig.lastWellTopic.size();
    if(lastWellTopicLen)
    {
        memcpy(lastWellTopic, aNewMqttConfig.lastWellTopic.data(), aNewMqttConfig.lastWellTopic.size());
        storageDelegate.Put(MQTT_LAST_WILL_TOPIC_NVS_KEY, lastWellTopic, lastWellTopicLen);
    } else {
        memset(lastWellTopic, 0, sizeof(lastWellTopic));
        storageDelegate.Delete(MQTT_LAST_WILL_TOPIC_NVS_KEY);
    }
    
    lastWellMsgLen = aNewMqttConfig.lastWellMsg.size();
    if(lastWellMsgLen)
    {
        memcpy(lastWellMsg, aNewMqttConfig.lastWellMsg.data(), aNewMqttConfig.lastWellMsg.size());
        storageDelegate.Put(MQTT_LAST_WILL_MSG_NVS_KEY, lastWellMsg, lastWellMsgLen);
    } else {
        memset(lastWellMsg, 0, sizeof(lastWellMsg));
        storageDelegate.Delete(MQTT_LAST_WILL_MSG_NVS_KEY);
    }

    lastWellQOS = aNewMqttConfig.lastWellQOS;
    storageDelegate.Put(MQTT_LAST_WILL_QOS_NVS_KEY, &lastWellQOS, sizeof(lastWellQOS));
    lastWellRetain = aNewMqttConfig.lastWellRetain;
    storageDelegate.Put(MQTT_LAST_WILL_RETAIN_NVS_KEY, &lastWellRetain, sizeof(lastWellRetain));
    cleanSession = aNewMqttConfig.cleanSession;
    storageDelegate.Put(MQTT_CLEAN_SESSION_NVS_KEY, &cleanSession, sizeof(cleanSession));
    reconnectTimeoutMS = aNewMqttConfig.reconnectTimeoutMS;
    storageDelegate.Put(MQTT_RECONNECT_TIMEOUT_NVS_KEY, &reconnectTimeoutMS, sizeof(reconnectTimeoutMS));
    timeoutMS = aNewMqttConfig.timeoutMS;
    storageDelegate.Put(MQTT_NETWORK_TIMEOUT_NVS_KEY, &timeoutMS, sizeof(timeoutMS));
    refreshConnectionAfterMS = aNewMqttConfig.refreshConnectionAfterMS;
    storageDelegate.Put(MQTT_REFRESH_CONNECTION_AFTER_NVS_KEY, &refreshConnectionAfterMS, sizeof(refreshConnectionAfterMS));
    replyToLen = aNewMqttConfig.replyTo.size();
    if(replyToLen)
    {
        memcpy(replyTo, aNewMqttConfig.replyTo.data(), aNewMqttConfig.replyTo.size());
        storageDelegate.Put(MQTT_REPLY_TO_NVS_KEY, replyTo, replyToLen);
    } else {
        memset(replyTo, 0, sizeof(replyTo));
        storageDelegate.Delete(MQTT_REPLY_TO_NVS_KEY);
    }

    MatterReportingAttributeChangeCallback(ConcreteAttributePath(mEndpointId, Id, Attributes::MqttConfig::Id));
    return CHIP_NO_ERROR;
}

/**
 * @return The current MqttConfig PhotonMQTTStruct.
 */
Structs::PhotonMQTTStruct::Type Instance::GetMqttConfig()
{
    Structs::PhotonMQTTStruct::Type mMqttConfig;
    mMqttConfig.host = chip::CharSpan((char *) host, host_size);
    mMqttConfig.port = port;
    if (transport == 2 || transport == 4)
    {
        mMqttConfig.transport = transport == 2 ? MqttTransport::kSsl : MqttTransport::kWss;
    }
    else
    {
        mMqttConfig.transport = MqttTransport::kSsl;
    }
    mMqttConfig.keepAlive = keepAlive;
    if (lastWellTopicLen)
    {
        mMqttConfig.lastWellTopic = chip::CharSpan((char *) lastWellTopic, lastWellTopicLen);
    }
    else
    {
        mMqttConfig.lastWellTopic = chip::CharSpan();
    }
    if (lastWellMsgLen)
    {
        mMqttConfig.lastWellMsg = chip::ByteSpan(lastWellMsg, lastWellMsgLen);
    }
    else
    {
        mMqttConfig.lastWellMsg = chip::ByteSpan();
    }
    mMqttConfig.lastWellQOS              = lastWellQOS;
    mMqttConfig.lastWellRetain           = lastWellRetain;
    mMqttConfig.cleanSession             = cleanSession;
    mMqttConfig.reconnectTimeoutMS       = reconnectTimeoutMS;
    mMqttConfig.timeoutMS                = timeoutMS;
    mMqttConfig.refreshConnectionAfterMS = refreshConnectionAfterMS;
    if (replyToLen)
    {
        mMqttConfig.replyTo = chip::CharSpan((char *) replyTo, replyToLen);
    }
    else
    {
        mMqttConfig.replyTo = chip::CharSpan();
    }
    
    return mMqttConfig;
}

CHIP_ERROR Instance::Read(const ConcreteReadAttributePath & aPath, AttributeValueEncoder & aEncoder)
{
    switch (aPath.mAttributeId)
    {
    case Attributes::MqttConfig::Id:
        ReturnErrorOnFailure(aEncoder.Encode(GetMqttConfig()));
        break;
    }
    return CHIP_NO_ERROR;
}

CHIP_ERROR Instance::Write(const ConcreteDataAttributePath & attributePath, AttributeValueDecoder & aDecoder)
{
    VerifyOrDie(attributePath.mClusterId == Id);

    switch (attributePath.mAttributeId)
    {
    case Attributes::MqttConfig::Id: {
        Structs::PhotonMQTTStruct::Type newMqttConfig;
        CHIP_ERROR err = aDecoder.Decode(newMqttConfig);
        ChipLogProgress(DeviceLayer, "Write MqttConfig %x", err);
        ReturnErrorOnFailure(err);
        return UpdateMqttConfig(newMqttConfig);
    }
    break;
    default: // return CHIP_NO_ERROR and just write to the attribute store in default
        break;
    }
    return CHIP_NO_ERROR;
}

} // namespace PhotonSmart
} // namespace Clusters
} // namespace app
} // namespace chip

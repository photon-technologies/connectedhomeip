#include "photon-smart-server.h"

#include <app-common/zap-generated/attributes/Accessors.h>
#include <app/data-model/Nullable.h>
#include <app/reporting/reporting.h>
#include <app/util/attribute-storage.h>
#include <app/util/config.h>
#include <app/util/util.h>
#include <protocols/interaction_model/StatusCode.h>
#include <app/AttributeAccessInterfaceRegistry.h>
#include <src/platform/Photon/FctryStoreManager.h>

using namespace chip;
using namespace chip::app;
using namespace chip::app::Clusters;
using chip::Protocols::InteractionModel::Status;

namespace chip {
namespace app {
namespace Clusters {
namespace PhotonSmart {

class StorageDelagate : public DeviceLayer::PersistedStorage::FctryStoreManager
{
public:
    template<typename T>
    CHIP_ERROR Put(const char *key, const T &value)
    {
        return FctryStoreManager::Put(key, value);
    }

    template<typename T>
    CHIP_ERROR Get(const char *key, T *value)
    {
        return FctryStoreManager::Get(key, value);
    }
};

static StorageDelagate storageDelagate;
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

    // TODO: Load mMqttConfig from persistent storage
    chip::CharSpan host;
    uint16_t port           = static_cast<uint16_t>(8883);
    MqttTransport transport = static_cast<MqttTransport>(0);
    uint16_t keepAlive      = static_cast<uint16_t>(120);
    chip::CharSpan lastWellTopic;
    chip::ByteSpan lastWellMsg;
    uint16_t lastWellMsgLen           = static_cast<uint16_t>(0);
    uint8_t lastWellQOS               = static_cast<uint8_t>(0);
    bool lastWellRetain               = static_cast<bool>(0);
    bool cleanSession                 = static_cast<bool>(1);
    uint32_t reconnectTimeoutMS       = static_cast<uint32_t>(10000);
    uint32_t timeoutMS                = static_cast<uint32_t>(10000);
    uint32_t refreshConnectionAfterMS = static_cast<uint32_t>(0);


    VerifyOrDie(storageDelagate.Get(MQTT_HOST_NVS_KEY, &host) == CHIP_NO_ERROR);

    if (storageDelagate.Get(MQTT_PORT_NVS_KEY, &port) != CHIP_NO_ERROR)
    {
        storageDelagate.Put(MQTT_PORT_NVS_KEY, port);
    }

    if (storageDelagate.Get(MQTT_TRANSPORT_NVS_KEY, &transport) != CHIP_NO_ERROR)
    {
        storageDelagate.Put(MQTT_TRANSPORT_NVS_KEY, transport);
    }

    if (storageDelagate.Get(MQTT_KEEP_ALIVE_NVS_KEY, &keepAlive) != CHIP_NO_ERROR)
    {
        storageDelagate.Put(MQTT_KEEP_ALIVE_NVS_KEY, keepAlive);
    }

    if (storageDelagate.Get(MQTT_LAST_WILL_TOPIC_NVS_KEY, &lastWellTopic) != CHIP_NO_ERROR)
    {
        storageDelagate.Put(MQTT_LAST_WILL_TOPIC_NVS_KEY, lastWellTopic);
    }

    if (storageDelagate.Get(MQTT_LAST_WILL_MSG_NVS_KEY, &lastWellMsg) != CHIP_NO_ERROR)
    {
        storageDelagate.Put(MQTT_LAST_WILL_MSG_NVS_KEY, lastWellMsg);
    }

    lastWellMsgLen = lastWellMsg.size();

    if (storageDelagate.Get(MQTT_LAST_WILL_QOS_NVS_KEY, &lastWellQOS) != CHIP_NO_ERROR)
    {
        storageDelagate.Put(MQTT_LAST_WILL_QOS_NVS_KEY, lastWellQOS);
    }

    if (storageDelagate.Get(MQTT_LAST_WILL_RETAIN_NVS_KEY, &lastWellRetain) != CHIP_NO_ERROR)
    {
        storageDelagate.Put(MQTT_LAST_WILL_RETAIN_NVS_KEY, lastWellRetain);
    }

    if (storageDelagate.Get(MQTT_CLEAN_SESSION_NVS_KEY, &cleanSession) != CHIP_NO_ERROR)
    {
        storageDelagate.Put(MQTT_CLEAN_SESSION_NVS_KEY, cleanSession);
    }

    if (storageDelagate.Get(MQTT_RECONNECT_TIMEOUT_NVS_KEY, &reconnectTimeoutMS) != CHIP_NO_ERROR)
    {
        storageDelagate.Put(MQTT_RECONNECT_TIMEOUT_NVS_KEY, reconnectTimeoutMS);
    }

    if (storageDelagate.Get(MQTT_NETWORK_TIMEOUT_NVS_KEY, &timeoutMS) != CHIP_NO_ERROR)
    {
        storageDelagate.Put(MQTT_NETWORK_TIMEOUT_NVS_KEY, timeoutMS);
    }

    if (storageDelagate.Get(MQTT_REFRESH_CONNECTION_AFTER_NVS_KEY, &refreshConnectionAfterMS) != CHIP_NO_ERROR)
    {
        storageDelagate.Put(MQTT_REFRESH_CONNECTION_AFTER_NVS_KEY, refreshConnectionAfterMS);
    }

    VerifyOrReturnError(AttributeAccessInterfaceRegistry::Instance().Register(this), CHIP_ERROR_INCORRECT_STATE);

    return CHIP_NO_ERROR;
}

CHIP_ERROR Instance::UpdateMqttConfig(Structs::PhotonMQTTStruct::Type aNewMqttConfig)
{
    // TODO: Validate aNewMqttConfig if needed

    storageDelagate.Put(MQTT_HOST_NVS_KEY, mMqttConfig.host);
    storageDelagate.Put(MQTT_PORT_NVS_KEY, mMqttConfig.port);
    storageDelagate.Put(MQTT_TRANSPORT_NVS_KEY, mMqttConfig.transport);
    storageDelagate.Put(MQTT_KEEP_ALIVE_NVS_KEY, mMqttConfig.keepAlive);
    storageDelagate.Put(MQTT_LAST_WILL_TOPIC_NVS_KEY, mMqttConfig.lastWellTopic);
    storageDelagate.Put(MQTT_LAST_WILL_MSG_NVS_KEY, mMqttConfig.lastWellMsg);
    storageDelagate.Put(MQTT_LAST_WILL_QOS_NVS_KEY, mMqttConfig.lastWellQOS);
    storageDelagate.Put(MQTT_LAST_WILL_RETAIN_NVS_KEY, mMqttConfig.lastWellRetain);
    storageDelagate.Put(MQTT_CLEAN_SESSION_NVS_KEY, mMqttConfig.cleanSession);
    storageDelagate.Put(MQTT_RECONNECT_TIMEOUT_NVS_KEY, mMqttConfig.reconnectTimeoutMS);
    storageDelagate.Put(MQTT_NETWORK_TIMEOUT_NVS_KEY, mMqttConfig.timeoutMS);
    storageDelagate.Put(MQTT_REFRESH_CONNECTION_AFTER_NVS_KEY, mMqttConfig.refreshConnectionAfterMS);

    MatterReportingAttributeChangeCallback(ConcreteAttributePath(mEndpointId, Id, Attributes::MqttConfig::Id));
    return CHIP_NO_ERROR;
}

/**
 * @return The current MqttConfig PhotonMQTTStruct.
 */
Structs::PhotonMQTTStruct::Type Instance::GetMqttConfig()
{
    return mMqttConfig;
}

CHIP_ERROR Instance::Read(const ConcreteReadAttributePath &aPath, AttributeValueEncoder &aEncoder)
{
    switch (aPath.mAttributeId)
    {
    case Attributes::MqttConfig::Id:
            ReturnErrorOnFailure(aEncoder.Encode(mMqttConfig));
            break;
    }
    return CHIP_NO_ERROR;
}

CHIP_ERROR Instance::Write(const ConcreteDataAttributePath &attributePath, AttributeValueDecoder &aDecoder)
{
    VerifyOrDie(attributePath.mClusterId == Id);

    switch (attributePath.mAttributeId)
    {
    case Attributes::MqttConfig::Id: {
            Structs::PhotonMQTTStruct::Type newMqttConfig;
            ReturnErrorOnFailure(aDecoder.Decode(newMqttConfig));
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

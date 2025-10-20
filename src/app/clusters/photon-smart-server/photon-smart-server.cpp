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

    Delegate * gDelegate = nullptr;

    void SetDelegate(Delegate * delegate)
    {
        gDelegate = delegate;
    }

class StorageDelegate : public DeviceLayer::PersistedStorage::FctryStoreManager
{
public:
    CHIP_ERROR Put(uint8_t type, const char * key, const void * value, size_t value_size)
    {
        return FctryStoreManager::PutTyped(type, key, value, value_size);
    }

    CHIP_ERROR Get(uint8_t type, const char * key, void * buffer, size_t buffer_size, size_t * read_bytes_size = nullptr, size_t offset_bytes = 0)
    {
        return FctryStoreManager::GetTyped(type, key, buffer, buffer_size, read_bytes_size, offset_bytes);
    }
};

static StorageDelegate storageDelegate;

Instance::Instance(EndpointId aEndpointId) :
    AttributeAccessInterface(Optional<EndpointId>(aEndpointId), Id), mEndpointId(aEndpointId)
{
    insightsParams = {
        .core_dump_enable = true,
        .min_interval_sec = 300,
        .max_interval_sec = 3600,
        .drop_wifi_logs = true,
        .report_metrics = true,
        .metrics = {
            .report_heap_metrics = true,
            .report_wifi_metrics = true,
            .reporting_mode = {
                .polling = {
                    .heap_metrics_poll_interval_sec = 150,
                    .wifi_metrics_poll_interval_sec = 150,
                },
            },
            .use_polling = true},
        .report_variables = true,
        .variables = {
            .report_network_variables = true,
            .report_more_network_variables = true,
        },
        .watermark_percent = 80,
    };
}

Instance::~Instance()
{
    AttributeAccessInterfaceRegistry::Instance().Unregister(this);
}

CHIP_ERROR Instance::Init()
{
    // Check if the cluster has been selected in zap
    // VerifyOrDie(emberAfContainsServer(mEndpointId, Id) == true);

    // Set ShouldReboot to false on init as Init is called only after boot;
    Attributes::ShouldReboot::Set(mEndpointId, false);

    ChipLogProgress(DeviceLayer, "Init MQTT config");
    VerifyOrDie(storageDelegate.Get(0x41 /* Type blob */, MQTT_HOST_NVS_KEY, &host, sizeof(host), &host_size) == CHIP_NO_ERROR);
    ChipLogProgress(DeviceLayer, "host_size: %d == strlen(host): %d, last character %d", host_size, strlen((char *) host), host[host_size]);

    if (storageDelegate.Get(0x02 /* U16 */, MQTT_PORT_NVS_KEY, &port, sizeof(port)) != CHIP_NO_ERROR)
    {
        storageDelegate.Put(0x02 /* U16 */, MQTT_PORT_NVS_KEY, &port, sizeof(port));
    }

    if (storageDelegate.Get(0x01 /* U8 */, MQTT_TRANSPORT_NVS_KEY, &transport, sizeof(transport)) != CHIP_NO_ERROR)
    {
        storageDelegate.Put(0x01 /* U8 */, MQTT_TRANSPORT_NVS_KEY, &transport, sizeof(transport));
    }

    if (storageDelegate.Get(0x02 /* U16 */, MQTT_KEEP_ALIVE_NVS_KEY, &keepAlive, sizeof(keepAlive)) != CHIP_NO_ERROR)
    {
        storageDelegate.Put(0x02 /* U16 */, MQTT_KEEP_ALIVE_NVS_KEY, &keepAlive, sizeof(keepAlive));
    }
    ChipLogProgress(DeviceLayer, "lastWillTopicLen before: %d", lastWillTopicLen);
    storageDelegate.Get(0x41 /* Type blob */, MQTT_LAST_WILL_TOPIC_NVS_KEY, &lastWillTopic, sizeof(lastWillTopic), &lastWillTopicLen);
    ChipLogProgress(DeviceLayer, "lastWillTopic: %.*s", lastWillTopicLen, lastWillTopic);
    ChipLogProgress(DeviceLayer, "lastWillTopicLen: after %d == strlen(lastWillTopic): %d, last character %d", lastWillTopicLen, strlen((char *) lastWillTopic), lastWillTopic[lastWillTopicLen]);

    ChipLogProgress(DeviceLayer, "lastWillMsgLen before: %d", lastWillMsgLen);
    storageDelegate.Get(0x41 /* Type blob */, MQTT_LAST_WILL_MSG_NVS_KEY, &lastWillMsg, sizeof(lastWillMsg), &lastWillMsgLen);
    ChipLogProgress(DeviceLayer, "lastWillMsg: %.*s", lastWillMsgLen, lastWillMsg);
    ChipLogProgress(DeviceLayer, "lastWillMsgLen: after %d == strlen(lastWillMsg): %d, last character %d", lastWillMsgLen, strlen((char *) lastWillMsg), lastWillMsg[lastWillMsgLen]);


    if (storageDelegate.Get(0x01 /* U8 */, MQTT_LAST_WILL_QOS_NVS_KEY, &lastWillQOS, sizeof(lastWillQOS)) != CHIP_NO_ERROR)
    {
        storageDelegate.Put(0x01 /* U8 */, MQTT_LAST_WILL_QOS_NVS_KEY, &lastWillQOS, sizeof(lastWillQOS));
    }

    if (storageDelegate.Get(0x01 /* U8 */, MQTT_LAST_WILL_RETAIN_NVS_KEY, &lastWillRetain, sizeof(lastWillRetain)) != CHIP_NO_ERROR)
    {
        storageDelegate.Put(0x01 /* U8 */, MQTT_LAST_WILL_RETAIN_NVS_KEY, &lastWillRetain, sizeof(lastWillRetain));
    }

    if (storageDelegate.Get(0x01 /* U8 */, MQTT_CLEAN_SESSION_NVS_KEY, &cleanSession, sizeof(cleanSession)) != CHIP_NO_ERROR)
    {
        storageDelegate.Put(0x01 /* U8 */, MQTT_CLEAN_SESSION_NVS_KEY, &cleanSession, sizeof(cleanSession));
    }

    if (storageDelegate.Get(0x04 /*!< U32 */, MQTT_RECONNECT_TIMEOUT_NVS_KEY, &reconnectTimeoutMS, sizeof(reconnectTimeoutMS)) != CHIP_NO_ERROR)
    {
        storageDelegate.Put(0x04 /*!< U32 */, MQTT_RECONNECT_TIMEOUT_NVS_KEY, &reconnectTimeoutMS, sizeof(reconnectTimeoutMS));
    }

    if (storageDelegate.Get(0x04 /*!< U32 */, MQTT_NETWORK_TIMEOUT_NVS_KEY, &timeoutMS, sizeof(timeoutMS)) != CHIP_NO_ERROR)
    {
        storageDelegate.Put(0x04 /*!< U32 */, MQTT_NETWORK_TIMEOUT_NVS_KEY, &timeoutMS, sizeof(timeoutMS));
    }

    if (storageDelegate.Get(0x04 /*!< U32 */, MQTT_REFRESH_CONNECTION_AFTER_NVS_KEY, &refreshConnectionAfterMS, sizeof(refreshConnectionAfterMS)) !=
        CHIP_NO_ERROR)
    {
        storageDelegate.Put(0x04 /*!< U32 */, MQTT_REFRESH_CONNECTION_AFTER_NVS_KEY, &refreshConnectionAfterMS, sizeof(refreshConnectionAfterMS));
    }

    storageDelegate.Get(0x41 /* Type blob */, MQTT_REPLY_TO_NVS_KEY, &replyTo, sizeof(replyTo), &replyToLen);


    if (storageDelegate.Get(0x41 /* Type blob */, INSIGHTS_PARAMS_NVS_KEY, &insightsParams, sizeof(photon_insights_params_t)) != CHIP_NO_ERROR)
    {
        storageDelegate.Put(0x41 /* Type blob */, INSIGHTS_PARAMS_NVS_KEY, &insightsParams, sizeof(photon_insights_params_t));
    }

    storageDelegate.Get(0x01 /* U8 */, MQTT_ENABLED_NVS_KEY, &mqttEnabled, sizeof(mqttEnabled));
    storageDelegate.Get(0x01 /* U8 */, INSIGHTS_ENABLED_NVS_KEY, &insightsEnabled, sizeof(insightsEnabled));

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
    if (aNewMqttConfig.lastWillTopic.size() != lastWillTopicLen || memcmp(aNewMqttConfig.lastWillTopic.data(), lastWillTopic, lastWillTopicLen) != 0)
    {
        dataHasChanged = true;
    }
    if (aNewMqttConfig.lastWillMsg.size() != lastWillMsgLen || memcmp(aNewMqttConfig.lastWillMsg.data(), lastWillMsg, lastWillMsgLen) != 0)
    {
        dataHasChanged = true;
    }
    if (aNewMqttConfig.lastWillQOS != lastWillQOS)
    {
        dataHasChanged = true;
    }
    if (aNewMqttConfig.lastWillRetain != lastWillRetain)
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

CHIP_ERROR Instance::UpdateInsightsParams(const Structs::PhotonInsightsParamsStruct::Type aNewInsightsParams)
{
    insightsParams.core_dump_enable = aNewInsightsParams.coreDumpEnabled;
    insightsParams.min_interval_sec = aNewInsightsParams.minInterval;
    insightsParams.max_interval_sec = aNewInsightsParams.maxInterval;
    insightsParams.drop_wifi_logs   = aNewInsightsParams.dropWifiLogs;
    insightsParams.report_metrics   = aNewInsightsParams.reportMetrics;
    insightsParams.metrics.report_heap_metrics = aNewInsightsParams.reportHeapMetrics;
    insightsParams.metrics.report_wifi_metrics = aNewInsightsParams.reportWifiMetrics;
    insightsParams.metrics.use_polling = aNewInsightsParams.usePolling;
    if(aNewInsightsParams.usePolling)
    {
        insightsParams.metrics.reporting_mode.polling.heap_metrics_poll_interval_sec =
            aNewInsightsParams.heapPollingInterval;
        insightsParams.metrics.reporting_mode.polling.wifi_metrics_poll_interval_sec =
            aNewInsightsParams.wifiPollingInterval;
    } else {
        insightsParams.metrics.reporting_mode.count.heap_metrics_report_count =
            aNewInsightsParams.heapPollingCount;
        insightsParams.metrics.reporting_mode.count.wifi_metrics_report_count =
            aNewInsightsParams.wifiPollingCount;
    }
    insightsParams.report_variables = aNewInsightsParams.reportVariables;
    insightsParams.variables.report_network_variables = aNewInsightsParams.reportNetworkVariables;
    insightsParams.variables.report_more_network_variables = aNewInsightsParams.reportMoreNetworkVariables;
    insightsParams.watermark_percent = aNewInsightsParams.reportWatermarkPercent;
    if(storageDelegate.Put(0x41 /* Type blob */, INSIGHTS_PARAMS_NVS_KEY, &insightsParams, sizeof(photon_insights_params_t)) != CHIP_NO_ERROR)
    {
        return CHIP_ERROR_INCORRECT_STATE;
    }
    if (gDelegate != nullptr)
    {
        gDelegate->OnInsightsParamsUpdated(&insightsParams);
    }
    MatterReportingAttributeChangeCallback(ConcreteAttributePath(mEndpointId, Id, Attributes::InsightsParams::Id));
    return CHIP_NO_ERROR;
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
    storageDelegate.Put(0x41 /* Type blob */, MQTT_HOST_NVS_KEY, aNewMqttConfig.host.data(), aNewMqttConfig.host.size());
    port = aNewMqttConfig.port;
    storageDelegate.Put(0x02 /* Type u16 */, MQTT_PORT_NVS_KEY, &port, sizeof(port));
    transport = aNewMqttConfig.transport == MqttTransport::kWss ? 4 : 2;
    storageDelegate.Put(0x01 /* Type u8 */, MQTT_TRANSPORT_NVS_KEY, &transport, sizeof(transport));
    keepAlive = aNewMqttConfig.keepAlive;
    storageDelegate.Put(0x02 /* Type u16 */, MQTT_KEEP_ALIVE_NVS_KEY, &keepAlive, sizeof(keepAlive));
    lastWillTopicLen = aNewMqttConfig.lastWillTopic.size();
    if(lastWillTopicLen)
    {
        memcpy(lastWillTopic, aNewMqttConfig.lastWillTopic.data(), aNewMqttConfig.lastWillTopic.size());
        storageDelegate.Put(0x41 /* Type blob */, MQTT_LAST_WILL_TOPIC_NVS_KEY, lastWillTopic, lastWillTopicLen);
    } else {
        memset(lastWillTopic, 0, sizeof(lastWillTopic));
        storageDelegate.Delete(MQTT_LAST_WILL_TOPIC_NVS_KEY);
    }
    
    lastWillMsgLen = aNewMqttConfig.lastWillMsg.size();
    if(lastWillMsgLen)
    {
        memcpy(lastWillMsg, aNewMqttConfig.lastWillMsg.data(), aNewMqttConfig.lastWillMsg.size());
        storageDelegate.Put(0x41 /* Type blob */, MQTT_LAST_WILL_MSG_NVS_KEY, lastWillMsg, lastWillMsgLen);
    } else {
        memset(lastWillMsg, 0, sizeof(lastWillMsg));
        storageDelegate.Delete(MQTT_LAST_WILL_MSG_NVS_KEY);
    }

    lastWillQOS = aNewMqttConfig.lastWillQOS;
    storageDelegate.Put(0x01 /* Type u8 */, MQTT_LAST_WILL_QOS_NVS_KEY, &lastWillQOS, sizeof(lastWillQOS));
    lastWillRetain = aNewMqttConfig.lastWillRetain;
    storageDelegate.Put(0x01 /* Type u8 */, MQTT_LAST_WILL_RETAIN_NVS_KEY, &lastWillRetain, sizeof(lastWillRetain));
    cleanSession = aNewMqttConfig.cleanSession;
    storageDelegate.Put(0x01 /* Type u8 */, MQTT_CLEAN_SESSION_NVS_KEY, &cleanSession, sizeof(cleanSession));
    reconnectTimeoutMS = aNewMqttConfig.reconnectTimeoutMS;
    storageDelegate.Put(0x04 /* Type u32 */, MQTT_RECONNECT_TIMEOUT_NVS_KEY, &reconnectTimeoutMS, sizeof(reconnectTimeoutMS));
    timeoutMS = aNewMqttConfig.timeoutMS;
    storageDelegate.Put(0x04 /* Type u32 */, MQTT_NETWORK_TIMEOUT_NVS_KEY, &timeoutMS, sizeof(timeoutMS));
    refreshConnectionAfterMS = aNewMqttConfig.refreshConnectionAfterMS;
    storageDelegate.Put(0x04 /* Type u32 */, MQTT_REFRESH_CONNECTION_AFTER_NVS_KEY, &refreshConnectionAfterMS, sizeof(refreshConnectionAfterMS));
    replyToLen = aNewMqttConfig.replyTo.size();
    if(replyToLen)
    {
        memcpy(replyTo, aNewMqttConfig.replyTo.data(), aNewMqttConfig.replyTo.size());
        storageDelegate.Put(0x41 /* Type blob */, MQTT_REPLY_TO_NVS_KEY, replyTo, replyToLen);
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
    if (lastWillTopicLen)
    {
        mMqttConfig.lastWillTopic = chip::CharSpan((char *) lastWillTopic, lastWillTopicLen);
    }
    else
    {
        mMqttConfig.lastWillTopic = chip::CharSpan();
    }
    if (lastWillMsgLen)
    {
        mMqttConfig.lastWillMsg = chip::ByteSpan(lastWillMsg, lastWillMsgLen);
    }
    else
    {
        mMqttConfig.lastWillMsg = chip::ByteSpan();
    }
    mMqttConfig.lastWillQOS              = lastWillQOS;
    mMqttConfig.lastWillRetain           = lastWillRetain;
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

Structs::PhotonInsightsParamsStruct::Type Instance::GetInsightsParams()
{
    Structs::PhotonInsightsParamsStruct::Type mInsightsParams;
    mInsightsParams.coreDumpEnabled              = insightsParams.core_dump_enable;
    mInsightsParams.minInterval                  = insightsParams.min_interval_sec;
    mInsightsParams.maxInterval                  = insightsParams.max_interval_sec;
    mInsightsParams.dropWifiLogs                 = insightsParams.drop_wifi_logs;
    mInsightsParams.reportMetrics                = insightsParams.report_metrics;
    mInsightsParams.reportHeapMetrics            = insightsParams.metrics.report_heap_metrics;
    mInsightsParams.reportWifiMetrics            = insightsParams.metrics.report_wifi_metrics;
    mInsightsParams.usePolling                   = insightsParams.metrics.use_polling;
    if(insightsParams.metrics.use_polling)
    {
        mInsightsParams.heapPollingInterval      = insightsParams.metrics.reporting_mode.polling.heap_metrics_poll_interval_sec;
        mInsightsParams.wifiPollingInterval      = insightsParams.metrics.reporting_mode.polling.wifi_metrics_poll_interval_sec;
         mInsightsParams.heapPollingCount        = static_cast<uint8_t>(0);
         mInsightsParams.wifiPollingCount        = static_cast<uint8_t>(0);
    }else {
        mInsightsParams.heapPollingInterval      = static_cast<uint32_t>(0);
        mInsightsParams.wifiPollingInterval      = static_cast<uint32_t>(0);
        mInsightsParams.heapPollingCount         = insightsParams.metrics.reporting_mode.count.heap_metrics_report_count;
        mInsightsParams.wifiPollingCount         = insightsParams.metrics.reporting_mode.count.wifi_metrics_report_count;
    }
    mInsightsParams.reportVariables              = insightsParams.report_variables;
    mInsightsParams.reportNetworkVariables       = insightsParams.variables.report_network_variables;
    mInsightsParams.reportMoreNetworkVariables   = insightsParams.variables.report_more_network_variables;
    mInsightsParams.reportWatermarkPercent       = insightsParams.watermark_percent;

    return mInsightsParams;
}

CHIP_ERROR Instance::Read(const ConcreteReadAttributePath & aPath, AttributeValueEncoder & aEncoder)
{
    switch (aPath.mAttributeId)
    {
    case Attributes::MqttConfig::Id:
        ReturnErrorOnFailure(aEncoder.Encode(GetMqttConfig()));
        break;
    
    case Attributes::InsightsParams::Id:
        ReturnErrorOnFailure(aEncoder.Encode(GetInsightsParams()));
        break;
    case Attributes::InsightsEnabled::Id:
        ReturnErrorOnFailure(aEncoder.Encode(insightsEnabled));
        break;
        case Attributes::MqttReportEnabled::Id:
        ReturnErrorOnFailure(aEncoder.Encode(mqttEnabled));
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
    case Attributes::InsightsParams::Id: {
        Structs::PhotonInsightsParamsStruct::Type newInsightsParams;
        CHIP_ERROR err = aDecoder.Decode(newInsightsParams);
        ChipLogProgress(DeviceLayer, "Write InsightsParams %x", err);
        ReturnErrorOnFailure(err);
        return UpdateInsightsParams(newInsightsParams);
    }
    break;
    case Attributes::InsightsEnabled::Id: {
        bool newInsightsEnabled;
        CHIP_ERROR err = aDecoder.Decode(newInsightsEnabled);
        ChipLogProgress(DeviceLayer, "Write InsightsEnabled %x", err);
        ReturnErrorOnFailure(err);
        insightsEnabled = newInsightsEnabled;
        err = storageDelegate.Put(0x01 /* Type u8 */, INSIGHTS_ENABLED_NVS_KEY, &insightsEnabled, sizeof(insightsEnabled));
        ReturnErrorOnFailure(err);
        if (gDelegate != nullptr)
        {
            gDelegate->OnInsightsEnabledUpdated(insightsEnabled);
        }
        MatterReportingAttributeChangeCallback(ConcreteAttributePath(mEndpointId, Id, Attributes::InsightsEnabled::Id));
        
    }
    break;
    case Attributes::MqttReportEnabled::Id: {
        bool newMqttReportEnabled;
        CHIP_ERROR err = aDecoder.Decode(newMqttReportEnabled);
        ChipLogProgress(DeviceLayer, "Write MqttReportEnabled %x", err);
        ReturnErrorOnFailure(err);
        if(mqttEnabled == newMqttReportEnabled)
        {
            ChipLogProgress(DeviceLayer, "MqttReportEnabled not changed");
            return CHIP_NO_ERROR;
        }
        // Update ShouldReboot attribute to true to indicate that a reboot is required to apply the new setting
        chip::Protocols::InteractionModel::Status status = Attributes::ShouldReboot::Set(mEndpointId, true);
        ChipLogProgress(DeviceLayer, "Requesting reboot: %d", status);
        if (status != chip::Protocols::InteractionModel::Status::Success)
        {
            return CHIP_ERROR_INCORRECT_STATE;
        }
        mqttEnabled = newMqttReportEnabled;
        err = storageDelegate.Put(0x01 /* Type u8 */, MQTT_ENABLED_NVS_KEY, &mqttEnabled, sizeof(mqttEnabled));
        ReturnErrorOnFailure(err);
        MatterReportingAttributeChangeCallback(ConcreteAttributePath(mEndpointId, Id, Attributes::MqttReportEnabled::Id));
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

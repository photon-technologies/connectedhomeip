/*
 *
 *    Copyright (c) 2020 Project CHIP Authors
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#pragma once

#include <app-common/zap-generated/cluster-objects.h>
#include <app/AttributeAccessInterface.h>
#include <app/CommandHandler.h>
#include <app/ConcreteCommandPath.h>
#include <app/util/af-types.h>
#include <app/util/basic-types.h>
#include <platform/CHIPDeviceConfig.h>
#include <protocols/interaction_model/StatusCode.h>
#include "photon-smart-delegate.h"

/**********************************************************
 * Defines and Macros
 *********************************************************/
static constexpr char * const MQTT_HOST_NVS_KEY                     = "mqtt_host";
static constexpr char * const MQTT_PORT_NVS_KEY                     = "mqtt_port";
static constexpr char * const MQTT_TRANSPORT_NVS_KEY                = "mqtt_transport";
static constexpr char * const MQTT_LAST_WILL_TOPIC_NVS_KEY          = "lwt_topic";
static constexpr char * const MQTT_LAST_WILL_MSG_NVS_KEY            = "lwt_msg";
static constexpr char * const MQTT_LAST_WILL_QOS_NVS_KEY            = "lwt_qos";
static constexpr char * const MQTT_LAST_WILL_RETAIN_NVS_KEY         = "lwt_retain";
static constexpr char * const MQTT_CLEAN_SESSION_NVS_KEY            = "clean_session";
static constexpr char * const MQTT_KEEP_ALIVE_NVS_KEY               = "keep_alive";
static constexpr char * const MQTT_RECONNECT_TIMEOUT_NVS_KEY        = "recon_timeout";
static constexpr char * const MQTT_NETWORK_TIMEOUT_NVS_KEY          = "net_timeout";
static constexpr char * const MQTT_REFRESH_CONNECTION_AFTER_NVS_KEY = "ref_con_after";
static constexpr char * const MQTT_REPLY_TO_NVS_KEY                 = "mqtt_reply_to";
static constexpr char * const MQTT_ENABLED_NVS_KEY                  = "mqtt_en";
static constexpr char * const INSIGHTS_ENABLED_NVS_KEY              = "insights_en";
static constexpr char * const INSIGHTS_PARAMS_NVS_KEY               = "insights_params";
static constexpr char * const PUBLIC_IPV4_ENABLED_NVS_KEY           = "pub_ipv4";

namespace chip::DeviceLayer::PersistedStorage {
class KeyValueStoreManager;
}

namespace chip {
namespace app {
namespace Clusters {
namespace PhotonSmart {


class Instance : public AttributeAccessInterface
{
public:
    /**
     * Creates an air quality cluster instance. The Init() function needs to be called for this instance to be registered and
     * called by the interaction model at the appropriate times.
     * @param aEndpointId The endpoint on which this cluster exists. This must match the zap configuration.
     * @param aFeature The bitmask value that identifies which features are supported by this instance.
     */
    Instance(EndpointId aEndpointId);

    ~Instance() override;

    /**
     * Initialises the air quality cluster instance
     * @return Returns an error if an air quality cluster has not been enabled in zap for the given endpoint ID or
     * if the AttributeHandler registration fails.
     */
    CHIP_ERROR Init();

    /**
     * Sets the MqttConfig attribute.
     * @param aNewMqttConfig The value to which the MqttConfig attribute is to be set.
     * @return Returns a ConstraintError if the aNewMqttConfig value is not valid. Returns Success otherwise.
     */
    CHIP_ERROR UpdateMqttConfig(Structs::PhotonMQTTStruct::Type aNewMqttConfig);

    /**
     * @return The current InsightsParams PhotonInsightsParamsStruct.
     */
    Structs::PhotonInsightsParamsStruct::Type GetInsightsParams();

    /**
     * Sets the InsightsParams attribute.
     * @param aNewInsightsParams The value to which the InsightsParams attribute is to be set.
     * @return Returns a ConstraintError if the aNewInsightsParams value is not valid. Returns Success otherwise.
     */
    CHIP_ERROR UpdateInsightsParams(Structs::PhotonInsightsParamsStruct::Type aNewInsightsParams);

    /**
     * @return The current MqttConfig PhotonMQTTStruct.
     */
    Structs::PhotonMQTTStruct::Type GetMqttConfig();

private:
    EndpointId mEndpointId;
    uint8_t host[254];
    size_t host_size   = 0;
    uint16_t port      = static_cast<uint16_t>(8883);
    uint8_t transport  = static_cast<uint8_t>(2);
    uint16_t keepAlive = static_cast<uint16_t>(120);
    uint8_t lastWillTopic[254];
    size_t lastWillTopicLen = 0;
    uint8_t lastWillMsg[1000];
    size_t lastWillMsgLen             = 0;
    uint8_t lastWillQOS               = static_cast<uint8_t>(0);
    bool lastWillRetain               = static_cast<bool>(0);
    bool cleanSession                 = static_cast<bool>(1);
    uint32_t reconnectTimeoutMS       = static_cast<uint32_t>(10000);
    uint32_t timeoutMS                = static_cast<uint32_t>(10000);
    uint32_t refreshConnectionAfterMS = static_cast<uint32_t>(0);
    uint8_t replyTo[128];   
    size_t replyToLen = 0;
    
    photon_insights_params_t insightsParams;
    bool insightsEnabled = true;
    bool mqttEnabled     = true;
    bool getPublicIpv4   = true;

    bool mqttConfigHasChanged(const Structs::PhotonMQTTStruct::Type & aNewMqttConfig);

    // AttributeAccessInterface
    CHIP_ERROR Read(const ConcreteReadAttributePath & aPath, AttributeValueEncoder & aEncoder) override;
    CHIP_ERROR Write(const ConcreteDataAttributePath & aPath, AttributeValueDecoder & aDecoder) override;
};

} // namespace PhotonSmart
} // namespace Clusters
} // namespace app
} // namespace chip

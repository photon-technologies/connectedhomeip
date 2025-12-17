#pragma once

#include <app-common/zap-generated/cluster-objects.h>
#include <protocols/interaction_model/StatusCode.h>
#include <lib/support/Span.h>

namespace chip {
namespace app {
namespace Clusters {
namespace PhotonSmart {

typedef struct __attribute__((packed)) {
  bool core_dump_enable;      /*!< Enable coredump reporting */
  uint32_t min_interval_sec;  /*!< Minimum interval between data reports to cloud in seconds */
  uint32_t max_interval_sec;  /*!< Maximum interval between data reports to cloud in seconds */
  bool drop_wifi_logs;        /*!< Drop wifi logs from insights */
  bool report_metrics;         /*!< Enable reporting of metrics */
  struct params_metrics_t {
      union reporting_t {
          struct polling_t {
              uint32_t heap_metrics_poll_interval_sec; /*!< Polling interval for heap metrics in seconds */
              uint32_t wifi_metrics_poll_interval_sec; /*!< Polling interval for wifi metrics in seconds */
          } polling;
          struct count_t {
              uint8_t heap_metrics_report_count; /*!< Number of times metrics will be reported within interval */
              uint8_t wifi_metrics_report_count; /*!< Number of times wifi metrics will be reported within interval */
          } count;
      } reporting_mode;               /*!< Reporting mode: polling or count based */
        bool report_heap_metrics;    /*!< Enable reporting of heap metrics */
        bool report_wifi_metrics;    /*!< Enable reporting of wifi metrics */
      bool use_polling;           /*!< Use polling based reporting if true, else use count based reporting */
  } metrics;
  bool report_variables;       /*!< Enable reporting of variables */
  struct params_variables_t {
      bool report_network_variables; /*!< Enable reporting of network variables */
      bool report_more_network_variables; /*!< Enable reporting of Advanced network variables */
  } variables;
  uint8_t watermark_percent;       /*!< Watermark percentage to trigger data send */
} photon_insights_params_t;

typedef struct __attribute__((packed)) {
    uint32_t session_expiry_interval;            /*!< The interval time of session expiry */
    uint32_t maximum_packet_size;                /*!< The maximum packet size that we can receive */
    uint16_t receive_maximum;                    /*!< The maximum pakcket count that we process concurrently */
    uint16_t topic_alias_maximum;                /*!< The maximum topic alias that we support */
    bool request_resp_info;                      /*!< This value to request Server to return Response information */
    bool request_problem_info;                   /*!< This value to indicate whether the reason string or user properties are sent in case of failures */
    uint32_t will_delay_interval;                /*!< The time interval that server delays publishing will message  */
    uint32_t message_expiry_interval;            /*!< The time interval that message expiry */
    bool payload_format_indicator;               /*!< This value is to indicator will message payload format */
} photon_mqtt5_conn_config_t;
class Delegate
{
public:
    virtual ~Delegate() = default;

    // virtual void OnMqttConfigUpdated(const Structs::PhotonMQTTStruct::Type & aNewMqttConfig) = 0;
    virtual void OnInsightsParamsUpdated(photon_insights_params_t *aNewInsightsParams) = 0;
    virtual void OnInsightsEnabledUpdated(bool aNewInsightsEnabled) = 0;
    virtual void GetDeviceId(MutableCharSpan & aDeviceId) = 0;
};

} // namespace PhotonSmart
} // namespace Clusters
} // namespace app
} // namespace chip
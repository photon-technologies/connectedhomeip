#pragma once

#include <app-common/zap-generated/cluster-objects.h>
#include <protocols/interaction_model/StatusCode.h>

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
      bool report_heap_metrics;    /*!< Enable reporting of heap metrics */
      bool report_wifi_metrics;    /*!< Enable reporting of wifi metrics */
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
      bool use_polling;           /*!< Use polling based reporting if true, else use count based reporting */
  } metrics;
  bool report_variables;       /*!< Enable reporting of variables */
  struct params_variables_t {
      bool report_network_variables; /*!< Enable reporting of network variables */
      bool report_more_network_variables; /*!< Enable reporting of Advanced network variables */
  } variables;
  uint8_t watermark_percent;       /*!< Watermark percentage to trigger data send */
} photon_insights_params_t;

class Delegate
{
public:
    virtual ~Delegate() = default;

    // virtual void OnMqttConfigUpdated(const Structs::PhotonMQTTStruct::Type & aNewMqttConfig) = 0;
    virtual void OnInsightsParamsUpdated(photon_insights_params_t *aNewInsightsParams) = 0;
    virtual void OnInsightsEnabledUpdated(bool aNewInsightsEnabled) = 0;
};

} // namespace PhotonSmart
} // namespace Clusters
} // namespace app
} // namespace chip
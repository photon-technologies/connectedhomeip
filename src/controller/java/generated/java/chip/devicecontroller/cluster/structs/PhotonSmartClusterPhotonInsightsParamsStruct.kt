/*
 *
 *    Copyright (c) 2023 Project CHIP Authors
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
package chip.devicecontroller.cluster.structs

import chip.devicecontroller.cluster.*
import matter.tlv.AnonymousTag
import matter.tlv.ContextSpecificTag
import matter.tlv.Tag
import matter.tlv.TlvParsingException
import matter.tlv.TlvReader
import matter.tlv.TlvWriter

import java.util.Optional

class PhotonSmartClusterPhotonInsightsParamsStruct (
    val coreDumpEnabled: Boolean,
    val minInterval: ULong,
    val maxInterval: ULong,
    val dropWifiLogs: Boolean,
    val reportMetrics: Boolean,
    val reportHeapMetrics: Boolean,
    val heapPollingInterval: ULong,
    val heapPollingCount: UInt,
    val reportWifiMetrics: Boolean,
    val wifiPollingInterval: ULong,
    val wifiPollingCount: UInt,
    val usePolling: Boolean,
    val reportVariables: Boolean,
    val reportNetworkVariables: Boolean,
    val reportMoreNetworkVariables: Boolean,
    val reportWatermarkPercent: UInt) {
  override fun toString(): String  = buildString {
    append("PhotonSmartClusterPhotonInsightsParamsStruct {\n")
    append("\tcoreDumpEnabled : $coreDumpEnabled\n")
    append("\tminInterval : $minInterval\n")
    append("\tmaxInterval : $maxInterval\n")
    append("\tdropWifiLogs : $dropWifiLogs\n")
    append("\treportMetrics : $reportMetrics\n")
    append("\treportHeapMetrics : $reportHeapMetrics\n")
    append("\theapPollingInterval : $heapPollingInterval\n")
    append("\theapPollingCount : $heapPollingCount\n")
    append("\treportWifiMetrics : $reportWifiMetrics\n")
    append("\twifiPollingInterval : $wifiPollingInterval\n")
    append("\twifiPollingCount : $wifiPollingCount\n")
    append("\tusePolling : $usePolling\n")
    append("\treportVariables : $reportVariables\n")
    append("\treportNetworkVariables : $reportNetworkVariables\n")
    append("\treportMoreNetworkVariables : $reportMoreNetworkVariables\n")
    append("\treportWatermarkPercent : $reportWatermarkPercent\n")
    append("}\n")
  }

  fun toTlv(tlvTag: Tag, tlvWriter: TlvWriter) {
    tlvWriter.apply {
      startStructure(tlvTag)
      put(ContextSpecificTag(TAG_CORE_DUMP_ENABLED), coreDumpEnabled)
      put(ContextSpecificTag(TAG_MIN_INTERVAL), minInterval)
      put(ContextSpecificTag(TAG_MAX_INTERVAL), maxInterval)
      put(ContextSpecificTag(TAG_DROP_WIFI_LOGS), dropWifiLogs)
      put(ContextSpecificTag(TAG_REPORT_METRICS), reportMetrics)
      put(ContextSpecificTag(TAG_REPORT_HEAP_METRICS), reportHeapMetrics)
      put(ContextSpecificTag(TAG_HEAP_POLLING_INTERVAL), heapPollingInterval)
      put(ContextSpecificTag(TAG_HEAP_POLLING_COUNT), heapPollingCount)
      put(ContextSpecificTag(TAG_REPORT_WIFI_METRICS), reportWifiMetrics)
      put(ContextSpecificTag(TAG_WIFI_POLLING_INTERVAL), wifiPollingInterval)
      put(ContextSpecificTag(TAG_WIFI_POLLING_COUNT), wifiPollingCount)
      put(ContextSpecificTag(TAG_USE_POLLING), usePolling)
      put(ContextSpecificTag(TAG_REPORT_VARIABLES), reportVariables)
      put(ContextSpecificTag(TAG_REPORT_NETWORK_VARIABLES), reportNetworkVariables)
      put(ContextSpecificTag(TAG_REPORT_MORE_NETWORK_VARIABLES), reportMoreNetworkVariables)
      put(ContextSpecificTag(TAG_REPORT_WATERMARK_PERCENT), reportWatermarkPercent)
      endStructure()
    }
  }

  companion object {
    private const val TAG_CORE_DUMP_ENABLED = 0
    private const val TAG_MIN_INTERVAL = 1
    private const val TAG_MAX_INTERVAL = 2
    private const val TAG_DROP_WIFI_LOGS = 3
    private const val TAG_REPORT_METRICS = 4
    private const val TAG_REPORT_HEAP_METRICS = 5
    private const val TAG_HEAP_POLLING_INTERVAL = 6
    private const val TAG_HEAP_POLLING_COUNT = 7
    private const val TAG_REPORT_WIFI_METRICS = 8
    private const val TAG_WIFI_POLLING_INTERVAL = 9
    private const val TAG_WIFI_POLLING_COUNT = 10
    private const val TAG_USE_POLLING = 11
    private const val TAG_REPORT_VARIABLES = 12
    private const val TAG_REPORT_NETWORK_VARIABLES = 13
    private const val TAG_REPORT_MORE_NETWORK_VARIABLES = 14
    private const val TAG_REPORT_WATERMARK_PERCENT = 15

    fun fromTlv(tlvTag: Tag, tlvReader: TlvReader) : PhotonSmartClusterPhotonInsightsParamsStruct {
      tlvReader.enterStructure(tlvTag)
      val coreDumpEnabled = tlvReader.getBoolean(ContextSpecificTag(TAG_CORE_DUMP_ENABLED))
      val minInterval = tlvReader.getULong(ContextSpecificTag(TAG_MIN_INTERVAL))
      val maxInterval = tlvReader.getULong(ContextSpecificTag(TAG_MAX_INTERVAL))
      val dropWifiLogs = tlvReader.getBoolean(ContextSpecificTag(TAG_DROP_WIFI_LOGS))
      val reportMetrics = tlvReader.getBoolean(ContextSpecificTag(TAG_REPORT_METRICS))
      val reportHeapMetrics = tlvReader.getBoolean(ContextSpecificTag(TAG_REPORT_HEAP_METRICS))
      val heapPollingInterval = tlvReader.getULong(ContextSpecificTag(TAG_HEAP_POLLING_INTERVAL))
      val heapPollingCount = tlvReader.getUInt(ContextSpecificTag(TAG_HEAP_POLLING_COUNT))
      val reportWifiMetrics = tlvReader.getBoolean(ContextSpecificTag(TAG_REPORT_WIFI_METRICS))
      val wifiPollingInterval = tlvReader.getULong(ContextSpecificTag(TAG_WIFI_POLLING_INTERVAL))
      val wifiPollingCount = tlvReader.getUInt(ContextSpecificTag(TAG_WIFI_POLLING_COUNT))
      val usePolling = tlvReader.getBoolean(ContextSpecificTag(TAG_USE_POLLING))
      val reportVariables = tlvReader.getBoolean(ContextSpecificTag(TAG_REPORT_VARIABLES))
      val reportNetworkVariables = tlvReader.getBoolean(ContextSpecificTag(TAG_REPORT_NETWORK_VARIABLES))
      val reportMoreNetworkVariables = tlvReader.getBoolean(ContextSpecificTag(TAG_REPORT_MORE_NETWORK_VARIABLES))
      val reportWatermarkPercent = tlvReader.getUInt(ContextSpecificTag(TAG_REPORT_WATERMARK_PERCENT))
      
      tlvReader.exitContainer()

      return PhotonSmartClusterPhotonInsightsParamsStruct(coreDumpEnabled, minInterval, maxInterval, dropWifiLogs, reportMetrics, reportHeapMetrics, heapPollingInterval, heapPollingCount, reportWifiMetrics, wifiPollingInterval, wifiPollingCount, usePolling, reportVariables, reportNetworkVariables, reportMoreNetworkVariables, reportWatermarkPercent)
    }
  }
}

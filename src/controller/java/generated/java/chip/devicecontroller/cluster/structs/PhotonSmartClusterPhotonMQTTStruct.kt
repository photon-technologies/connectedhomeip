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
import matter.tlv.ContextSpecificTag
import matter.tlv.Tag
import matter.tlv.TlvReader
import matter.tlv.TlvWriter

class PhotonSmartClusterPhotonMQTTStruct(
  val host: String,
  val port: UInt,
  val transport: UInt,
  val keepAlive: UInt,
  val cleanSession: Boolean,
  val reconnectBackoffBaseMS: ULong,
  val timeoutMS: ULong,
  val sessionExpiryIntervalS: ULong,
  val maxPacketSize: ULong,
  val maxReceivePacketCount: UInt,
  val maxTopicAlias: UInt,
  val requestRespInfo: Boolean,
  val requestProblemInfo: Boolean,
  val willDelayIntervalS: ULong,
  val messageExpiryIntervalS: ULong,
  val payloadFormatIndicator: Boolean,
  val reconnectBackoffMaxMS: ULong,
  val bootJitterMaxMS: ULong,
) {
  override fun toString(): String = buildString {
    append("PhotonSmartClusterPhotonMQTTStruct {\n")
    append("\thost : $host\n")
    append("\tport : $port\n")
    append("\ttransport : $transport\n")
    append("\tkeepAlive : $keepAlive\n")
    append("\tcleanSession : $cleanSession\n")
    append("\treconnectBackoffBaseMS : $reconnectBackoffBaseMS\n")
    append("\ttimeoutMS : $timeoutMS\n")
    append("\tsessionExpiryIntervalS : $sessionExpiryIntervalS\n")
    append("\tmaxPacketSize : $maxPacketSize\n")
    append("\tmaxReceivePacketCount : $maxReceivePacketCount\n")
    append("\tmaxTopicAlias : $maxTopicAlias\n")
    append("\trequestRespInfo : $requestRespInfo\n")
    append("\trequestProblemInfo : $requestProblemInfo\n")
    append("\twillDelayIntervalS : $willDelayIntervalS\n")
    append("\tmessageExpiryIntervalS : $messageExpiryIntervalS\n")
    append("\tpayloadFormatIndicator : $payloadFormatIndicator\n")
    append("\treconnectBackoffMaxMS : $reconnectBackoffMaxMS\n")
    append("\tbootJitterMaxMS : $bootJitterMaxMS\n")
    append("}\n")
  }

  fun toTlv(tlvTag: Tag, tlvWriter: TlvWriter) {
    tlvWriter.apply {
      startStructure(tlvTag)
      put(ContextSpecificTag(TAG_HOST), host)
      put(ContextSpecificTag(TAG_PORT), port)
      put(ContextSpecificTag(TAG_TRANSPORT), transport)
      put(ContextSpecificTag(TAG_KEEP_ALIVE), keepAlive)
      put(ContextSpecificTag(TAG_CLEAN_SESSION), cleanSession)
      put(ContextSpecificTag(TAG_RECONNECT_BACKOFF_BASE_MS), reconnectBackoffBaseMS)
      put(ContextSpecificTag(TAG_TIMEOUT_MS), timeoutMS)
      put(ContextSpecificTag(TAG_SESSION_EXPIRY_INTERVAL_S), sessionExpiryIntervalS)
      put(ContextSpecificTag(TAG_MAX_PACKET_SIZE), maxPacketSize)
      put(ContextSpecificTag(TAG_MAX_RECEIVE_PACKET_COUNT), maxReceivePacketCount)
      put(ContextSpecificTag(TAG_MAX_TOPIC_ALIAS), maxTopicAlias)
      put(ContextSpecificTag(TAG_REQUEST_RESP_INFO), requestRespInfo)
      put(ContextSpecificTag(TAG_REQUEST_PROBLEM_INFO), requestProblemInfo)
      put(ContextSpecificTag(TAG_WILL_DELAY_INTERVAL_S), willDelayIntervalS)
      put(ContextSpecificTag(TAG_MESSAGE_EXPIRY_INTERVAL_S), messageExpiryIntervalS)
      put(ContextSpecificTag(TAG_PAYLOAD_FORMAT_INDICATOR), payloadFormatIndicator)
      put(ContextSpecificTag(TAG_RECONNECT_BACKOFF_MAX_MS), reconnectBackoffMaxMS)
      put(ContextSpecificTag(TAG_BOOT_JITTER_MAX_MS), bootJitterMaxMS)
      endStructure()
    }
  }

  companion object {
    private const val TAG_HOST = 1
    private const val TAG_PORT = 2
    private const val TAG_TRANSPORT = 3
    private const val TAG_KEEP_ALIVE = 4
    private const val TAG_CLEAN_SESSION = 5
    private const val TAG_RECONNECT_BACKOFF_BASE_MS = 6
    private const val TAG_TIMEOUT_MS = 7
    private const val TAG_SESSION_EXPIRY_INTERVAL_S = 9
    private const val TAG_MAX_PACKET_SIZE = 10
    private const val TAG_MAX_RECEIVE_PACKET_COUNT = 11
    private const val TAG_MAX_TOPIC_ALIAS = 12
    private const val TAG_REQUEST_RESP_INFO = 13
    private const val TAG_REQUEST_PROBLEM_INFO = 14
    private const val TAG_WILL_DELAY_INTERVAL_S = 15
    private const val TAG_MESSAGE_EXPIRY_INTERVAL_S = 16
    private const val TAG_PAYLOAD_FORMAT_INDICATOR = 17
    private const val TAG_RECONNECT_BACKOFF_MAX_MS = 18
    private const val TAG_BOOT_JITTER_MAX_MS = 19

    fun fromTlv(tlvTag: Tag, tlvReader: TlvReader): PhotonSmartClusterPhotonMQTTStruct {
      tlvReader.enterStructure(tlvTag)
      val host = tlvReader.getString(ContextSpecificTag(TAG_HOST))
      val port = tlvReader.getUInt(ContextSpecificTag(TAG_PORT))
      val transport = tlvReader.getUInt(ContextSpecificTag(TAG_TRANSPORT))
      val keepAlive = tlvReader.getUInt(ContextSpecificTag(TAG_KEEP_ALIVE))
      val cleanSession = tlvReader.getBoolean(ContextSpecificTag(TAG_CLEAN_SESSION))
      val reconnectBackoffBaseMS =
        tlvReader.getULong(ContextSpecificTag(TAG_RECONNECT_BACKOFF_BASE_MS))
      val timeoutMS = tlvReader.getULong(ContextSpecificTag(TAG_TIMEOUT_MS))
      val sessionExpiryIntervalS =
        tlvReader.getULong(ContextSpecificTag(TAG_SESSION_EXPIRY_INTERVAL_S))
      val maxPacketSize = tlvReader.getULong(ContextSpecificTag(TAG_MAX_PACKET_SIZE))
      val maxReceivePacketCount =
        tlvReader.getUInt(ContextSpecificTag(TAG_MAX_RECEIVE_PACKET_COUNT))
      val maxTopicAlias = tlvReader.getUInt(ContextSpecificTag(TAG_MAX_TOPIC_ALIAS))
      val requestRespInfo = tlvReader.getBoolean(ContextSpecificTag(TAG_REQUEST_RESP_INFO))
      val requestProblemInfo = tlvReader.getBoolean(ContextSpecificTag(TAG_REQUEST_PROBLEM_INFO))
      val willDelayIntervalS = tlvReader.getULong(ContextSpecificTag(TAG_WILL_DELAY_INTERVAL_S))
      val messageExpiryIntervalS =
        tlvReader.getULong(ContextSpecificTag(TAG_MESSAGE_EXPIRY_INTERVAL_S))
      val payloadFormatIndicator =
        tlvReader.getBoolean(ContextSpecificTag(TAG_PAYLOAD_FORMAT_INDICATOR))
      val reconnectBackoffMaxMS =
        tlvReader.getULong(ContextSpecificTag(TAG_RECONNECT_BACKOFF_MAX_MS))
      val bootJitterMaxMS = tlvReader.getULong(ContextSpecificTag(TAG_BOOT_JITTER_MAX_MS))

      tlvReader.exitContainer()

      return PhotonSmartClusterPhotonMQTTStruct(
        host,
        port,
        transport,
        keepAlive,
        cleanSession,
        reconnectBackoffBaseMS,
        timeoutMS,
        sessionExpiryIntervalS,
        maxPacketSize,
        maxReceivePacketCount,
        maxTopicAlias,
        requestRespInfo,
        requestProblemInfo,
        willDelayIntervalS,
        messageExpiryIntervalS,
        payloadFormatIndicator,
        reconnectBackoffMaxMS,
        bootJitterMaxMS,
      )
    }
  }
}

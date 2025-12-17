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
package matter.controller.cluster.structs

import matter.controller.cluster.*
import matter.tlv.ContextSpecificTag
import matter.tlv.Tag
import matter.tlv.TlvReader
import matter.tlv.TlvWriter

class PhotonSmartClusterPhotonMQTTStruct(
  val host: String,
  val port: UShort,
  val transport: UByte,
  val keepAlive: UShort,
  val cleanSession: Boolean,
  val reconnectTimeoutMS: UInt,
  val timeoutMS: UInt,
  val refreshConnectionAfterMS: UInt,
  val sessionExpiryIntervalS: UInt,
  val maxPacketSize: UInt,
  val maxReceivePacketCount: UShort,
  val maxTopicAlias: UShort,
  val requestRespInfo: Boolean,
  val requestProblemInfo: Boolean,
  val willDelayIntervalS: UInt,
  val messageExpiryIntervalS: UInt,
  val payloadFormatIndicator: Boolean,
) {
  override fun toString(): String = buildString {
    append("PhotonSmartClusterPhotonMQTTStruct {\n")
    append("\thost : $host\n")
    append("\tport : $port\n")
    append("\ttransport : $transport\n")
    append("\tkeepAlive : $keepAlive\n")
    append("\tcleanSession : $cleanSession\n")
    append("\treconnectTimeoutMS : $reconnectTimeoutMS\n")
    append("\ttimeoutMS : $timeoutMS\n")
    append("\trefreshConnectionAfterMS : $refreshConnectionAfterMS\n")
    append("\tsessionExpiryIntervalS : $sessionExpiryIntervalS\n")
    append("\tmaxPacketSize : $maxPacketSize\n")
    append("\tmaxReceivePacketCount : $maxReceivePacketCount\n")
    append("\tmaxTopicAlias : $maxTopicAlias\n")
    append("\trequestRespInfo : $requestRespInfo\n")
    append("\trequestProblemInfo : $requestProblemInfo\n")
    append("\twillDelayIntervalS : $willDelayIntervalS\n")
    append("\tmessageExpiryIntervalS : $messageExpiryIntervalS\n")
    append("\tpayloadFormatIndicator : $payloadFormatIndicator\n")
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
      put(ContextSpecificTag(TAG_RECONNECT_TIMEOUT_MS), reconnectTimeoutMS)
      put(ContextSpecificTag(TAG_TIMEOUT_MS), timeoutMS)
      put(ContextSpecificTag(TAG_REFRESH_CONNECTION_AFTER_MS), refreshConnectionAfterMS)
      put(ContextSpecificTag(TAG_SESSION_EXPIRY_INTERVAL_S), sessionExpiryIntervalS)
      put(ContextSpecificTag(TAG_MAX_PACKET_SIZE), maxPacketSize)
      put(ContextSpecificTag(TAG_MAX_RECEIVE_PACKET_COUNT), maxReceivePacketCount)
      put(ContextSpecificTag(TAG_MAX_TOPIC_ALIAS), maxTopicAlias)
      put(ContextSpecificTag(TAG_REQUEST_RESP_INFO), requestRespInfo)
      put(ContextSpecificTag(TAG_REQUEST_PROBLEM_INFO), requestProblemInfo)
      put(ContextSpecificTag(TAG_WILL_DELAY_INTERVAL_S), willDelayIntervalS)
      put(ContextSpecificTag(TAG_MESSAGE_EXPIRY_INTERVAL_S), messageExpiryIntervalS)
      put(ContextSpecificTag(TAG_PAYLOAD_FORMAT_INDICATOR), payloadFormatIndicator)
      endStructure()
    }
  }

  companion object {
    private const val TAG_HOST = 1
    private const val TAG_PORT = 2
    private const val TAG_TRANSPORT = 3
    private const val TAG_KEEP_ALIVE = 4
    private const val TAG_CLEAN_SESSION = 5
    private const val TAG_RECONNECT_TIMEOUT_MS = 6
    private const val TAG_TIMEOUT_MS = 7
    private const val TAG_REFRESH_CONNECTION_AFTER_MS = 8
    private const val TAG_SESSION_EXPIRY_INTERVAL_S = 9
    private const val TAG_MAX_PACKET_SIZE = 10
    private const val TAG_MAX_RECEIVE_PACKET_COUNT = 11
    private const val TAG_MAX_TOPIC_ALIAS = 12
    private const val TAG_REQUEST_RESP_INFO = 13
    private const val TAG_REQUEST_PROBLEM_INFO = 14
    private const val TAG_WILL_DELAY_INTERVAL_S = 15
    private const val TAG_MESSAGE_EXPIRY_INTERVAL_S = 16
    private const val TAG_PAYLOAD_FORMAT_INDICATOR = 17

    fun fromTlv(tlvTag: Tag, tlvReader: TlvReader): PhotonSmartClusterPhotonMQTTStruct {
      tlvReader.enterStructure(tlvTag)
      val host = tlvReader.getString(ContextSpecificTag(TAG_HOST))
      val port = tlvReader.getUShort(ContextSpecificTag(TAG_PORT))
      val transport = tlvReader.getUByte(ContextSpecificTag(TAG_TRANSPORT))
      val keepAlive = tlvReader.getUShort(ContextSpecificTag(TAG_KEEP_ALIVE))
      val cleanSession = tlvReader.getBoolean(ContextSpecificTag(TAG_CLEAN_SESSION))
      val reconnectTimeoutMS = tlvReader.getUInt(ContextSpecificTag(TAG_RECONNECT_TIMEOUT_MS))
      val timeoutMS = tlvReader.getUInt(ContextSpecificTag(TAG_TIMEOUT_MS))
      val refreshConnectionAfterMS =
        tlvReader.getUInt(ContextSpecificTag(TAG_REFRESH_CONNECTION_AFTER_MS))
      val sessionExpiryIntervalS =
        tlvReader.getUInt(ContextSpecificTag(TAG_SESSION_EXPIRY_INTERVAL_S))
      val maxPacketSize = tlvReader.getUInt(ContextSpecificTag(TAG_MAX_PACKET_SIZE))
      val maxReceivePacketCount =
        tlvReader.getUShort(ContextSpecificTag(TAG_MAX_RECEIVE_PACKET_COUNT))
      val maxTopicAlias = tlvReader.getUShort(ContextSpecificTag(TAG_MAX_TOPIC_ALIAS))
      val requestRespInfo = tlvReader.getBoolean(ContextSpecificTag(TAG_REQUEST_RESP_INFO))
      val requestProblemInfo = tlvReader.getBoolean(ContextSpecificTag(TAG_REQUEST_PROBLEM_INFO))
      val willDelayIntervalS = tlvReader.getUInt(ContextSpecificTag(TAG_WILL_DELAY_INTERVAL_S))
      val messageExpiryIntervalS =
        tlvReader.getUInt(ContextSpecificTag(TAG_MESSAGE_EXPIRY_INTERVAL_S))
      val payloadFormatIndicator =
        tlvReader.getBoolean(ContextSpecificTag(TAG_PAYLOAD_FORMAT_INDICATOR))

      tlvReader.exitContainer()

      return PhotonSmartClusterPhotonMQTTStruct(
        host,
        port,
        transport,
        keepAlive,
        cleanSession,
        reconnectTimeoutMS,
        timeoutMS,
        refreshConnectionAfterMS,
        sessionExpiryIntervalS,
        maxPacketSize,
        maxReceivePacketCount,
        maxTopicAlias,
        requestRespInfo,
        requestProblemInfo,
        willDelayIntervalS,
        messageExpiryIntervalS,
        payloadFormatIndicator,
      )
    }
  }
}

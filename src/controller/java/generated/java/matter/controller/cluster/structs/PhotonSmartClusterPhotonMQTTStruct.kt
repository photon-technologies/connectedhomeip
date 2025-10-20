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
  val lastWillTopic: String,
  val lastWillMsg: ByteArray,
  val lastWillMsgLen: UShort,
  val lastWillQOS: UByte,
  val lastWillRetain: Boolean,
  val cleanSession: Boolean,
  val reconnectTimeoutMS: UInt,
  val timeoutMS: UInt,
  val refreshConnectionAfterMS: UInt,
  val replyTo: String,
) {
  override fun toString(): String = buildString {
    append("PhotonSmartClusterPhotonMQTTStruct {\n")
    append("\thost : $host\n")
    append("\tport : $port\n")
    append("\ttransport : $transport\n")
    append("\tkeepAlive : $keepAlive\n")
    append("\tlastWillTopic : $lastWillTopic\n")
    append("\tlastWillMsg : $lastWillMsg\n")
    append("\tlastWillMsgLen : $lastWillMsgLen\n")
    append("\tlastWillQOS : $lastWillQOS\n")
    append("\tlastWillRetain : $lastWillRetain\n")
    append("\tcleanSession : $cleanSession\n")
    append("\treconnectTimeoutMS : $reconnectTimeoutMS\n")
    append("\ttimeoutMS : $timeoutMS\n")
    append("\trefreshConnectionAfterMS : $refreshConnectionAfterMS\n")
    append("\treplyTo : $replyTo\n")
    append("}\n")
  }

  fun toTlv(tlvTag: Tag, tlvWriter: TlvWriter) {
    tlvWriter.apply {
      startStructure(tlvTag)
      put(ContextSpecificTag(TAG_HOST), host)
      put(ContextSpecificTag(TAG_PORT), port)
      put(ContextSpecificTag(TAG_TRANSPORT), transport)
      put(ContextSpecificTag(TAG_KEEP_ALIVE), keepAlive)
      put(ContextSpecificTag(TAG_LAST_WILL_TOPIC), lastWillTopic)
      put(ContextSpecificTag(TAG_LAST_WILL_MSG), lastWillMsg)
      put(ContextSpecificTag(TAG_LAST_WILL_MSG_LEN), lastWillMsgLen)
      put(ContextSpecificTag(TAG_LAST_WILL_QOS), lastWillQOS)
      put(ContextSpecificTag(TAG_LAST_WILL_RETAIN), lastWillRetain)
      put(ContextSpecificTag(TAG_CLEAN_SESSION), cleanSession)
      put(ContextSpecificTag(TAG_RECONNECT_TIMEOUT_MS), reconnectTimeoutMS)
      put(ContextSpecificTag(TAG_TIMEOUT_MS), timeoutMS)
      put(ContextSpecificTag(TAG_REFRESH_CONNECTION_AFTER_MS), refreshConnectionAfterMS)
      put(ContextSpecificTag(TAG_REPLY_TO), replyTo)
      endStructure()
    }
  }

  companion object {
    private const val TAG_HOST = 1
    private const val TAG_PORT = 2
    private const val TAG_TRANSPORT = 3
    private const val TAG_KEEP_ALIVE = 4
    private const val TAG_LAST_WILL_TOPIC = 5
    private const val TAG_LAST_WILL_MSG = 6
    private const val TAG_LAST_WILL_MSG_LEN = 7
    private const val TAG_LAST_WILL_QOS = 8
    private const val TAG_LAST_WILL_RETAIN = 9
    private const val TAG_CLEAN_SESSION = 10
    private const val TAG_RECONNECT_TIMEOUT_MS = 11
    private const val TAG_TIMEOUT_MS = 12
    private const val TAG_REFRESH_CONNECTION_AFTER_MS = 13
    private const val TAG_REPLY_TO = 14

    fun fromTlv(tlvTag: Tag, tlvReader: TlvReader): PhotonSmartClusterPhotonMQTTStruct {
      tlvReader.enterStructure(tlvTag)
      val host = tlvReader.getString(ContextSpecificTag(TAG_HOST))
      val port = tlvReader.getUShort(ContextSpecificTag(TAG_PORT))
      val transport = tlvReader.getUByte(ContextSpecificTag(TAG_TRANSPORT))
      val keepAlive = tlvReader.getUShort(ContextSpecificTag(TAG_KEEP_ALIVE))
      val lastWillTopic = tlvReader.getString(ContextSpecificTag(TAG_LAST_WILL_TOPIC))
      val lastWillMsg = tlvReader.getByteArray(ContextSpecificTag(TAG_LAST_WILL_MSG))
      val lastWillMsgLen = tlvReader.getUShort(ContextSpecificTag(TAG_LAST_WILL_MSG_LEN))
      val lastWillQOS = tlvReader.getUByte(ContextSpecificTag(TAG_LAST_WILL_QOS))
      val lastWillRetain = tlvReader.getBoolean(ContextSpecificTag(TAG_LAST_WILL_RETAIN))
      val cleanSession = tlvReader.getBoolean(ContextSpecificTag(TAG_CLEAN_SESSION))
      val reconnectTimeoutMS = tlvReader.getUInt(ContextSpecificTag(TAG_RECONNECT_TIMEOUT_MS))
      val timeoutMS = tlvReader.getUInt(ContextSpecificTag(TAG_TIMEOUT_MS))
      val refreshConnectionAfterMS =
        tlvReader.getUInt(ContextSpecificTag(TAG_REFRESH_CONNECTION_AFTER_MS))
      val replyTo = tlvReader.getString(ContextSpecificTag(TAG_REPLY_TO))

      tlvReader.exitContainer()

      return PhotonSmartClusterPhotonMQTTStruct(
        host,
        port,
        transport,
        keepAlive,
        lastWillTopic,
        lastWillMsg,
        lastWillMsgLen,
        lastWillQOS,
        lastWillRetain,
        cleanSession,
        reconnectTimeoutMS,
        timeoutMS,
        refreshConnectionAfterMS,
        replyTo,
      )
    }
  }
}

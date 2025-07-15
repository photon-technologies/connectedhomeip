//
// Created by Mark Ragaee on 13/07/2025.
//

#include "ReadTlv.h"

#include <jni.h>
#include <lib/support/CHIPMem.h>
#include <lib/support/CodeUtils.h>
#include <lib/support/logging/CHIPLogging.h>

#define JNI_METHOD(RETURN, CLASS_NAME, METHOD_NAME)                                                                                \
extern "C" JNIEXPORT RETURN JNICALL Java_chip_devicecontroller_##CLASS_NAME##_##METHOD_NAME


JNI_METHOD(void, ReadTlvJni, readReportData)
(JNIEnv * env, jobject self, jbyteArray byteArrayJava)
{
    readReportData(env, self, byteArrayJava, "()Lchip/devicecontroller/model/NodeState;");
}
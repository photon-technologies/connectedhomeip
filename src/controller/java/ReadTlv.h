//
// Created by Mark Ragaee on 13/07/2025.
//
#include <app/AttributePathParams.h>
#include <app/ConcreteAttributePath.h>
#include <app/EventHeader.h>
#include <app/EventPathParams.h>
#include <app/MessageDef/ReadRequestMessage.h>
#include <app/MessageDef/StatusIB.h>
#include <app/MessageDef/StatusResponseMessage.h>
#include <app/MessageDef/SubscribeRequestMessage.h>
#include <app/MessageDef/SubscribeResponseMessage.h>
#include <lib/core/CHIPCore.h>
#include <lib/core/TLVDebug.h>
#include <lib/support/CodeUtils.h>
#include <app/InteractionModelEngine.h>
#include <jni.h>
#include <lib/support/CHIPJNIError.h>
#include <lib/support/JniReferences.h>
#include <lib/support/JniTypeWrappers.h>

using namespace chip;
using namespace chip::app;

class ReadTlv {
    public:
        ReadTlv(jobject wrapperCallback, const char * nodeStateClassSignature);
        ~ReadTlv() = default;
        CHIP_ERROR ProcessReportData(uint8_t *aPayload, size_t aSize);
        CHIP_ERROR ProcessAttributeReportIBs(TLV::TLVReader & aAttributeDataIBsReader);
        CHIP_ERROR ProcessEventReportIBs(TLV::TLVReader & aEventReportIBsReader);
        CHIP_ERROR ProcessAttributePath(AttributePathIB::Parser & aAttributePath, ConcreteDataAttributePath & aClusterInfo);

        void OnAttributeData(const app::ConcreteDataAttributePath & aPath, TLV::TLVReader * apData,
                             const app::StatusIB & aStatus);
        void OnEventData(const app::EventHeader & aEventHeader, TLV::TLVReader * apData, const app::StatusIB * apStatus);
        void UpdateClusterDataVersion();

        const char * mNodeStateClassSignature;
        JniGlobalReference mWrapperCallbackRef;
        Timestamp mEventTimestamp;
};

void readReportData(JNIEnv * env, jobject self, jbyteArray byteArrayJava, const char * nodeStateClassSignature);

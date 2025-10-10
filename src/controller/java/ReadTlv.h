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
#include <app/ClusterStateCache.h>
#include <jni.h>
#include <lib/support/CHIPJNIError.h>
#include <lib/support/JniReferences.h>
#include <lib/support/JniTypeWrappers.h>

class ReadTlv {
    public:
        ReadTlv(jobject wrapperCallback, const char * nodeStateClassSignature);
        ~ReadTlv() = default;
        CHIP_ERROR ProcessReportData(uint8_t *aPayload, size_t aSize);
        CHIP_ERROR ProcessAttributeReportIBs(chip::TLV::TLVReader & aAttributeDataIBsReader);
        CHIP_ERROR ProcessEventReportIBs(chip::TLV::TLVReader & aEventReportIBsReader);
        CHIP_ERROR ProcessAttributePath(chip::app::AttributePathIB::Parser & aAttributePath, chip::app::ConcreteDataAttributePath & aClusterInfo);

        void OnAttributeData(const chip::app::ConcreteDataAttributePath & aPath, chip::TLV::TLVReader * apData,
                             const chip::app::StatusIB & aStatus, chip::DataVersion & version);
        void OnEventData(const chip::app::EventHeader & aEventHeader, chip::TLV::TLVReader * apData, const chip::app::StatusIB * apStatus);
        void UpdateClusterDataVersion();

        // chip::app::ClusterStateCache mClusterCacheAdapter;
        chip::JniGlobalReference mWrapperCallbackRef;
        chip::app::Timestamp mEventTimestamp;
        const char * mNodeStateClassSignature;
};

void readReportData(JNIEnv * env, jobject self, jbyteArray byteArrayJava, const char * nodeStateClassSignature);

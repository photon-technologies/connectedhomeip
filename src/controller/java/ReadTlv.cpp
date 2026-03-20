//
// Created by Mark Ragaee on 13/07/2025.
//

#include "ReadTlv.h"
#include <jni.h>
#ifdef USE_JAVA_TLV_ENCODE_DECODE
#include <controller/java/CHIPAttributeTLVValueDecoder.h>
#include <controller/java/CHIPEventTLVValueDecoder.h>
#endif
#include <lib/support/jsontlv/JsonToTlv.h>
#include <lib/support/jsontlv/TlvToJson.h>
#include <string>
#include <type_traits>

using namespace chip;
using namespace chip::app;

static const int MILLIS_SINCE_BOOT  = 0;
static const int MILLIS_SINCE_EPOCH = 1;
// Add the bytes for attribute tag(1:control + 8:tag + 8:length) and structure(1:struct + 1:close container)
static const int EXTRA_SPACE_FOR_ATTRIBUTE_TAG = 19;

ReadTlv::ReadTlv(jobject wrapperCallback, const char * nodeStateClassSignature) :
    // mClusterCacheAdapter(*this, Optional<EventNumber>::Missing(), false /*cacheData*/),
    mNodeStateClassSignature(nodeStateClassSignature)
{
    JNIEnv * env = JniReferences::GetInstance().GetEnvForCurrentThread();
    VerifyOrReturn(env != nullptr, ChipLogError(Controller, "Could not get JNIEnv for current thread"));

    VerifyOrReturn(mWrapperCallbackRef.Init(wrapperCallback) == CHIP_NO_ERROR,
                   ChipLogError(Controller, "Could not init mWrapperCallbackRef in %s", __func__));
}

CHIP_ERROR ReadTlv::ProcessAttributePath(AttributePathIB::Parser & aAttributePathParser,
                                            ConcreteDataAttributePath & aAttributePath)
{
    // The ReportData must contain a concrete attribute path.  Don't validate ID
    // ranges here, so we can tell apart "malformed data" and "out of range
    // IDs".
    CHIP_ERROR err = CHIP_NO_ERROR;
    // The ReportData must contain a concrete attribute path
    err = aAttributePathParser.GetConcreteAttributePath(aAttributePath, AttributePathIB::ValidateIdRanges::kNo);
    VerifyOrReturnError(err == CHIP_NO_ERROR, CHIP_ERROR_IM_MALFORMED_ATTRIBUTE_PATH_IB);
    return CHIP_NO_ERROR;
}

// Convert TLV blob to Json with structure, the element's tag is replaced with the actual attributeId.
CHIP_ERROR ConvertReportTlvToJson(const uint32_t id, TLV::TLVReader & data, std::string & json)
{
    TLV::TLVWriter writer;
    TLV::TLVReader readerForJavaTLV;
    uint32_t size = 0;
    readerForJavaTLV.Init(data);
    size_t bufferLen                  = readerForJavaTLV.GetTotalLength() + EXTRA_SPACE_FOR_ATTRIBUTE_TAG;
    std::unique_ptr<uint8_t[]> buffer = std::unique_ptr<uint8_t[]>(new uint8_t[bufferLen]);
    writer.Init(buffer.get(), bufferLen);
    TLV::TLVType outer;

    ReturnErrorOnFailure(writer.StartContainer(TLV::AnonymousTag(), TLV::kTLVType_Structure, outer));
    TLV::Tag tag;
    ReturnErrorOnFailure(ConvertTlvTag(id, tag));
    ReturnErrorOnFailure(writer.CopyElement(tag, readerForJavaTLV));
    ReturnErrorOnFailure(writer.EndContainer(outer));
    size = writer.GetLengthWritten();

    TLV::TLVReader readerForJson;
    readerForJson.Init(buffer.get(), size);
    ReturnErrorOnFailure(readerForJson.Next());
    // Convert TLV to JSON
    return TlvToJson(readerForJson, json);
}

jobject GetNodeStateObj(JNIEnv * env, const char * nodeStateClassSignature, jobject wrapperCallback)
{
    jmethodID getNodeStateMethod;
    CHIP_ERROR err =
        JniReferences::GetInstance().FindMethod(env, wrapperCallback, "getNodeState", nodeStateClassSignature, &getNodeStateMethod);
    VerifyOrReturnValue(err == CHIP_NO_ERROR, nullptr, ChipLogError(Controller, "Could not find getNodeState method"));

    jobject ret = env->CallObjectMethod(wrapperCallback, getNodeStateMethod);
    VerifyOrReturnValue(!env->ExceptionCheck(), nullptr, env->ExceptionDescribe());

    return ret;
}

jobject DecodeGeneralTLVValue(JNIEnv * env, TLV::TLVReader & readerForGeneralValueObject, CHIP_ERROR & err)
{
    jobject retValue = nullptr;

    switch (readerForGeneralValueObject.GetType())
    {
    case TLV::kTLVType_SignedInteger: {
        int64_t signedValue = 0;
        VerifyOrReturnValue(readerForGeneralValueObject.Get(signedValue) == CHIP_NO_ERROR, nullptr,
                            ChipLogProgress(Controller, "Get TLV Value fail!"));
        err = JniReferences::GetInstance().CreateBoxedObject<jlong>("java/lang/Long", "(J)V", static_cast<jlong>(signedValue),
                                                                    retValue);
        VerifyOrReturnValue(err == CHIP_NO_ERROR, nullptr, ChipLogProgress(Controller, "Create Boxed Object fail!"));
        return retValue;
    }
    case TLV::kTLVType_UnsignedInteger: {
        uint64_t unsignedValue = 0;
        VerifyOrReturnValue(readerForGeneralValueObject.Get(unsignedValue) == CHIP_NO_ERROR, nullptr,
                            ChipLogProgress(Controller, "Get TLV Value fail!"));
        err = JniReferences::GetInstance().CreateBoxedObject<jlong>("java/lang/Long", "(J)V", static_cast<jlong>(unsignedValue),
                                                                    retValue);
        VerifyOrReturnValue(err == CHIP_NO_ERROR, nullptr, ChipLogProgress(Controller, "Create Boxed Object fail!"));
        return retValue;
    }
    case TLV::kTLVType_Boolean: {
        bool booleanValue = false;
        VerifyOrReturnValue(readerForGeneralValueObject.Get(booleanValue) == CHIP_NO_ERROR, nullptr,
                            ChipLogProgress(Controller, "Get TLV Value fail!"));
        err = JniReferences::GetInstance().CreateBoxedObject<jboolean>("java/lang/Boolean", "(Z)V",
                                                                       static_cast<jboolean>(booleanValue), retValue);
        VerifyOrReturnValue(err == CHIP_NO_ERROR, nullptr, ChipLogProgress(Controller, "Create Boxed Object fail!"));
        return retValue;
    }
    case TLV::kTLVType_FloatingPointNumber: {
        double doubleValue = 0.0;
        VerifyOrReturnValue(readerForGeneralValueObject.Get(doubleValue) == CHIP_NO_ERROR, nullptr,
                            ChipLogProgress(Controller, "Get TLV Value fail!"));
        err = JniReferences::GetInstance().CreateBoxedObject<jdouble>("java/lang/Double", "(D)V", static_cast<jdouble>(doubleValue),
                                                                      retValue);
        VerifyOrReturnValue(err == CHIP_NO_ERROR, nullptr, ChipLogProgress(Controller, "Create Boxed Object fail!"));
        return retValue;
    }
    case TLV::kTLVType_UTF8String: {
        uint32_t bufferLen             = readerForGeneralValueObject.GetLength();
        std::unique_ptr<char[]> buffer = std::unique_ptr<char[]>(new char[bufferLen + 1]);
        err                            = readerForGeneralValueObject.GetString(buffer.get(), bufferLen + 1);
        VerifyOrReturnValue(err == CHIP_NO_ERROR, nullptr, ChipLogProgress(Controller, "Get TLV Value fail!"));
        chip::CharSpan valueSpan(buffer.get(), bufferLen);
        chip::JniReferences::GetInstance().CharToStringUTF(valueSpan, retValue);
        return retValue;
    }
    case TLV::kTLVType_ByteString: {
        uint32_t bufferLen                = readerForGeneralValueObject.GetLength();
        std::unique_ptr<uint8_t[]> buffer = std::unique_ptr<uint8_t[]>(new uint8_t[bufferLen + 1]);
        err                               = readerForGeneralValueObject.GetBytes(buffer.get(), bufferLen + 1);
        VerifyOrReturnValue(err == CHIP_NO_ERROR, nullptr, ChipLogProgress(Controller, "Get TLV Value fail!"));

        jbyteArray valueByteArray = env->NewByteArray(static_cast<jsize>(bufferLen));
        env->SetByteArrayRegion(valueByteArray, 0, static_cast<jsize>(bufferLen), reinterpret_cast<const jbyte *>(buffer.get()));

        return static_cast<jobject>(valueByteArray);
    }
    case TLV::kTLVType_Array: {
        TLV::TLVType containerType;
        err = readerForGeneralValueObject.EnterContainer(containerType);
        VerifyOrReturnValue(err == CHIP_NO_ERROR, nullptr,
                            ChipLogProgress(Controller, "EnterContainer fail! : %" CHIP_ERROR_FORMAT, err.Format()));
        err = chip::JniReferences::GetInstance().CreateArrayList(retValue);
        VerifyOrReturnValue(err == CHIP_NO_ERROR, nullptr,
                            ChipLogProgress(Controller, "CreateArrayList fail! : %" CHIP_ERROR_FORMAT, err.Format()));
        while (readerForGeneralValueObject.Next() == CHIP_NO_ERROR)
        {
            jobject inValue = DecodeGeneralTLVValue(env, readerForGeneralValueObject, err);
            VerifyOrReturnValue(err == CHIP_NO_ERROR, nullptr,
                                ChipLogProgress(Controller, "Can't parse general value : %" CHIP_ERROR_FORMAT, err.Format()));
            err = chip::JniReferences::GetInstance().AddToList(retValue, inValue);
        }
        return retValue;
    }
    case TLV::kTLVType_List: {
        TLV::TLVType containerType;
        err = readerForGeneralValueObject.EnterContainer(containerType);
        VerifyOrReturnValue(err == CHIP_NO_ERROR, nullptr,
                            ChipLogProgress(Controller, "EnterContainer fail! : %" CHIP_ERROR_FORMAT, err.Format()));
        err = chip::JniReferences::GetInstance().CreateArrayList(retValue);
        VerifyOrReturnValue(err == CHIP_NO_ERROR, nullptr,
                            ChipLogProgress(Controller, "CreateArrayList fail! : %" CHIP_ERROR_FORMAT, err.Format()));
        while (readerForGeneralValueObject.Next() == CHIP_NO_ERROR)
        {
            jobject inValue = DecodeGeneralTLVValue(env, readerForGeneralValueObject, err);
            VerifyOrReturnValue(err == CHIP_NO_ERROR, nullptr,
                                ChipLogProgress(Controller, "Can't parse general value : %" CHIP_ERROR_FORMAT, err.Format()));
            err = chip::JniReferences::GetInstance().AddToList(retValue, inValue);
        }
        return retValue;
    }
    case TLV::kTLVType_Null: {
        return nullptr;
    }
    default:
        err = CHIP_ERROR_WRONG_TLV_TYPE;
        return nullptr;
    }
}

void ReadTlv::UpdateClusterDataVersion()
{
//    JNIEnv * env = JniReferences::GetInstance().GetEnvForCurrentThread();
//    VerifyOrReturn(env != nullptr, ChipLogError(Controller, "Could not get JNIEnv for current thread"));
//    chip::app::ConcreteClusterPath lastConcreteClusterPath;

//    if (!lastConcreteClusterPath.IsValidConcreteClusterPath())
//    {
//        return;
//    }

//    VerifyOrReturn(mWrapperCallbackRef.HasValidObjectRef(),
//                   ChipLogError(Controller, "mReportCallbackRef is not valid in %s", __func__));
//    jobject wrapperCallback = mWrapperCallbackRef.ObjectRef();
//    jobject nodeState       = GetNodeStateObj(env, mNodeStateClassSignature, wrapperCallback);

//    // SetDataVersion to NodeState
//    jmethodID setDataVersionMethod;
//    CHIP_ERROR err = JniReferences::GetInstance().FindMethod(env, nodeState, "setDataVersion", "(IJJ)V", &setDataVersionMethod);
//    VerifyOrReturn(err == CHIP_NO_ERROR, ChipLogError(Controller, "Could not find setDataVersion method"));
//    env->CallVoidMethod(nodeState, setDataVersionMethod, static_cast<jint>(lastConcreteClusterPath.mEndpointId),
//                        static_cast<jlong>(lastConcreteClusterPath.mClusterId), static_cast<jlong>(committedDataVersion.Value()));
//    VerifyOrReturn(!env->ExceptionCheck(), env->ExceptionDescribe());
}

void ReadTlv::OnAttributeData(const app::ConcreteDataAttributePath & aPath, TLV::TLVReader * apData,
                                     const app::StatusIB & aStatus, DataVersion & version)
{
    DeviceLayer::StackUnlock unlock;
    CHIP_ERROR err = CHIP_NO_ERROR;
    JNIEnv * env   = JniReferences::GetInstance().GetEnvForCurrentThread();
    VerifyOrReturn(env != nullptr, ChipLogError(Controller, "Could not get JNIEnv for current thread"));
    JniLocalReferenceScope scope(env);
    VerifyOrReturn(!aPath.IsListItemOperation(), ChipLogError(Controller, "Expect non-list item operation"); aPath.LogPath());

    VerifyOrReturn(mWrapperCallbackRef.HasValidObjectRef(),
                   ChipLogError(Controller, "mReportCallbackRef is not valid in %s", __func__));
    jobject wrapperCallback = mWrapperCallbackRef.ObjectRef();

    jobject nodeState = GetNodeStateObj(env, mNodeStateClassSignature, wrapperCallback);

    {
        // Add Attribute Status to wrapperCallback
        jmethodID addAttributeStatusMethod = nullptr;
        err = JniReferences::GetInstance().FindMethod(env, nodeState, "addAttributeStatus", "(IJJILjava/lang/Integer;)V",
                                                      &addAttributeStatusMethod);
        VerifyOrReturn(
            err == CHIP_NO_ERROR,
            ChipLogError(Controller, "Could not find addAttributeStatus method with error %" CHIP_ERROR_FORMAT, err.Format()));

        jobject jClusterState = nullptr;
        if (aStatus.mClusterStatus.has_value())
        {
            err = JniReferences::GetInstance().CreateBoxedObject<jint>("java/lang/Integer", "(I)V",
                                                                       static_cast<jint>(*aStatus.mClusterStatus), jClusterState);
            VerifyOrReturn(err == CHIP_NO_ERROR,
                           ChipLogError(Controller, "Could not CreateBoxedObject with error %" CHIP_ERROR_FORMAT, err.Format()));
        }

        env->CallVoidMethod(nodeState, addAttributeStatusMethod, static_cast<jint>(aPath.mEndpointId),
                            static_cast<jlong>(aPath.mClusterId), static_cast<jlong>(aPath.mAttributeId),
                            static_cast<jint>(aStatus.mStatus), jClusterState);
        VerifyOrReturn(!env->ExceptionCheck(), env->ExceptionDescribe());
    }

    VerifyOrReturn(aStatus.IsSuccess(), ChipLogError(Controller, "Receive bad status %s", ErrorStr(aStatus.ToChipError()));
                   aPath.LogPath());
    VerifyOrReturn(apData != nullptr, ChipLogError(Controller, "Receive empty apData"); aPath.LogPath());

    TLV::TLVReader readerForJavaTLV;
    readerForJavaTLV.Init(*apData);

    jobject value = nullptr;
    TLV::TLVReader readerForJavaObject;
    readerForJavaObject.Init(*apData);
#ifdef USE_JAVA_TLV_ENCODE_DECODE
    value = DecodeAttributeValue(aPath, readerForJavaObject, &err);
    // If we don't know this attribute, suppress it.
    if (err == CHIP_ERROR_IM_MALFORMED_ATTRIBUTE_PATH_IB)
    {
        TLV::TLVReader readerForGeneralValueObject;
        readerForGeneralValueObject.Init(*apData);
        value = DecodeGeneralTLVValue(env, readerForGeneralValueObject, err);
        err   = CHIP_NO_ERROR;
    }

    VerifyOrReturn(err == CHIP_NO_ERROR, ChipLogError(Controller, "Fail to decode attribute with error %s", ErrorStr(err));
                   aPath.LogPath());
    VerifyOrReturn(!env->ExceptionCheck(), env->ExceptionDescribe());
#else
    value = DecodeGeneralTLVValue(env, readerForJavaObject, err);
#endif
    // Create TLV byte array to pass to Java layer
    size_t bufferLen                  = readerForJavaTLV.GetRemainingLength() + readerForJavaTLV.GetLengthRead();
    std::unique_ptr<uint8_t[]> buffer = std::unique_ptr<uint8_t[]>(new uint8_t[bufferLen]);
    uint32_t size                     = 0;

    // The TLVReader's read head is not pointing to the first element in the container, instead of the container itself, use
    // a TLVWriter to get a TLV with a normalized TLV buffer (Wrapped with an anonymous tag, no extra "end of container" tag
    // at the end.)
    TLV::TLVWriter writer;
    writer.Init(buffer.get(), bufferLen);
    err = writer.CopyElement(TLV::AnonymousTag(), readerForJavaTLV);
    VerifyOrReturn(err == CHIP_NO_ERROR, ChipLogError(Controller, "Fail to copy tlv element with error %s", ErrorStr(err));
                   aPath.LogPath());
    size = writer.GetLengthWritten();
    chip::ByteArray jniByteArray(env, reinterpret_cast<jbyte *>(buffer.get()), static_cast<jint>(size));

    // Convert TLV to JSON
    std::string json;
    err = ConvertReportTlvToJson(static_cast<uint32_t>(aPath.mAttributeId), *apData, json);
    VerifyOrReturn(err == CHIP_NO_ERROR,
                   ChipLogError(Controller, "Fail to convert report tlv to json with error %s", ErrorStr(err));
                   aPath.LogPath());
    UtfString jsonString(env, json.c_str());

    // Add AttributeState to wrapperCallback
    jmethodID addAttributeMethod;
    err = JniReferences::GetInstance().FindMethod(env, nodeState, "addAttribute", "(IJJLjava/lang/Object;[BLjava/lang/String;)V",
                                                  &addAttributeMethod);
    VerifyOrReturn(err == CHIP_NO_ERROR,
                   ChipLogError(Controller, "Could not find addAttribute method with error %s", ErrorStr(err)));
    env->CallVoidMethod(nodeState, addAttributeMethod, static_cast<jint>(aPath.mEndpointId), static_cast<jlong>(aPath.mClusterId),
                        static_cast<jlong>(aPath.mAttributeId), value, jniByteArray.jniValue(), jsonString.jniValue());

   
    VerifyOrReturn(!env->ExceptionCheck(), env->ExceptionDescribe());

    // UpdateClusterDataVersion();

    // SetDataVersion to NodeState
    jmethodID setDataVersionMethod;
    err = JniReferences::GetInstance().FindMethod(env, nodeState, "setDataVersion", "(IJJ)V", &setDataVersionMethod);
    VerifyOrReturn(err == CHIP_NO_ERROR, ChipLogError(Controller, "Could not find setDataVersion method"));
    env->CallVoidMethod(nodeState, setDataVersionMethod, static_cast<jint>(aPath.mEndpointId),
                        static_cast<jlong>(aPath.mClusterId), static_cast<jlong>(version));
}

void ReadTlv::OnEventData(const app::EventHeader & aEventHeader, TLV::TLVReader * apData, const app::StatusIB * apStatus)
{
    DeviceLayer::StackUnlock unlock;
    CHIP_ERROR err = CHIP_NO_ERROR;
    JNIEnv * env   = JniReferences::GetInstance().GetEnvForCurrentThread();
    VerifyOrReturn(env != nullptr, ChipLogError(Controller, "Could not get JNIEnv for current thread"));

    VerifyOrReturn(mWrapperCallbackRef.HasValidObjectRef(),
                   ChipLogError(Controller, "mReportCallbackRef is not valid in %s", __func__));
    jobject wrapperCallback = mWrapperCallbackRef.ObjectRef();
    jobject nodeState       = GetNodeStateObj(env, mNodeStateClassSignature, wrapperCallback);
    if (apStatus != nullptr)
    {
        // Add Event Status to NodeState
        jmethodID addEventStatusMethod;
        err = JniReferences::GetInstance().FindMethod(env, nodeState, "addEventStatus", "(IJJILjava/lang/Integer;)V",
                                                      &addEventStatusMethod);
        VerifyOrReturn(
            err == CHIP_NO_ERROR,
            ChipLogError(Controller, "Could not find addEventStatus method with error %" CHIP_ERROR_FORMAT, err.Format()));

        jobject jClusterState = nullptr;
        if (apStatus->mClusterStatus.has_value())
        {
            err = JniReferences::GetInstance().CreateBoxedObject<jint>("java/lang/Integer", "(I)V",
                                                                       static_cast<jint>(*apStatus->mClusterStatus), jClusterState);
            VerifyOrReturn(err == CHIP_NO_ERROR,
                           ChipLogError(Controller, "Could not CreateBoxedObject with error %" CHIP_ERROR_FORMAT, err.Format()));
        }

        env->CallVoidMethod(nodeState, addEventStatusMethod, static_cast<jint>(aEventHeader.mPath.mEndpointId),
                            static_cast<jlong>(aEventHeader.mPath.mClusterId), static_cast<jlong>(aEventHeader.mPath.mEventId),
                            static_cast<jint>(apStatus->mStatus), jClusterState);
        VerifyOrReturn(!env->ExceptionCheck(), env->ExceptionDescribe());
        return;
    }
    VerifyOrReturn(apData != nullptr, ChipLogError(Controller, "Receive empty apData"); aEventHeader.LogPath());

    TLV::TLVReader readerForJavaTLV;
    readerForJavaTLV.Init(*apData);

    jlong eventNumber    = static_cast<jlong>(aEventHeader.mEventNumber);
    jint priorityLevel   = static_cast<jint>(aEventHeader.mPriorityLevel);
    jlong timestampValue = static_cast<jlong>(aEventHeader.mTimestamp.mValue);

    jint timestampType = 0;
    if (aEventHeader.mTimestamp.mType == app::Timestamp::Type::kSystem)
    {
        timestampType = static_cast<jint>(MILLIS_SINCE_BOOT);
    }
    else if (aEventHeader.mTimestamp.mType == app::Timestamp::Type::kEpoch)
    {
        timestampType = static_cast<jint>(MILLIS_SINCE_EPOCH);
    }
    else
    {
        ChipLogError(Controller, "Unsupported event timestamp type");
        aEventHeader.LogPath();
        return;
    }

    jobject value = nullptr;
    TLV::TLVReader readerForJavaObject;
    readerForJavaObject.Init(*apData);
#ifdef USE_JAVA_TLV_ENCODE_DECODE
    value = DecodeEventValue(aEventHeader.mPath, readerForJavaObject, &err);
    // If we don't know this event, just skip it.
    if (err == CHIP_ERROR_IM_MALFORMED_EVENT_PATH_IB)
    {
        TLV::TLVReader readerForGeneralValueObject;
        readerForGeneralValueObject.Init(*apData);
        value = DecodeGeneralTLVValue(env, readerForGeneralValueObject, err);
        err   = CHIP_NO_ERROR;
    }
    VerifyOrReturn(err == CHIP_NO_ERROR, ChipLogError(Controller, "Fail to decode event with error %s", ErrorStr(err));
                   aEventHeader.LogPath());
    VerifyOrReturn(!env->ExceptionCheck(), env->ExceptionDescribe());
#else
    value = DecodeGeneralTLVValue(env, readerForJavaObject, err);
#endif

    // Create TLV byte array to pass to Java layer
    size_t bufferLen                  = readerForJavaTLV.GetRemainingLength() + readerForJavaTLV.GetLengthRead();
    std::unique_ptr<uint8_t[]> buffer = std::unique_ptr<uint8_t[]>(new uint8_t[bufferLen]);
    uint32_t size                     = 0;
    // The TLVReader's read head is not pointing to the first element in the container, instead of the container itself, use
    // a TLVWriter to get a TLV with a normalized TLV buffer (Wrapped with an anonymous tag, no extra "end of container" tag
    // at the end.)
    TLV::TLVWriter writer;
    writer.Init(buffer.get(), bufferLen);
    err = writer.CopyElement(TLV::AnonymousTag(), readerForJavaTLV);

    VerifyOrReturn(err == CHIP_NO_ERROR, ChipLogError(Controller, "Fail to copy element with error %s", ErrorStr(err));
                   aEventHeader.LogPath());
    size = writer.GetLengthWritten();
    chip::ByteArray jniByteArray(env, reinterpret_cast<jbyte *>(buffer.get()), static_cast<jint>(size));

    // Convert TLV to JSON
    std::string json;
    err = ConvertReportTlvToJson(static_cast<uint32_t>(aEventHeader.mPath.mEventId), *apData, json);
    VerifyOrReturn(err == CHIP_NO_ERROR,
                   ChipLogError(Controller, "Fail to convert report tlv to Json with error %s", ErrorStr(err));
                   aEventHeader.LogPath());
    UtfString jsonString(env, json.c_str());

    jmethodID addEventMethod;
    err = JniReferences::GetInstance().FindMethod(env, nodeState, "addEvent", "(IJJJIIJLjava/lang/Object;[BLjava/lang/String;)V",
                                                  &addEventMethod);
    VerifyOrReturn(err == CHIP_NO_ERROR, ChipLogError(Controller, "Could not find addEvent method with error %s", ErrorStr(err));
                   aEventHeader.LogPath());
    env->CallVoidMethod(nodeState, addEventMethod, static_cast<jint>(aEventHeader.mPath.mEndpointId),
                        static_cast<jlong>(aEventHeader.mPath.mClusterId), static_cast<jlong>(aEventHeader.mPath.mEventId),
                        eventNumber, priorityLevel, timestampType, timestampValue, value, jniByteArray.jniValue(),
                        jsonString.jniValue());
    VerifyOrReturn(!env->ExceptionCheck(), env->ExceptionDescribe(); aEventHeader.LogPath());
}

CHIP_ERROR ReadTlv::ProcessAttributeReportIBs(TLV::TLVReader & aAttributeReportIBsReader)
{
    CHIP_ERROR err = CHIP_NO_ERROR;
    while (CHIP_NO_ERROR == (err = aAttributeReportIBsReader.Next()))
    {
        TLV::TLVReader dataReader;
        AttributeReportIB::Parser report;
        AttributeDataIB::Parser data;
        AttributeStatusIB::Parser status;
        AttributePathIB::Parser path;
        ConcreteDataAttributePath attributePath;
        StatusIB statusIB;

        TLV::TLVReader reader = aAttributeReportIBsReader;
        ReturnErrorOnFailure(report.Init(reader));

        err = report.GetAttributeStatus(&status);
        if (CHIP_NO_ERROR == err)
        {
            StatusIB::Parser errorStatus;
            ReturnErrorOnFailure(status.GetPath(&path));
            ReturnErrorOnFailure(ProcessAttributePath(path, attributePath));
            if (!attributePath.IsValid())
            {
                // Don't fail the entire read or subscription when there is an
                // out-of-range ID.  Just skip that one AttributeReportIB.
                ChipLogError(DataManagement,
                             "Skipping AttributeStatusIB with out-of-range IDs: (%d, " ChipLogFormatMEI ", " ChipLogFormatMEI ") ",
                             attributePath.mEndpointId, ChipLogValueMEI(attributePath.mClusterId),
                             ChipLogValueMEI(attributePath.mAttributeId));
                continue;
            }

            ReturnErrorOnFailure(status.GetErrorStatus(&errorStatus));
            ReturnErrorOnFailure(errorStatus.DecodeStatusIB(statusIB));
//            NoteReportingData();
            DataVersion version = 0;
            OnAttributeData(attributePath, nullptr, statusIB, version);
        }
        else if (CHIP_END_OF_TLV == err)
        {
            ReturnErrorOnFailure(report.GetAttributeData(&data));
            ReturnErrorOnFailure(data.GetPath(&path));
            ReturnErrorOnFailure(ProcessAttributePath(path, attributePath));
            if (!attributePath.IsValid())
            {
                // Don't fail the entire read or subscription when there is an
                // out-of-range ID.  Just skip that one AttributeReportIB.
                ChipLogError(DataManagement,
                             "Skipping AttributeDataIB  with out-of-range IDs: (%d, " ChipLogFormatMEI ", " ChipLogFormatMEI ") ",
                             attributePath.mEndpointId, ChipLogValueMEI(attributePath.mClusterId),
                             ChipLogValueMEI(attributePath.mAttributeId));
                continue;
            }

            DataVersion version = 0;
            ReturnErrorOnFailure(data.GetDataVersion(&version));
            attributePath.mDataVersion.SetValue(version);

//            if (mReadPrepareParams.mpDataVersionFilterList != nullptr)
//            {
//                UpdateDataVersionFilters(attributePath);
//            }

            ReturnErrorOnFailure(data.GetData(&dataReader));

            // The element in an array may be another array -- so we should only set the list operation when we are handling the
            // whole list.
            if (!attributePath.IsListOperation() && dataReader.GetType() == TLV::kTLVType_Array)
            {
                attributePath.mListOp = ConcreteDataAttributePath::ListOperation::ReplaceAll;
            }

//            if (attributePath.MatchesConcreteAttributePath(ConcreteAttributePath(
//                    kRootEndpointId, Clusters::IcdManagement::Id, Clusters::IcdManagement::Attributes::OperatingMode::Id)))
//            {
//                PeerType peerType;
//                TLV::TLVReader operatingModeTlvReader;
//                operatingModeTlvReader.Init(dataReader);
//                if (CHIP_NO_ERROR == ReadICDOperatingModeFromAttributeDataIB(std::move(operatingModeTlvReader), peerType))
//                {
//                    // It is safe to call `OnPeerTypeChange` since we are in the middle of parsing the attribute data, And
//                    // the subscription should be active so `OnActiveModeNotification` is a no-op in this case.
//                    InteractionModelEngine::GetInstance()->OnPeerTypeChange(mPeer, peerType);
//                }
//                else
//                {
//                    ChipLogError(DataManagement, "Failed to get ICD state from attribute data with error'%" CHIP_ERROR_FORMAT "'",
//                                 err.Format());
//                }
//            }

//            NoteReportingData();
            OnAttributeData(attributePath, &dataReader, statusIB, version);

             
        }
    }

    if (CHIP_END_OF_TLV == err)
    {
        err = CHIP_NO_ERROR;
    }

    return err;
}

CHIP_ERROR ReadTlv::ProcessEventReportIBs(TLV::TLVReader & aEventReportIBsReader)
{
    CHIP_ERROR err = CHIP_NO_ERROR;
    while (CHIP_NO_ERROR == (err = aEventReportIBsReader.Next()))
    {
        TLV::TLVReader dataReader;
        EventReportIB::Parser report;
        EventDataIB::Parser data;
        EventHeader header;
        StatusIB statusIB; // Default value for statusIB is success.

        TLV::TLVReader reader = aEventReportIBsReader;
        ReturnErrorOnFailure(report.Init(reader));

        err = report.GetEventData(&data);

        if (err == CHIP_NO_ERROR)
        {
            header.mTimestamp = mEventTimestamp;
            ReturnErrorOnFailure(data.DecodeEventHeader(header));
            mEventTimestamp = header.mTimestamp;

            ReturnErrorOnFailure(data.GetData(&dataReader));

//            //
//            // Update the event number being tracked in mReadPrepareParams in case
//            // we want to send it in the next SubscribeRequest message to convey
//            // the event number for which we have already received an event.
//            //
//            mReadPrepareParams.mEventNumber.SetValue(header.mEventNumber + 1);

//            NoteReportingData();
            OnEventData(header, &dataReader, nullptr);
        }
        else if (err == CHIP_END_OF_TLV)
        {
            EventStatusIB::Parser status;
            EventPathIB::Parser pathIB;
            StatusIB::Parser statusIBParser;
            ReturnErrorOnFailure(report.GetEventStatus(&status));
            ReturnErrorOnFailure(status.GetPath(&pathIB));
            ReturnErrorOnFailure(pathIB.GetEventPath(&header.mPath));
            ReturnErrorOnFailure(status.GetErrorStatus(&statusIBParser));
            ReturnErrorOnFailure(statusIBParser.DecodeStatusIB(statusIB));

//            NoteReportingData();
            OnEventData(header, nullptr, &statusIB);
        }
    }

    if (CHIP_END_OF_TLV == err)
    {
        err = CHIP_NO_ERROR;
    }

    return err;
}


CHIP_ERROR ReadTlv::ProcessReportData(uint8_t *aPayload, size_t aSize) {
//    packet->Read(aPayload, aSize);

    CHIP_ERROR err = CHIP_NO_ERROR;

    System::PacketBufferTLVWriter writer;
    writer.Init(chip::System::PacketBufferHandle::New(chip::System::PacketBuffer::kMaxSize));
    TLV::TLVReader aReader;
    aReader.Init(aPayload, aSize);
    err = aReader.Next();

    err = writer.CopyElement(aReader);
    chip::System::PacketBufferHandle packet;
    err = writer.Finalize(&packet);

    ReportDataMessage::Parser report;
    bool suppressResponse         = true;
    bool mPendingMoreChunks       = false;
    EventReportIBs::Parser eventReportIBs;
    AttributeReportIBs::Parser attributeReportIBs;
    System::PacketBufferTLVReader reader;
    reader.Init(std::move(packet));
    err = report.Init(reader);
    SuccessOrExit(err);

    err = report.GetSuppressResponse(&suppressResponse);
    if (CHIP_END_OF_TLV == err)
    {
        suppressResponse = false;
        err              = CHIP_NO_ERROR;
    }
    SuccessOrExit(err);

    err = report.GetMoreChunkedMessages(&mPendingMoreChunks);
    if (CHIP_END_OF_TLV == err)
    {
        mPendingMoreChunks = false;
        err                = CHIP_NO_ERROR;
    }
    SuccessOrExit(err);

    err = report.GetEventReports(&eventReportIBs);
    if (err == CHIP_END_OF_TLV)
    {
        err = CHIP_NO_ERROR;
    }
    else if (err == CHIP_NO_ERROR)
    {
        chip::TLV::TLVReader EventReportsReader;
        eventReportIBs.GetReader(&EventReportsReader);
        err = ProcessEventReportIBs(EventReportsReader);
    }
    SuccessOrExit(err);

    err = report.GetAttributeReportIBs(&attributeReportIBs);
    if (err == CHIP_END_OF_TLV)
    {
        err = CHIP_NO_ERROR;
    }
    else if (err == CHIP_NO_ERROR)
    {
        TLV::TLVReader attributeReportIBsReader;
        attributeReportIBs.GetReader(&attributeReportIBsReader);
        err = ProcessAttributeReportIBs(attributeReportIBsReader);
    }
    SuccessOrExit(err);

exit:
    return err;
}


void readReportData(JNIEnv * env, jobject self, jbyteArray byteArrayJava, const char * nodeStateClassSignature)
{
    printf("readReportData called with byteArrayJava: %p\n", byteArrayJava);
        chip::DeviceLayer::StackLock lock;
        CHIP_ERROR err = CHIP_NO_ERROR;

        JniByteArray byteArray(env, byteArrayJava);
        if (byteArray.byteSpan().empty())
        {
                ChipLogError(Controller, "readReportData called with empty byte array");
                return;
        }

        // ReadTlv * readTlv = chip::Platform::New<ReadTlv>(self, nodeStateClassSignature);
        ReadTlv readTlv(self, nodeStateClassSignature);
//        // 1) Get raw bytes
//        jsize len = (env)->GetArrayLength(env, byteArray);
//        jbyte *buf = (env)->GetByteArrayElements(env, byteArray, NULL);
//        err = readTlv.Init((const uint8_t*)buf, (size_t)len);
//
//        // 3) Release the JNI byte buffer
//        (env)->ReleaseByteArrayElements(env, byteArray, buf, JNI_ABORT);
        err = readTlv.ProcessReportData((uint8_t *) byteArray.byteSpan().data(), byteArray.byteSpan().size());
        if (err != CHIP_NO_ERROR)
        {
                ChipLogError(Controller, "Failed to process report data: %" CHIP_ERROR_FORMAT, err.Format());
                return;
        }
}
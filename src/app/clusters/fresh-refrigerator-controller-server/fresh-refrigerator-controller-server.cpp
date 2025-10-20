/**
 *
 *    Copyright (c) 2025 Photon Smart Authors
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
 *
 */
#include "fresh-refrigerator-controller-server.h"
#include <app/AttributeAccessInterfaceRegistry.h>
#include <src/platform/ESP32/FctryStoreManager.h>

#include "app/reporting/reporting.h"
#include "app/util/attribute-storage.h"
#include "app/util/generic-callbacks.h"
#include <app-common/zap-generated/attribute-type.h>

namespace chip::app::Clusters::FreshRefrigeratorController {
class StorageDelagate : public DeviceLayer::PersistedStorage::FctryStoreManager
{
public:
    template <typename T>
    CHIP_ERROR Put(const char * key, const T & value)
    {
        return FctryStoreManager::Put(key, value);
    }

    template <typename T>
    CHIP_ERROR Get(const char * key, T * value)
    {
        return FctryStoreManager::Get(key, value);
    }
};

static StorageDelagate storageDelagate;

Instance::Instance(EndpointId aEndpointId, ClusterId aClusterId) :
    AttributeAccessInterface(Optional<EndpointId>(aEndpointId), aClusterId), mEndpointId(aEndpointId), mClusterId(aClusterId)
// mode in the list at the start of the Init function to ensure that it represents a valid mode.
{}

CHIP_ERROR Instance::Init()
{
    VerifyOrDie(emberAfContainsServer(mEndpointId, mClusterId) == true);
    if (storageDelagate.Get("default-fridge-temperature", &mDefaultFridgeTemperature) != CHIP_NO_ERROR)
    {
        storageDelagate.Put("default-fridge-temperature", mDefaultFridgeTemperature);
    }
    if (storageDelagate.Get("default-freezer-temperature", &mDefaultFreezerTemperature) != CHIP_NO_ERROR)
    {
        storageDelagate.Put("default-freezer-temperature", mDefaultFreezerTemperature);
    }
    if (storageDelagate.Get("previous-fridge-temperature", &mPreviousFridgeTemperature) != CHIP_NO_ERROR)
    {
        storageDelagate.Put("previous-fridge-temperature", mPreviousFridgeTemperature);
    }
    if (storageDelagate.Get("previous-freezer-temperature", &mPreviousFreezerTemperature) != CHIP_NO_ERROR)
    {
        storageDelagate.Put("previous-freezer-temperature", mPreviousFreezerTemperature);
    }
    if (storageDelagate.Get("super-cool-time", &mSuperCoolTime) != CHIP_NO_ERROR)
    {
        storageDelagate.Put("super-cool-time", mSuperCoolTime);
    }
    if (storageDelagate.Get("super-freeze-time", &mSuperFreezeTime) != CHIP_NO_ERROR)
    {
        storageDelagate.Put("super-freeze-time", mSuperFreezeTime);
    }
    if (storageDelagate.Get("alarm-time", &mAlarmTime) != CHIP_NO_ERROR)
    {
        storageDelagate.Put("alarm-time", mAlarmTime);
    }
    if (storageDelagate.Get("reset-timeout", &mResetTimeout) != CHIP_NO_ERROR)
    {
        storageDelagate.Put("reset-timeout", mResetTimeout);
    }
    if (storageDelagate.Get("display-active-time", &mDisplayActiveTime) != CHIP_NO_ERROR)
    {
        storageDelagate.Put("display-active-time", mDisplayActiveTime);
    }
    if (storageDelagate.Get("display-error-time", &mDisplayErrorTime) != CHIP_NO_ERROR)
    {
        storageDelagate.Put("display-error-time", mDisplayErrorTime);
    }
    if (storageDelagate.Get("fridge-error-margin", &mFridgeErrorMargin) != CHIP_NO_ERROR)
    {
        storageDelagate.Put("fridge-error-margin", mFridgeErrorMargin);
    }
    if (storageDelagate.Get("freezer-error-margin", &mFreezerErrorMargin) != CHIP_NO_ERROR)
    {
        storageDelagate.Put("freezer-error-margin", mFreezerErrorMargin);
    }
    if (storageDelagate.Get("temperature-error-time", &mTemperatureErrorTime) != CHIP_NO_ERROR)
    {
        storageDelagate.Put("temperature-error-time", mTemperatureErrorTime);
    }
    VerifyOrReturnError(AttributeAccessInterfaceRegistry::Instance().Register(this), CHIP_ERROR_INCORRECT_STATE);

    return CHIP_NO_ERROR;
}

Instance::~Instance()
{
    AttributeAccessInterfaceRegistry::Instance().Unregister(this);
}

int16_t Instance::GetDefaultFridgeTemperature() const
{
    return mDefaultFridgeTemperature;
}
int16_t Instance::GetDefrostTemperature() const
{
    return mDefrostTemperature;
}

int16_t Instance::GetDefaultFreezerTemperature() const
{
    return mDefaultFreezerTemperature;
}

int16_t Instance::GetPreviousFridgeTemperature() const
{
    return mPreviousFridgeTemperature;
}

int16_t Instance::GetPreviousFreezerTemperature() const
{
    return mPreviousFreezerTemperature;
}

uint32_t Instance::GetSuperCoolTime() const
{
    return mSuperCoolTime;
}

uint32_t Instance::GetSuperFreezeTime() const
{
    return mSuperFreezeTime;
}

uint32_t Instance::GetAlarmTime() const
{
    return mAlarmTime;
}

uint32_t Instance::GetResetTimeout() const
{
    return mResetTimeout;
}

uint32_t Instance::GetDisplayActiveTime() const
{
    return mDisplayActiveTime;
}

uint32_t Instance::GetDisplayErrorTime() const
{
    return mDisplayErrorTime;
}

int16_t Instance::GetFridgeErrorMargin() const
{
    return mFridgeErrorMargin;
}

int16_t Instance::GetFreezerErrorMargin() const
{
    return mFreezerErrorMargin;
}

uint32_t Instance::GetTemperatureErrorTime() const
{
    return mTemperatureErrorTime;
}

bool Instance::GetCompressorState() const
{
    return mCompressorState;
}

bool Instance::GetDefrostState() const
{
    return mDefrostState;
}

bool Instance::GetFridgeDoorState() const
{
    return mFridgeDoorState;
}

bool Instance::GetFreezerDoorState() const
{
    return mFridgeDoorState;
}

// Setters
CHIP_ERROR Instance::SetDefaultFridgeTemperature(int16_t temp)
{
    if (temp != mDefaultFridgeTemperature)
    {
        if (temp < 200 || temp > 800)
        {
            return StatusIB(Protocols::InteractionModel::Status::ConstraintError).ToChipError();
        }
        ConcreteAttributePath path = ConcreteAttributePath(mEndpointId, mClusterId, Attributes::FridgeTemperatureDefault::Id);
        ReturnLogErrorOnFailure(storageDelagate.Put("default-fridge-temperature", temp));
        mDefaultFridgeTemperature = temp;
        MatterReportingAttributeChangeCallback(path);
        MatterPostAttributeChangeCallback(path, ZCL_INT16S_ATTRIBUTE_TYPE, sizeof(int16_t), reinterpret_cast<uint8_t *>(&temp));
    }
    return CHIP_NO_ERROR;
}

CHIP_ERROR Instance::SetDefaultFreezerTemperature(int16_t temp)
{
    if (temp != mDefaultFreezerTemperature)
    {
        if (temp < -2400 || temp > -1400)
        {
            return StatusIB(Protocols::InteractionModel::Status::ConstraintError).ToChipError();
        }
        ConcreteAttributePath path = ConcreteAttributePath(mEndpointId, mClusterId, Attributes::FreezerTemperatureDefault::Id);
        ReturnErrorOnFailure(storageDelagate.Put("default-freezer-temperature", temp));
        mDefaultFreezerTemperature = temp;
        MatterReportingAttributeChangeCallback(path);
        MatterPostAttributeChangeCallback(path, ZCL_INT16S_ATTRIBUTE_TYPE, sizeof(int16_t), reinterpret_cast<uint8_t *>(&temp));
    }
    return CHIP_NO_ERROR;
}

CHIP_ERROR Instance::SetDefrostTemperature(int16_t temp)
{
    if (temp != mDefrostTemperature)
    {
        if (temp < -5000 || temp > -5000)
        {
            return StatusIB(Protocols::InteractionModel::Status::ConstraintError).ToChipError();
        }
        ConcreteAttributePath path = ConcreteAttributePath(mEndpointId, mClusterId, Attributes::DefrostTemperature::Id);
        ReturnErrorOnFailure(storageDelagate.Put("defrost-temperature", temp));
        mDefrostTemperature = temp;
        MatterReportingAttributeChangeCallback(path);
        MatterPostAttributeChangeCallback(path, ZCL_INT16S_ATTRIBUTE_TYPE, sizeof(int16_t), reinterpret_cast<uint8_t *>(&temp));
    }
    return CHIP_NO_ERROR;
}

CHIP_ERROR Instance::SetPreviousFridgeTemperature(int16_t temp)
{
    if (temp != mPreviousFridgeTemperature)
    {
        if (temp < 200 || temp > 800)
        {
            return StatusIB(Protocols::InteractionModel::Status::ConstraintError).ToChipError();
        }
        ConcreteAttributePath path = ConcreteAttributePath(mEndpointId, mClusterId, Attributes::FridgePreviousTemperature::Id);
        ReturnErrorOnFailure(storageDelagate.Put("previous-fridge-temperature", temp));
        mPreviousFridgeTemperature = temp;
        MatterReportingAttributeChangeCallback(path);
        MatterPostAttributeChangeCallback(path, ZCL_INT16S_ATTRIBUTE_TYPE, sizeof(int16_t), reinterpret_cast<uint8_t *>(&temp));
    }
    return CHIP_NO_ERROR;
}

CHIP_ERROR Instance::SetPreviousFreezerTemperature(int16_t temp)
{
    if (temp != mDefaultFreezerTemperature)
    {
        if (temp < -2400 || temp > -1400)
        {
            return StatusIB(Protocols::InteractionModel::Status::ConstraintError).ToChipError();
        }
        ConcreteAttributePath path = ConcreteAttributePath(mEndpointId, mClusterId, Attributes::FreezerPreviousTemperature::Id);
        ReturnErrorOnFailure(storageDelagate.Put("previous-freezer-temperature", temp));
        mPreviousFridgeTemperature = temp;
        MatterReportingAttributeChangeCallback(path);
        MatterPostAttributeChangeCallback(path, ZCL_INT16S_ATTRIBUTE_TYPE, sizeof(int16_t), reinterpret_cast<uint8_t *>(&temp));
    }
    return CHIP_NO_ERROR;
}

CHIP_ERROR Instance::SetSuperCoolTime(uint32_t time)
{
    if (time != mSuperCoolTime)
    {
        if (time < (60 * 60) || time > (60 * 60 * 24 * 3)) // 6 minutes to 7 days
        {
            return StatusIB(Protocols::InteractionModel::Status::ConstraintError).ToChipError();
        }
        ConcreteAttributePath path = ConcreteAttributePath(mEndpointId, mClusterId, Attributes::SuperCoolTime::Id);
        ReturnErrorOnFailure(storageDelagate.Put("super-cool-time", time));
        mSuperCoolTime = time;
        MatterReportingAttributeChangeCallback(path);
        MatterPostAttributeChangeCallback(path, ZCL_INT32U_ATTRIBUTE_TYPE, sizeof(uint32_t), reinterpret_cast<uint8_t *>(&time));
    }
    return CHIP_NO_ERROR;
}

CHIP_ERROR Instance::SetSuperFreezeTime(uint32_t time)
{
    if (time != mSuperFreezeTime)
    {
        if (time < (60 * 60) || time > (60 * 60 * 24 * 3)) // 6 minutes to 7 days
        {
            return StatusIB(Protocols::InteractionModel::Status::ConstraintError).ToChipError();
        }
        ConcreteAttributePath path = ConcreteAttributePath(mEndpointId, mClusterId, Attributes::SuperFreezeTime::Id);
        ReturnErrorOnFailure(storageDelagate.Put("super-freeze-time", time));
        mSuperFreezeTime = time;
        MatterReportingAttributeChangeCallback(path);
        MatterPostAttributeChangeCallback(path, ZCL_INT32U_ATTRIBUTE_TYPE, sizeof(uint32_t), reinterpret_cast<uint8_t *>(&time));
    }
    return CHIP_NO_ERROR;
}

CHIP_ERROR Instance::SetAlarmTime(uint32_t time)
{
    if (time != mAlarmTime)
    {
        if (time < 5 || time > (60 * 5))
        {
            return StatusIB(Protocols::InteractionModel::Status::ConstraintError).ToChipError();
        }
        ConcreteAttributePath path = ConcreteAttributePath(mEndpointId, mClusterId, Attributes::AlarmTime::Id);
        ReturnErrorOnFailure(storageDelagate.Put("alarm-time", time));
        mAlarmTime = time;
        MatterReportingAttributeChangeCallback(path);
        MatterPostAttributeChangeCallback(path, ZCL_INT32U_ATTRIBUTE_TYPE, sizeof(uint32_t), reinterpret_cast<uint8_t *>(&time));
    }
    return CHIP_NO_ERROR;
}

CHIP_ERROR Instance::SetResetTimeout(uint32_t timeout)
{
    if (timeout != mResetTimeout)
    {
        if (timeout < 1 || timeout > 7)
        {
            return StatusIB(Protocols::InteractionModel::Status::ConstraintError).ToChipError();
        }
        ConcreteAttributePath path = ConcreteAttributePath(mEndpointId, mClusterId, Attributes::ResetTimeout::Id);
        ReturnErrorOnFailure(storageDelagate.Put("reset-timeout", timeout));
        mResetTimeout = timeout;
        MatterReportingAttributeChangeCallback(path);
        MatterPostAttributeChangeCallback(path, ZCL_INT32U_ATTRIBUTE_TYPE, sizeof(uint32_t), reinterpret_cast<uint8_t *>(&timeout));
    }
    return CHIP_NO_ERROR;
}

CHIP_ERROR Instance::SetDisplayActiveTime(uint32_t time)
{
    if (time != mDisplayActiveTime)
    {
        if (time < 10 || time > 60 * 5)
        {
            return StatusIB(Protocols::InteractionModel::Status::ConstraintError).ToChipError();
        }
        ConcreteAttributePath path = ConcreteAttributePath(mEndpointId, mClusterId, Attributes::DisplayActiveTime::Id);
        ReturnErrorOnFailure(storageDelagate.Put("display-active-time", time));
        mDisplayActiveTime = time;
        MatterReportingAttributeChangeCallback(path);
        MatterPostAttributeChangeCallback(path, ZCL_INT32U_ATTRIBUTE_TYPE, sizeof(uint32_t), reinterpret_cast<uint8_t *>(&time));
    }
    return CHIP_NO_ERROR;
}

CHIP_ERROR Instance::SetDisplayErrorTime(uint32_t time)
{
    if (time != mDisplayErrorTime)
    {
        if (time < 2 || time > 60 * 5)
        {
            return StatusIB(Protocols::InteractionModel::Status::ConstraintError).ToChipError();
        }
        ConcreteAttributePath path = ConcreteAttributePath(mEndpointId, mClusterId, Attributes::DisplayErrorTime::Id);
        ReturnErrorOnFailure(storageDelagate.Put("display-error-time", time));
        mDisplayErrorTime = time;
        MatterReportingAttributeChangeCallback(path);
        MatterPostAttributeChangeCallback(path, ZCL_INT32U_ATTRIBUTE_TYPE, sizeof(uint32_t), reinterpret_cast<uint8_t *>(&time));
    }
    return CHIP_NO_ERROR;
}

CHIP_ERROR Instance::SetFridgeErrorMargin(int16_t margin)
{
    if (margin != mFridgeErrorMargin)
    {
        if (margin < 100 || margin > 5000)
        {
            return StatusIB(Protocols::InteractionModel::Status::ConstraintError).ToChipError();
        }
        ConcreteAttributePath path = ConcreteAttributePath(mEndpointId, mClusterId, Attributes::FridgeErrorMargin::Id);
        ReturnErrorOnFailure(storageDelagate.Put("fridge-error-margin", margin));
        mFridgeErrorMargin = margin;
        MatterReportingAttributeChangeCallback(path);
        MatterPostAttributeChangeCallback(path, ZCL_INT16S_ATTRIBUTE_TYPE, sizeof(int16_t), reinterpret_cast<uint8_t *>(&margin));
    }
    return CHIP_NO_ERROR;
}

CHIP_ERROR Instance::SetFreezerErrorMargin(int16_t margin)
{
    if (margin != mFreezerErrorMargin)
    {
        if (margin < 100 || margin > 5000)
        {
            return StatusIB(Protocols::InteractionModel::Status::ConstraintError).ToChipError();
        }
        ConcreteAttributePath path = ConcreteAttributePath(mEndpointId, mClusterId, Attributes::FreezerErrorMargin::Id);
        ReturnErrorOnFailure(storageDelagate.Put("freezer-error-margin", margin));
        mFreezerErrorMargin = margin;
        MatterReportingAttributeChangeCallback(path);
        MatterPostAttributeChangeCallback(path, ZCL_INT16S_ATTRIBUTE_TYPE, sizeof(int16_t), reinterpret_cast<uint8_t *>(&margin));
    }
    return CHIP_NO_ERROR;
}

CHIP_ERROR Instance::SetTemperatureErrorTime(uint32_t time)
{
    if (time != mTemperatureErrorTime)
    {
        if (time < 60 * 5 || time > 60 * 60 * 10) // 5 minutes to 5 hours
        {
            return StatusIB(Protocols::InteractionModel::Status::ConstraintError).ToChipError();
        }
        ConcreteAttributePath path = ConcreteAttributePath(mEndpointId, mClusterId, Attributes::TemperatureErrorTime::Id);
        ReturnErrorOnFailure(storageDelagate.Put("temperature-error-time", time));
        mTemperatureErrorTime = time;
        MatterReportingAttributeChangeCallback(path);
        MatterPostAttributeChangeCallback(path, ZCL_INT32U_ATTRIBUTE_TYPE, sizeof(uint32_t), reinterpret_cast<uint8_t *>(&time));
    }
    return CHIP_NO_ERROR;
}

CHIP_ERROR Instance::SetCompressorState(bool state)
{
    if (state != mCompressorState)
    {
        ConcreteAttributePath path = ConcreteAttributePath(mEndpointId, mClusterId, Attributes::CompressorState::Id);
        mCompressorState           = state;
        MatterReportingAttributeChangeCallback(path);
        MatterPostAttributeChangeCallback(path, ZCL_BOOLEAN_ATTRIBUTE_TYPE, sizeof(bool), reinterpret_cast<uint8_t *>(&state));
    }
    return CHIP_NO_ERROR;
}

CHIP_ERROR Instance::SetDefrostState(bool state)
{
    if (state != mDefrostState)
    {
        ConcreteAttributePath path = ConcreteAttributePath(mEndpointId, mClusterId, Attributes::DefrostState::Id);
        mDefrostState              = state;
        MatterReportingAttributeChangeCallback(path);
        MatterPostAttributeChangeCallback(path, ZCL_BOOLEAN_ATTRIBUTE_TYPE, sizeof(bool), reinterpret_cast<uint8_t *>(&state));
    }
    return CHIP_NO_ERROR;
}

CHIP_ERROR Instance::SetFridgeDoorState(bool state)
{
    if (state != mFridgeDoorState)
    {
        ConcreteAttributePath path = ConcreteAttributePath(mEndpointId, mClusterId, Attributes::FridgeDoorState::Id);
        mFridgeDoorState           = state;
        MatterReportingAttributeChangeCallback(path);
        MatterPostAttributeChangeCallback(path, ZCL_BOOLEAN_ATTRIBUTE_TYPE, sizeof(bool), reinterpret_cast<uint8_t *>(&state));
    }
    return CHIP_NO_ERROR;
}

CHIP_ERROR Instance::SetFreezerDoorState(bool state)
{
    if (state != mFreezerDoorState)
    {
        ConcreteAttributePath path = ConcreteAttributePath(mEndpointId, mClusterId, Attributes::FreezerDoorState::Id);
        mFreezerDoorState          = state;
        MatterReportingAttributeChangeCallback(path);
        MatterPostAttributeChangeCallback(path, ZCL_BOOLEAN_ATTRIBUTE_TYPE, sizeof(bool), reinterpret_cast<uint8_t *>(&state));
    }
    return CHIP_NO_ERROR;
}

CHIP_ERROR Instance::Read(const ConcreteReadAttributePath & aPath, AttributeValueEncoder & aEncoder)
{
    ChipLogProgress(InteractionModel, " Fresh FreshRefrigeratorController Read (%" PRIu32 ")", aPath.mAttributeId);
    switch (aPath.mAttributeId)
    {
    case Attributes::FridgeTemperatureDefault::Id:
        ReturnErrorOnFailure(aEncoder.Encode(mDefaultFridgeTemperature));
        break;
    case Attributes::FreezerTemperatureDefault::Id:
        ReturnErrorOnFailure(aEncoder.Encode(mDefaultFreezerTemperature));
        break;
    case Attributes::FridgePreviousTemperature::Id:
        ReturnErrorOnFailure(aEncoder.Encode(mPreviousFridgeTemperature));
        break;
    case Attributes::FreezerPreviousTemperature::Id:
        ReturnErrorOnFailure(aEncoder.Encode(mPreviousFreezerTemperature));
        break;
    case Attributes::SuperCoolTime::Id:
        ReturnErrorOnFailure(aEncoder.Encode(mSuperCoolTime));
        break;
    case Attributes::SuperFreezeTime::Id:
        ReturnErrorOnFailure(aEncoder.Encode(mSuperFreezeTime));
        break;
    case Attributes::AlarmTime::Id:
        ReturnErrorOnFailure(aEncoder.Encode(mAlarmTime));
        break;
    case Attributes::ResetTimeout::Id:
        ReturnErrorOnFailure(aEncoder.Encode(mResetTimeout));
        break;
    case Attributes::DisplayActiveTime::Id:
        ReturnErrorOnFailure(aEncoder.Encode(mDisplayActiveTime));
        break;
    case Attributes::DisplayErrorTime::Id:
        ReturnErrorOnFailure(aEncoder.Encode(mDisplayErrorTime));
        break;
    case Attributes::FridgeErrorMargin::Id:
        ReturnErrorOnFailure(aEncoder.Encode(mFridgeErrorMargin));
        break;
    case Attributes::FreezerErrorMargin::Id:
        ReturnErrorOnFailure(aEncoder.Encode(mFreezerErrorMargin));
        break;
    case Attributes::TemperatureErrorTime::Id:
        ReturnErrorOnFailure(aEncoder.Encode(mTemperatureErrorTime));
        break;
    case Attributes::CompressorState::Id:
        ReturnErrorOnFailure(aEncoder.Encode(mCompressorState));
        break;
    case Attributes::DefrostState::Id:
        ReturnErrorOnFailure(aEncoder.Encode(mDefrostState));
        break;
    case Attributes::FridgeDoorState::Id:
        ReturnErrorOnFailure(aEncoder.Encode(mFridgeDoorState));
        break;
    case Attributes::FreezerDoorState::Id:
        ReturnErrorOnFailure(aEncoder.Encode(mFreezerDoorState));
        break;
    default:
        break;
    }
    return CHIP_NO_ERROR;
}

CHIP_ERROR Instance::SetDefaultFridgeTemperature(AttributeValueDecoder & aDecoder)
{
    int16_t newtemp;
    ReturnLogErrorOnFailure(aDecoder.Decode(newtemp));
    ReturnLogErrorOnFailure(SetDefaultFridgeTemperature(newtemp));
    return CHIP_NO_ERROR;
}

CHIP_ERROR Instance::SetDefaultFreezerTemperature(AttributeValueDecoder & aDecoder)
{
    int16_t newtemp;
    ReturnErrorOnFailure(aDecoder.Decode(newtemp));
    ReturnErrorOnFailure(SetDefaultFreezerTemperature(newtemp));
    return CHIP_NO_ERROR;
}

CHIP_ERROR Instance::SetDefrostTemperature(AttributeValueDecoder & aDecoder)
{
    int16_t newtemp;
    ReturnErrorOnFailure(aDecoder.Decode(newtemp));
    ReturnErrorOnFailure(SetDefrostTemperature(newtemp));
    return CHIP_NO_ERROR;
}

CHIP_ERROR Instance::SetPreviousFridgeTemperature(AttributeValueDecoder & aDecoder)
{
    int16_t newtemp;
    ReturnErrorOnFailure(aDecoder.Decode(newtemp));
    ReturnErrorOnFailure(SetPreviousFridgeTemperature(newtemp));
    return CHIP_NO_ERROR;
}

CHIP_ERROR Instance::SetPreviousFreezerTemperature(AttributeValueDecoder & aDecoder)
{
    int16_t newtemp;
    ReturnErrorOnFailure(aDecoder.Decode(newtemp));
    ReturnErrorOnFailure(SetPreviousFreezerTemperature(newtemp));
    return CHIP_NO_ERROR;
}

CHIP_ERROR Instance::SetSuperCoolTime(AttributeValueDecoder & aDecoder)
{
    uint32_t newtime;
    ReturnErrorOnFailure(aDecoder.Decode(newtime));
    ReturnErrorOnFailure(SetSuperCoolTime(newtime));
    return CHIP_NO_ERROR;
}

CHIP_ERROR Instance::SetSuperFreezeTime(AttributeValueDecoder & aDecoder)
{
    uint32_t newtime;
    ReturnErrorOnFailure(aDecoder.Decode(newtime));
    ReturnErrorOnFailure(SetSuperFreezeTime(newtime));
    return CHIP_NO_ERROR;
}

CHIP_ERROR Instance::SetAlarmTime(AttributeValueDecoder & aDecoder)
{
    uint32_t newtime;
    ReturnErrorOnFailure(aDecoder.Decode(newtime));
    ReturnErrorOnFailure(SetAlarmTime(newtime));
    return CHIP_NO_ERROR;
}

CHIP_ERROR Instance::SetResetTimeout(AttributeValueDecoder & aDecoder)
{
    uint32_t newtime;
    ReturnErrorOnFailure(aDecoder.Decode(newtime));
    ReturnErrorOnFailure(SetResetTimeout(newtime));
    return CHIP_NO_ERROR;
}

CHIP_ERROR Instance::SetDisplayActiveTime(AttributeValueDecoder & aDecoder)
{
    uint32_t newtime;
    ReturnErrorOnFailure(aDecoder.Decode(newtime));
    ReturnErrorOnFailure(SetDisplayActiveTime(newtime));
    return CHIP_NO_ERROR;
}

CHIP_ERROR Instance::SetDisplayErrorTime(AttributeValueDecoder & aDecoder)
{
    uint32_t newtime;
    ReturnErrorOnFailure(aDecoder.Decode(newtime));
    ReturnErrorOnFailure(SetDisplayErrorTime(newtime));
    return CHIP_NO_ERROR;
}

CHIP_ERROR Instance::SetFridgeErrorMargin(AttributeValueDecoder & aDecoder)
{
    int16_t newMargin;
    ReturnErrorOnFailure(aDecoder.Decode(newMargin));
    ReturnErrorOnFailure(SetFridgeErrorMargin(newMargin));
    return CHIP_NO_ERROR;
}

CHIP_ERROR Instance::SetFreezerErrorMargin(AttributeValueDecoder & aDecoder)
{
    int16_t newMargin;
    ReturnErrorOnFailure(aDecoder.Decode(newMargin));
    ReturnErrorOnFailure(SetFreezerErrorMargin(newMargin));
    return CHIP_NO_ERROR;
}

CHIP_ERROR Instance::SetTemperatureErrorTime(AttributeValueDecoder & aDecoder)
{
    uint32_t newtime;
    ReturnErrorOnFailure(aDecoder.Decode(newtime));
    ReturnErrorOnFailure(SetTemperatureErrorTime(newtime));
    return CHIP_NO_ERROR;
}

CHIP_ERROR Instance::SetCompressorState(AttributeValueDecoder & aDecoder)
{
    bool newState;
    ReturnErrorOnFailure(aDecoder.Decode(newState));
    ReturnErrorOnFailure(SetCompressorState(newState));
    return CHIP_NO_ERROR;
}

CHIP_ERROR Instance::SetDefrostState(AttributeValueDecoder & aDecoder)
{
    bool newState;
    ReturnErrorOnFailure(aDecoder.Decode(newState));
    ReturnErrorOnFailure(SetDefrostState(newState));
    return CHIP_NO_ERROR;
}

CHIP_ERROR Instance::SetFridgeDoorState(AttributeValueDecoder & aDecoder)
{
    bool newState;
    ReturnErrorOnFailure(aDecoder.Decode(newState));
    ReturnErrorOnFailure(SetFridgeDoorState(newState));
    return CHIP_NO_ERROR;
}

CHIP_ERROR Instance::SetFreezerDoorState(AttributeValueDecoder & aDecoder)
{
    bool newState;
    ReturnErrorOnFailure(aDecoder.Decode(newState));
    ReturnErrorOnFailure(SetFreezerDoorState(newState));
    return CHIP_NO_ERROR;
}

// Implements checking before attribute writes.
CHIP_ERROR Instance::Write(const ConcreteDataAttributePath & attributePath, AttributeValueDecoder & aDecoder)
{
    ChipLogProgress(InteractionModel, " Fresh FreshRefrigeratorController Write (%" PRIu32 ")", attributePath.mAttributeId);
    switch (attributePath.mAttributeId)
    {
    case Attributes::FridgeTemperatureDefault::Id:
        return SetDefaultFridgeTemperature(aDecoder);
    case Attributes::FreezerTemperatureDefault::Id:
        return SetDefaultFreezerTemperature(aDecoder);
    case Attributes::FridgePreviousTemperature::Id:
        return SetPreviousFridgeTemperature(aDecoder);
    case Attributes::FreezerPreviousTemperature::Id:
        return SetPreviousFreezerTemperature(aDecoder);
    case Attributes::SuperCoolTime::Id:
        return SetSuperCoolTime(aDecoder);
    case Attributes::SuperFreezeTime::Id:
        return SetSuperFreezeTime(aDecoder);
    case Attributes::AlarmTime::Id:
        return SetAlarmTime(aDecoder);
    case Attributes::ResetTimeout::Id:
        return SetResetTimeout(aDecoder);
    case Attributes::DisplayActiveTime::Id:
        return SetDisplayActiveTime(aDecoder);
    case Attributes::DisplayErrorTime::Id:
        return SetDisplayErrorTime(aDecoder);
    case Attributes::FridgeErrorMargin::Id:
        return SetFridgeErrorMargin(aDecoder);
    case Attributes::FreezerErrorMargin::Id:
        return SetFreezerErrorMargin(aDecoder);
    case Attributes::TemperatureErrorTime::Id:
        return SetTemperatureErrorTime(aDecoder);
    case Attributes::CompressorState::Id:
        return SetCompressorState(aDecoder);
    case Attributes::DefrostState::Id:
        return SetDefrostState(aDecoder);
    case Attributes::DefrostTemperature::Id:
        return SetDefrostTemperature(aDecoder);
    }

    return CHIP_ERROR_INCORRECT_STATE;
}
} // namespace chip::app::Clusters::FreshRefrigeratorController

void MatterFreshRefrigeratorControllerPluginServerInitCallback() {}

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
#define FACTORY_STORE_MANAGER_IMPLEMENTATION
#include "fresh-refrigerator-controller-server.h"
#include <app/AttributeAccessInterfaceRegistry.h>
#include <src/platform/Photon/FctryStoreManager.h>

#include "app/reporting/reporting.h"
#include "app/util/attribute-storage.h"

namespace chip::app::Clusters::FreshRefrigeratorController
{
    class StorageDelagate : public DeviceLayer::PersistedStorage::FctryStoreManager
    {
    public:
        template<typename T>
        CHIP_ERROR Put(const char *key, const T &value)
        {
            return FctryStoreManager::Put(key, value);
        }

        template<typename T>
        CHIP_ERROR Get(const char *key, T *value)
        {
            return FctryStoreManager::Get(key, value);
        }
    };

    static StorageDelagate storageDelagate;

    Instance::Instance(EndpointId aEndpointId, ClusterId aClusterId) : AttributeAccessInterface(Optional<EndpointId>(aEndpointId), aClusterId),
                                                                       mEndpointId(aEndpointId),
                                                                       mClusterId(aClusterId)
    // mode in the list at the start of the Init function to ensure that it represents a valid mode.
    {
    }

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

    // Setters
    CHIP_ERROR Instance::SetDefaultFridgeTemperature(int16_t temp)
    {
        if (temp != mDefaultFridgeTemperature)
        {
            ConcreteAttributePath path = ConcreteAttributePath(mEndpointId, mClusterId, Attributes::FridgeTemperatureDefault::Id);
            ReturnErrorOnFailure(storageDelagate.Put("default-fridge-temperature", temp));
            mDefaultFridgeTemperature = temp;
            MatterReportingAttributeChangeCallback(path);
        }
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR Instance::SetDefaultFreezerTemperature(int16_t temp)
    {
        if (temp != mDefaultFreezerTemperature)
        {
            ConcreteAttributePath path = ConcreteAttributePath(mEndpointId, mClusterId, Attributes::FreezerTemperatureDefault::Id);
            ReturnErrorOnFailure(storageDelagate.Put("default-freezer-temperature", temp));
            mDefaultFreezerTemperature = temp;
            MatterReportingAttributeChangeCallback(path);
        }
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR Instance::SetPreviousFridgeTemperature(int16_t temp)
    {
        if (temp != mPreviousFridgeTemperature)
        {
            ConcreteAttributePath path = ConcreteAttributePath(mEndpointId, mClusterId, Attributes::FridgePreviousTemperature::Id);
            ReturnErrorOnFailure(storageDelagate.Put("previous-fridge-temperature", temp));
            mPreviousFridgeTemperature = temp;
            MatterReportingAttributeChangeCallback(path);
        }
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR Instance::SetPreviousFreezerTemperature(int16_t temp)
    {
        if (temp != mDefaultFreezerTemperature)
        {
            ConcreteAttributePath path = ConcreteAttributePath(mEndpointId, mClusterId, Attributes::FreezerPreviousTemperature::Id);
            ReturnErrorOnFailure(storageDelagate.Put("previous-freezer-temperature", temp));
            mPreviousFridgeTemperature = temp;
            MatterReportingAttributeChangeCallback(path);
        }
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR Instance::SetSuperCoolTime(uint32_t time)
    {
        if (time != mSuperCoolTime)
        {
            ConcreteAttributePath path = ConcreteAttributePath(mEndpointId, mClusterId, Attributes::SuperCoolTime::Id);
            ReturnErrorOnFailure(storageDelagate.Put("super-cool-time", time));
            mSuperCoolTime = time;
            MatterReportingAttributeChangeCallback(path);
        }
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR Instance::SetSuperFreezeTime(uint32_t time)
    {
        if (time != mSuperFreezeTime)
        {
            ConcreteAttributePath path = ConcreteAttributePath(mEndpointId, mClusterId, Attributes::SuperFreezeTime::Id);
            ReturnErrorOnFailure(storageDelagate.Put("super-freeze-time", time));
            mSuperFreezeTime = time;
            MatterReportingAttributeChangeCallback(path);
        }
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR Instance::SetAlarmTime(uint32_t time)
    {
        if (time != mAlarmTime)
        {
            ConcreteAttributePath path = ConcreteAttributePath(mEndpointId, mClusterId, Attributes::AlarmTime::Id);
            ReturnErrorOnFailure(storageDelagate.Put("alarm-time", time));
            mAlarmTime = time;
            MatterReportingAttributeChangeCallback(path);
        }
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR Instance::SetResetTimeout(uint32_t timeout)
    {
        if (timeout != mResetTimeout)
        {
            ConcreteAttributePath path = ConcreteAttributePath(mEndpointId, mClusterId, Attributes::ResetTimeout::Id);
            ReturnErrorOnFailure(storageDelagate.Put("reset-timeout", timeout));
            mResetTimeout = timeout;
            MatterReportingAttributeChangeCallback(path);
        }
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR Instance::SetDisplayActiveTime(uint32_t time)
    {
        if (time != mDisplayActiveTime)
        {
            ConcreteAttributePath path = ConcreteAttributePath(mEndpointId, mClusterId, Attributes::DisplayActiveTime::Id);
            ReturnErrorOnFailure(storageDelagate.Put("display-active-time", time));
            mDisplayActiveTime = time;
            MatterReportingAttributeChangeCallback(path);
        }
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR Instance::SetDisplayErrorTime(uint32_t time)
    {
        if (time != mDisplayErrorTime)
        {
            ConcreteAttributePath path = ConcreteAttributePath(mEndpointId, mClusterId, Attributes::DisplayErrorTime::Id);
            ReturnErrorOnFailure(storageDelagate.Put("display-error-time", time));
            mDisplayErrorTime = time;
            MatterReportingAttributeChangeCallback(path);
        }
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR Instance::SetFridgeErrorMargin(int16_t margin)
    {
        if (margin != mFridgeErrorMargin)
        {
            ConcreteAttributePath path = ConcreteAttributePath(mEndpointId, mClusterId, Attributes::FridgeErrorMargin::Id);
            ReturnErrorOnFailure(storageDelagate.Put("fridge-error-margin", margin));
            mFridgeErrorMargin = margin;
            MatterReportingAttributeChangeCallback(path);
        }
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR Instance::SetFreezerErrorMargin(int16_t margin)
    {
        if (margin != mFreezerErrorMargin)
        {
            ConcreteAttributePath path = ConcreteAttributePath(mEndpointId, mClusterId, Attributes::FreezerErrorMargin::Id);
            ReturnErrorOnFailure(storageDelagate.Put("freezer-error-margin", margin));
            mFreezerErrorMargin = margin;
            MatterReportingAttributeChangeCallback(path);
        }
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR Instance::SetTemperatureErrorTime(uint32_t time)
    {
        if (time != mTemperatureErrorTime)
        {
            ConcreteAttributePath path = ConcreteAttributePath(mEndpointId, mClusterId, Attributes::TemperatureErrorTime::Id);
            ReturnErrorOnFailure(storageDelagate.Put("temperature-error-time", time));
            mTemperatureErrorTime = time;
            MatterReportingAttributeChangeCallback(path);
        }
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR Instance::SetCompressorState(bool state)
    {
        if (state != mCompressorState)
        {
            ConcreteAttributePath path = ConcreteAttributePath(mEndpointId, mClusterId, Attributes::CompressorState::Id);
            mCompressorState = state;
            MatterReportingAttributeChangeCallback(path);
        }
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR Instance::SetDefrostState(bool state)
    {
        if (state != mDefrostState)
        {
            ConcreteAttributePath path = ConcreteAttributePath(mEndpointId, mClusterId, Attributes::DefrostState::Id);
            mDefrostState = state;
            MatterReportingAttributeChangeCallback(path);
        }
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR Instance::Read(const ConcreteReadAttributePath &aPath, AttributeValueEncoder &aEncoder)
    {
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
        }
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR Instance::SetDefaultFridgeTemperature(AttributeValueDecoder &aDecoder)
    {
        int16_t newtemp;
        ReturnErrorOnFailure(aDecoder.Decode(newtemp));
        ReturnErrorOnFailure(SetDefaultFridgeTemperature(newtemp));
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR Instance::SetDefaultFreezerTemperature(AttributeValueDecoder &aDecoder)
    {
        int16_t newtemp;
        ReturnErrorOnFailure(aDecoder.Decode(newtemp));
        ReturnErrorOnFailure(SetDefaultFreezerTemperature(newtemp));
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR Instance::SetPreviousFridgeTemperature(AttributeValueDecoder &aDecoder)
    {
        int16_t newtemp;
        ReturnErrorOnFailure(aDecoder.Decode(newtemp));
        ReturnErrorOnFailure(SetPreviousFridgeTemperature(newtemp));
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR Instance::SetPreviousFreezerTemperature(AttributeValueDecoder &aDecoder)
    {
        int16_t newtemp;
        ReturnErrorOnFailure(aDecoder.Decode(newtemp));
        ReturnErrorOnFailure(SetPreviousFreezerTemperature(newtemp));
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR Instance::SetSuperCoolTime(AttributeValueDecoder &aDecoder)
    {
        uint32_t newtime;
        ReturnErrorOnFailure(aDecoder.Decode(newtime));
        ReturnErrorOnFailure(SetSuperCoolTime(newtime));
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR Instance::SetSuperFreezeTime(AttributeValueDecoder &aDecoder)
    {
        uint32_t newtime;
        ReturnErrorOnFailure(aDecoder.Decode(newtime));
        ReturnErrorOnFailure(SetSuperFreezeTime(newtime));
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR Instance::SetAlarmTime(AttributeValueDecoder &aDecoder)
    {
        uint32_t newtime;
        ReturnErrorOnFailure(aDecoder.Decode(newtime));
        ReturnErrorOnFailure(SetAlarmTime(newtime));
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR Instance::SetResetTimeout(AttributeValueDecoder &aDecoder)
    {
        uint32_t newtime;
        ReturnErrorOnFailure(aDecoder.Decode(newtime));
        ReturnErrorOnFailure(SetResetTimeout(newtime));
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR Instance::SetDisplayActiveTime(AttributeValueDecoder &aDecoder)
    {
        uint32_t newtime;
        ReturnErrorOnFailure(aDecoder.Decode(newtime));
        ReturnErrorOnFailure(SetDisplayActiveTime(newtime));
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR Instance::SetDisplayErrorTime(AttributeValueDecoder &aDecoder)
    {
        uint32_t newtime;
        ReturnErrorOnFailure(aDecoder.Decode(newtime));
        ReturnErrorOnFailure(SetDisplayErrorTime(newtime));
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR Instance::SetFridgeErrorMargin(AttributeValueDecoder &aDecoder)
    {
        int16_t newMargin;
        ReturnErrorOnFailure(aDecoder.Decode(newMargin));
        ReturnErrorOnFailure(SetFridgeErrorMargin(newMargin));
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR Instance::SetFreezerErrorMargin(AttributeValueDecoder &aDecoder)
    {
        int16_t newMargin;
        ReturnErrorOnFailure(aDecoder.Decode(newMargin));
        ReturnErrorOnFailure(SetFreezerErrorMargin(newMargin));
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR Instance::SetTemperatureErrorTime(AttributeValueDecoder &aDecoder)
    {
        uint32_t newtime;
        ReturnErrorOnFailure(aDecoder.Decode(newtime));
        ReturnErrorOnFailure(SetTemperatureErrorTime(newtime));
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR Instance::SetCompressorState(AttributeValueDecoder &aDecoder)
    {
        bool newState;
        ReturnErrorOnFailure(aDecoder.Decode(newState));
        ReturnErrorOnFailure(SetCompressorState(newState));
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR Instance::SetDefrostState(AttributeValueDecoder &aDecoder)
    {
        bool newState;
        ReturnErrorOnFailure(aDecoder.Decode(newState));
        ReturnErrorOnFailure(SetDefrostState(newState));
        return CHIP_NO_ERROR;
    }

    // Implements checking before attribute writes.
    CHIP_ERROR Instance::Write(const ConcreteDataAttributePath &attributePath, AttributeValueDecoder &aDecoder)
    {
        DataModel::Nullable<uint8_t> newMode;
        ReturnErrorOnFailure(aDecoder.Decode(newMode));

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
        }

        return CHIP_ERROR_INCORRECT_STATE;
    }
}


void MatterFreshRefrigeratorControllerPluginServerInitCallback()
{
}

/*
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
 */

#pragma once

#include <app-common/zap-generated/cluster-objects.h>
#include <app/util/af-types.h>
#include <app/AttributeAccessInterface.h>

namespace chip::DeviceLayer::PersistedStorage
{
    class KeyValueStoreManager;
}

namespace chip
{
    namespace app
    {
        namespace Clusters
        {
            namespace FreshRefrigeratorController
            {
                class Instance : public AttributeAccessInterface
                {
                public:
                    Instance(EndpointId aEndpointId, ClusterId aClusterId);

                    ~Instance() override;

                    CHIP_ERROR Init();

                    int16_t GetDefaultFridgeTemperature() const;

                    int16_t GetDefaultFreezerTemperature() const;

                    int16_t GetPreviousFridgeTemperature() const;

                    int16_t GetPreviousFreezerTemperature() const;

                    uint32_t GetSuperCoolTime() const;

                    uint32_t GetSuperFreezeTime() const;

                    uint32_t GetAlarmTime() const;

                    uint32_t GetResetTimeout() const;

                    uint32_t GetDisplayActiveTime() const;

                    uint32_t GetDisplayErrorTime() const;

                    int16_t GetFridgeErrorMargin() const;

                    int16_t GetFreezerErrorMargin() const;

                    uint32_t GetTemperatureErrorTime() const;

                    bool GetCompressorState() const;

                    bool GetDefrostState() const;

                    // Setters
                    CHIP_ERROR SetDefaultFridgeTemperature(int16_t temp);

                    CHIP_ERROR SetDefaultFreezerTemperature(int16_t temp);

                    CHIP_ERROR SetPreviousFridgeTemperature(int16_t temp);

                    CHIP_ERROR SetPreviousFreezerTemperature(int16_t temp);

                    CHIP_ERROR SetSuperCoolTime(uint32_t time);

                    CHIP_ERROR SetSuperFreezeTime(uint32_t time);

                    CHIP_ERROR SetAlarmTime(uint32_t time);

                    CHIP_ERROR SetResetTimeout(uint32_t timeout);

                    CHIP_ERROR SetDisplayActiveTime(uint32_t time);

                    CHIP_ERROR SetDisplayErrorTime(uint32_t time);

                    CHIP_ERROR SetFridgeErrorMargin(int16_t margin);

                    CHIP_ERROR SetFreezerErrorMargin(int16_t margin);

                    CHIP_ERROR SetTemperatureErrorTime(uint32_t time);

                    CHIP_ERROR SetCompressorState(bool state);

                    CHIP_ERROR SetDefrostState(bool state);

                private:
                    EndpointId mEndpointId;
                    ClusterId mClusterId;
                    int16_t mDefaultFridgeTemperature = 500;
                    int16_t mDefaultFreezerTemperature = -1800;
                    int16_t mPreviousFridgeTemperature = 500;
                    int16_t mPreviousFreezerTemperature = -1800;
                    uint32_t mSuperCoolTime = 21600; // 6 hours
                    uint32_t mSuperFreezeTime = 93600; // 26 hours
                    uint32_t mAlarmTime = 60; // 1 minute
                    uint32_t mResetTimeout = 7; // 7 seconds
                    uint32_t mDisplayActiveTime = 60; // 1 minute
                    uint32_t mDisplayErrorTime = 5; // 5 seconds
                    int16_t mFridgeErrorMargin = 1500; // 15 degrees
                    int16_t mFreezerErrorMargin = 1500; // 15 degrees
                    uint32_t mTemperatureErrorTime = 3600; // 1 hour
                    bool mCompressorState = false;
                    bool mDefrostState = false;

                    // AttributeAccessInterface
                    CHIP_ERROR Read(const ConcreteReadAttributePath &aPath, AttributeValueEncoder &aEncoder) override;

                    CHIP_ERROR Write(const ConcreteDataAttributePath &aPath, AttributeValueDecoder &aDecoder) override;


                    CHIP_ERROR SetDefaultFridgeTemperature(AttributeValueDecoder &aDecoder);
                    CHIP_ERROR SetDefaultFreezerTemperature(AttributeValueDecoder &aDecoder);
                    CHIP_ERROR SetPreviousFridgeTemperature(AttributeValueDecoder &aDecoder);
                    CHIP_ERROR SetPreviousFreezerTemperature(AttributeValueDecoder &aDecoder);
                    CHIP_ERROR SetSuperCoolTime(AttributeValueDecoder &aDecoder);
                    CHIP_ERROR SetSuperFreezeTime(AttributeValueDecoder &aDecoder);
                    CHIP_ERROR SetAlarmTime(AttributeValueDecoder &aDecoder);
                    CHIP_ERROR SetResetTimeout(AttributeValueDecoder &aDecoder);
                    CHIP_ERROR SetDisplayActiveTime(AttributeValueDecoder &aDecoder);
                    CHIP_ERROR SetDisplayErrorTime(AttributeValueDecoder &aDecoder);
                    CHIP_ERROR SetFridgeErrorMargin(AttributeValueDecoder &aDecoder);
                    CHIP_ERROR SetFreezerErrorMargin(AttributeValueDecoder &aDecoder);
                    CHIP_ERROR SetTemperatureErrorTime(AttributeValueDecoder &aDecoder);
                    CHIP_ERROR SetCompressorState(AttributeValueDecoder &aDecoder);
                    CHIP_ERROR SetDefrostState(AttributeValueDecoder &aDecoder);
                };
            } // namespace FreshRefrigeratorController
        } // namespace Clusters
    } // namespace app
} // namespace chip

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
#include "midea-air-conditioner-alarm-test-server.h"

#include <app-common/zap-generated/attributes/Accessors.h>
#include <app-common/zap-generated/cluster-enums.h>
#include <app-common/zap-generated/cluster-objects.h>
#include <app/EventLogging.h>
#include <app/InteractionModelEngine.h>
#include <app/util/attribute-storage.h>
#include <app/util/config.h>
#include <lib/support/BitFlags.h>

using namespace chip;
using namespace chip::app;
using namespace chip::app::Clusters;
using namespace chip::app::Clusters::MideaAirConditionerAlarmTest;
using namespace chip::app::Clusters::MideaAirConditionerAlarmTest::Attributes;
using namespace chip::DeviceLayer;
using chip::Protocols::InteractionModel::Status;

static constexpr size_t kMideaAirConditionerAlarmTestDelegateTableSize =
    MATTER_DM_MIDEA_ALARM_TEST_CLUSTER_SERVER_ENDPOINT_COUNT + CHIP_DEVICE_CONFIG_DYNAMIC_ENDPOINT_COUNT;

static_assert(kMideaAirConditionerAlarmTestDelegateTableSize <= kEmberInvalidEndpointIndex, "Midea Air Conditioner Alarm Delegate table size error");

namespace chip {
namespace app {
namespace Clusters {
namespace MideaAirConditionerAlarmTest {

Delegate * gDelegateTable[kMideaAirConditionerAlarmTestDelegateTableSize] = { nullptr };

Delegate * GetDelegate(EndpointId endpoint)
{
    uint16_t ep = emberAfGetClusterServerEndpointIndex(endpoint, MideaAirConditionerAlarmTest::Id,
                                                       MATTER_DM_MIDEA_ALARM_TEST_CLUSTER_SERVER_ENDPOINT_COUNT);
    return (ep >= kMideaAirConditionerAlarmTestDelegateTableSize ? nullptr : gDelegateTable[ep]);
}

void SetDefaultDelegate(EndpointId endpoint, Delegate * delegate)
{
    uint16_t ep = emberAfGetClusterServerEndpointIndex(endpoint, MideaAirConditionerAlarmTest::Id,
                                                       MATTER_DM_MIDEA_ALARM_TEST_CLUSTER_SERVER_ENDPOINT_COUNT);
    // if endpoint is found
    if (ep < kMideaAirConditionerAlarmTestDelegateTableSize)
    {
        gDelegateTable[ep] = delegate;
    }
}

} // namespace MideaAirConditionerAlarmTest
} // namespace Clusters
} // namespace app
} // namespace chip

MideaAirConditionerAlarmTestServer MideaAirConditionerAlarmTestServer::instance;

MideaAirConditionerAlarmTestServer & MideaAirConditionerAlarmTestServer::Instance()
{
    return instance;
}

Status MideaAirConditionerAlarmTestServer::GetMaskValue(EndpointId endpoint, BitMask<AlarmBitmap> * mask)
{
    Status status = Attributes::Mask::Get(endpoint, mask);
    if (status != Status::Success)
    {
        ChipLogProgress(Zcl, "Midea Air Conditioner Alarm: ERR: reading  mask, err:0x%x", to_underlying(status));
        return status;
    }
    return status;
}

Status MideaAirConditionerAlarmTestServer::GetLatchValue(EndpointId endpoint, BitMask<AlarmBitmap> * latch)
{
    if (!HasResetFeature(endpoint))
    {
        ChipLogProgress(Zcl, "Midea Air Conditioner Alarm feature: Unsupport Latch attribute");
        return Status::UnsupportedAttribute;
    }

    Status status = Attributes::Latch::Get(endpoint, latch);
    if (status != Status::Success)
    {
        ChipLogProgress(Zcl, "Midea Air Conditioner Alarm: ERR: reading  latch, err:0x%x", to_underlying(status));
        return status;
    }
    return status;
}

Status MideaAirConditionerAlarmTestServer::GetStateValue(EndpointId endpoint, BitMask<AlarmBitmap> * state)
{
    Status status = Attributes::State::Get(endpoint, state);
    if (status != Status::Success)
    {
        ChipLogProgress(Zcl, "Midea Air Conditioner Alarm: ERR: get state, err:0x%x", to_underlying(status));
        return status;
    }
    return status;
}

Status MideaAirConditionerAlarmTestServer::GetSupportedValue(EndpointId endpoint, BitMask<AlarmBitmap> * supported)
{
    Status status = Attributes::Supported::Get(endpoint, supported);
    if (status != Status::Success)
    {
        ChipLogProgress(Zcl, "Midea Air Conditioner Alarm: ERR: reading  supported, err:0x%x", to_underlying(status));
    }
    return status;
}

Status MideaAirConditionerAlarmTestServer::SetSupportedValue(EndpointId endpoint, const BitMask<AlarmBitmap> supported)
{
    Status status = Status::Success;

    if ((status = Attributes::Supported::Set(endpoint, supported)) != Status::Success)
    {
        ChipLogProgress(Zcl, "Midea Air Conditioner Alarm: ERR: writing supported, err:0x%x", to_underlying(status));
        return status;
    }

    // Whenever there is change in Supported attribute, Latch should change accordingly (if possible).
    BitMask<AlarmBitmap> latch;
    if (GetLatchValue(endpoint, &latch) == Status::Success && !supported.HasAll(latch))
    {
        latch  = latch & supported;
        status = SetLatchValue(endpoint, latch);
    }

    // Whenever there is change in Supported attribute, Mask, State should change accordingly.
    BitMask<AlarmBitmap> mask;
    if ((status = GetMaskValue(endpoint, &mask)) != Status::Success)
    {
        return status;
    }

    if (!supported.HasAll(mask))
    {
        mask   = supported & mask;
        status = SetMaskValue(endpoint, mask);
    }
    return status;
}

Status MideaAirConditionerAlarmTestServer::SetMaskValue(EndpointId endpoint, const BitMask<AlarmBitmap> mask)
{
    BitMask<AlarmBitmap> supported;
    if (Status::Success != GetSupportedValue(endpoint, &supported) || !supported.HasAll(mask))
    {
        ChipLogProgress(Zcl, "Midea Air Conditioner Alarm: ERR: Mask is not supported");
        return Status::Failure;
    }

    Status status = Status::Success;
    if ((status = Attributes::Mask::Set(endpoint, mask)) != Status::Success)
    {
        ChipLogProgress(Zcl, "Midea Air Conditioner Alarm: ERR: writing  mask, err:0x%x", to_underlying(status));
        return status;
    }

    // Whenever there is change in Mask, State should change accordingly.
    BitMask<AlarmBitmap> state;
    status = GetStateValue(endpoint, &state);
    if (status != Status::Success)
    {
        return status;
    }

    if (!mask.HasAll(state))
    {
        state  = mask & state;
        status = SetStateValue(endpoint, state, true);
    }
    return status;
}

Status MideaAirConditionerAlarmTestServer::SetLatchValue(EndpointId endpoint, const BitMask<AlarmBitmap> latch)
{
    if (!HasResetFeature(endpoint))
    {
        ChipLogProgress(Zcl, "Midea Air Conditioner Alarm feature: Unsupport Latch attribute");
        return Status::UnsupportedAttribute;
    }

    BitMask<AlarmBitmap> supported;
    if (Status::Success != GetSupportedValue(endpoint, &supported) || !supported.HasAll(latch))
    {
        ChipLogProgress(Zcl, "Midea Air Conditioner Alarm: ERR: Latch is not supported");
        return Status::Failure;
    }

    Status status = Attributes::Latch::Set(endpoint, latch);
    if (status != Status::Success)
    {
        ChipLogProgress(Zcl, "Midea Air Conditioner Alarm: ERR: writing  latch, err:0x%x", to_underlying(status));
        return status;
    }

    return status;
}

Status MideaAirConditionerAlarmTestServer::SetStateValue(EndpointId endpoint, const BitMask<AlarmBitmap> newState, bool ignoreLatchState)
{
    BitMask<AlarmBitmap> supported;
    BitMask<AlarmBitmap> finalNewState;
    finalNewState.Set(newState);

    if (Status::Success != GetSupportedValue(endpoint, &supported) || !supported.HasAll(finalNewState))
    {
        ChipLogProgress(Zcl, "Midea Air Conditioner Alarm: ERR: Alarm is not supported");
        return Status::Failure;
    }

    BitMask<AlarmBitmap> mask;
    if (Status::Success != GetMaskValue(endpoint, &mask) || !mask.HasAll(finalNewState))
    {
        ChipLogProgress(Zcl, "Midea Air Conditioner Alarm: ERR: Alarm is suppressed");
        return Status::Failure;
    }

    Status status = Status::Success;
    BitMask<AlarmBitmap> currentState;
    status = Attributes::State::Get(endpoint, &currentState);
    if (status != Status::Success)
    {
        ChipLogProgress(Zcl, "Midea Air Conditioner Alarm: ERR: reading  state, err:0x%x", to_underlying(status));
        return status;
    }

    BitMask<AlarmBitmap> latch;
    if (!ignoreLatchState && (GetLatchValue(endpoint, &latch) == Status::Success))
    {
        // Restore bits that have their Latch bit set.
        auto bitsToKeep = latch & currentState;
        finalNewState.Set(bitsToKeep);
    }

    // Store the new value of the State attribute.
    status = Attributes::State::Set(endpoint, finalNewState);
    if (status != Status::Success)
    {
        ChipLogProgress(Zcl, "Midea Air Conditioner Alarm: ERR: writing  state, err:0x%x", to_underlying(status));
        return status;
    }

    // Generate Notify event.
    BitMask<AlarmBitmap> becameActive;
    becameActive.Set(finalNewState).Clear(currentState);
    BitMask<AlarmBitmap> becameInactive;
    becameInactive.Set(currentState).Clear(finalNewState);

    SendNotifyEvent(endpoint, becameActive, becameInactive, finalNewState, mask);
    return status;
}

Status MideaAirConditionerAlarmTestServer::ResetLatchedAlarms(EndpointId endpoint, const BitMask<AlarmBitmap> alarms)
{
    BitMask<AlarmBitmap> supported;
    if (Status::Success != GetSupportedValue(endpoint, &supported) || !supported.HasAll(alarms))
    {
        ChipLogProgress(Zcl, "Midea Air Conditioner Alarm: ERR: Alarm is not supported");
        return Status::Failure;
    }

    BitMask<AlarmBitmap> state;
    if (GetStateValue(endpoint, &state) != Status::Success)
    {
        return Status::Failure;
    }

    state.Clear(alarms);
    return SetStateValue(endpoint, state, true);
}

bool MideaAirConditionerAlarmTestServer::HasResetFeature(EndpointId endpoint)
{
    uint32_t featureMap = 0;
    if (Attributes::FeatureMap::Get(endpoint, &featureMap) != Status::Success)
    {
        return false;
    }

    if (featureMap & to_underlying(Feature::kReset))
    {
        return true;
    }
    return false;
}

void MideaAirConditionerAlarmTestServer::SendNotifyEvent(EndpointId endpointId, BitMask<AlarmBitmap> becameActive, BitMask<AlarmBitmap> becameInactive,
                                            BitMask<AlarmBitmap> newState, BitMask<AlarmBitmap> mask)
{
    Events::Notify::Type event{ .active = becameActive, .inactive = becameInactive, .state = newState, .mask = mask };
    EventNumber eventNumber;
    CHIP_ERROR error = LogEvent(event, endpointId, eventNumber);
    if (CHIP_NO_ERROR != error)
    {
        ChipLogError(Zcl, "[Notify] Unable to send notify event: %s [endpointId=%d]", error.AsString(), endpointId);
    }
}

static Status ModifyEnabledHandler(const app::ConcreteCommandPath & commandPath, const BitMask<AlarmBitmap> mask)
{
    EndpointId endpoint = commandPath.mEndpointId;
    BitMask<AlarmBitmap> supported;

    if (MideaAirConditionerAlarmTestServer::Instance().GetSupportedValue(endpoint, &supported) != Status::Success)
    {
        return Status::Failure;
    }

    // receives this command with a Mask that includes bits that are set for alarms which are not supported
    if (!supported.HasAll(mask))
    {
        return Status::InvalidCommand;
    }

    // A server that is unable to enable a currently suppressed alarm,
    // or is unable to suppress a currently enabled alarm SHALL respond
    // with a status code of FAILURE
    Delegate * delegate = MideaAirConditionerAlarmTest::GetDelegate(endpoint);
    if (delegate && !(delegate->ModifyEnabledAlarmsCallback(mask)))
    {
        ChipLogProgress(Zcl, "Unable to modify enabled alarms");
        return Status::Failure;
    }
    // The cluster will do this update if delegate.ModifyEnabledAlarmsCallback() returns true.
    if (MideaAirConditionerAlarmTestServer::Instance().SetMaskValue(endpoint, mask) != Status::Success)
    {
        return Status::Failure;
    }
    return Status::Success;
}

static Status ResetHandler(const app::ConcreteCommandPath & commandPath, const BitMask<AlarmBitmap> alarms)
{
    EndpointId endpoint = commandPath.mEndpointId;

    if (!MideaAirConditionerAlarmTestServer::Instance().HasResetFeature(endpoint))
    {
        ChipLogProgress(Zcl, "Midea Air Conditioner Alarm feature: Unsupport Reset Command");
        return Status::UnsupportedCommand;
    }

    // A server that is unable to reset alarms SHALL respond with a status code of FAILURE
    Delegate * delegate = MideaAirConditionerAlarmTest::GetDelegate(endpoint);
    if (delegate && !(delegate->ResetAlarmsCallback(alarms)))
    {
        ChipLogProgress(Zcl, "Unable to reset alarms");
        return Status::Failure;
    }

    // The cluster will do this update if delegate.ResetAlarmsCallback() returns true.
    if (MideaAirConditionerAlarmTestServer::Instance().ResetLatchedAlarms(endpoint, alarms) != Status::Success)
    {
        ChipLogProgress(Zcl, "reset alarms fail");
        return Status::Failure;
    }
    return Status::Success;
}

bool emberAfMideaAirConditionerAlarmTestClusterResetCallback(app::CommandHandler * commandObj, const app::ConcreteCommandPath & commandPath,
                                                const Commands::Reset::DecodableType & commandData)
{
    auto & alarms = commandData.alarms;

    Status status = ResetHandler(commandPath, alarms);
    commandObj->AddStatus(commandPath, status);

    return true;
}

// bool emberAfMideaAirConditionerAlarmTestClusterModifyEnabledAlarmsCallback(app::CommandHandler * commandObj,
//                                                               const app::ConcreteCommandPath & commandPath,
//                                                               const Commands::ModifyEnabledAlarms::DecodableType & commandData)
// {
//     auto & mask   = commandData.mask;
//     Status status = ModifyEnabledHandler(commandPath, mask);
//     commandObj->AddStatus(commandPath, status);

//     return true;
// }

void MatterMideaAirConditionerAlarmTestPluginServerInitCallback() {}

void MatterMideaAirConditionerAlarmTestPluginServerShutdownCallback() {}
// DO NOT EDIT MANUALLY - Generated file
//
// Cluster metadata information for cluster FreshWaterHeaterController (cluster code: 367524869/0x15E7FC05)
// based on src/controller/data_model/controller-clusters.matter
#pragma once

#include <app/data-model-provider/MetadataTypes.h>
#include <array>
#include <lib/core/DataModelTypes.h>

#include <cstdint>

#include <clusters/FreshWaterHeaterController/Ids.h>

namespace chip {
namespace app {
namespace Clusters {
namespace FreshWaterHeaterController {

inline constexpr uint32_t kRevision = 1;

namespace Attributes {

namespace ColdWaterTemperature {
inline constexpr DataModel::AttributeEntry kMetadataEntry(ColdWaterTemperature::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, Access::Privilege::kOperate);
} // namespace ColdWaterTemperature
namespace ShowerTemperature {
inline constexpr DataModel::AttributeEntry kMetadataEntry(ShowerTemperature::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, Access::Privilege::kOperate);
} // namespace ShowerTemperature
namespace ShowerHysteresis {
inline constexpr DataModel::AttributeEntry kMetadataEntry(ShowerHysteresis::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, Access::Privilege::kOperate);
} // namespace ShowerHysteresis
namespace ShowerState {
inline constexpr DataModel::AttributeEntry kMetadataEntry(ShowerState::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace ShowerState
namespace DefaultShowerFlowLPM {
inline constexpr DataModel::AttributeEntry kMetadataEntry(DefaultShowerFlowLPM::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, Access::Privilege::kOperate);
} // namespace DefaultShowerFlowLPM
namespace StandardModeSetpoint {
inline constexpr DataModel::AttributeEntry kMetadataEntry(StandardModeSetpoint::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, Access::Privilege::kOperate);
} // namespace StandardModeSetpoint
namespace EcoModeSetpoint {
inline constexpr DataModel::AttributeEntry kMetadataEntry(EcoModeSetpoint::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, Access::Privilege::kOperate);
} // namespace EcoModeSetpoint
namespace DefaultBoostModeSetpoint {
inline constexpr DataModel::AttributeEntry kMetadataEntry(DefaultBoostModeSetpoint::Id,
                                                          BitFlags<DataModel::AttributeQualityFlags>(), Access::Privilege::kView,
                                                          std::nullopt);
} // namespace DefaultBoostModeSetpoint
namespace DisplayTemperatureStep {
inline constexpr DataModel::AttributeEntry kMetadataEntry(DisplayTemperatureStep::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, Access::Privilege::kOperate);
} // namespace DisplayTemperatureStep
namespace ResetTimeout {
inline constexpr DataModel::AttributeEntry kMetadataEntry(ResetTimeout::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, Access::Privilege::kOperate);
} // namespace ResetTimeout
namespace CoolDownTimeout {
inline constexpr DataModel::AttributeEntry kMetadataEntry(CoolDownTimeout::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, Access::Privilege::kOperate);
} // namespace CoolDownTimeout
namespace ResetCounterTimeout {
inline constexpr DataModel::AttributeEntry kMetadataEntry(ResetCounterTimeout::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, Access::Privilege::kOperate);
} // namespace ResetCounterTimeout
namespace DisplayActiveTimeout {
inline constexpr DataModel::AttributeEntry kMetadataEntry(DisplayActiveTimeout::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, Access::Privilege::kOperate);
} // namespace DisplayActiveTimeout
namespace DisplayErrorTimeout {
inline constexpr DataModel::AttributeEntry kMetadataEntry(DisplayErrorTimeout::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, Access::Privilege::kOperate);
} // namespace DisplayErrorTimeout
namespace DisplayTargetTimeout {
inline constexpr DataModel::AttributeEntry kMetadataEntry(DisplayTargetTimeout::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, Access::Privilege::kOperate);
} // namespace DisplayTargetTimeout
namespace TemperatureSensorMinValid {
inline constexpr DataModel::AttributeEntry kMetadataEntry(TemperatureSensorMinValid::Id,
                                                          BitFlags<DataModel::AttributeQualityFlags>(), Access::Privilege::kView,
                                                          Access::Privilege::kOperate);
} // namespace TemperatureSensorMinValid
namespace TemperatureSensorMaxValid {
inline constexpr DataModel::AttributeEntry kMetadataEntry(TemperatureSensorMaxValid::Id,
                                                          BitFlags<DataModel::AttributeQualityFlags>(), Access::Privilege::kView,
                                                          Access::Privilege::kOperate);
} // namespace TemperatureSensorMaxValid
namespace OverheatThresholdTemperature {
inline constexpr DataModel::AttributeEntry kMetadataEntry(OverheatThresholdTemperature::Id,
                                                          BitFlags<DataModel::AttributeQualityFlags>(), Access::Privilege::kView,
                                                          Access::Privilege::kOperate);
} // namespace OverheatThresholdTemperature
namespace RapidRiseDelta {
inline constexpr DataModel::AttributeEntry kMetadataEntry(RapidRiseDelta::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, Access::Privilege::kOperate);
} // namespace RapidRiseDelta
namespace RapidRiseWindow {
inline constexpr DataModel::AttributeEntry kMetadataEntry(RapidRiseWindow::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, Access::Privilege::kOperate);
} // namespace RapidRiseWindow
namespace PreviousTargetHeaterTemperature {
inline constexpr DataModel::AttributeEntry kMetadataEntry(PreviousTargetHeaterTemperature::Id,
                                                          BitFlags<DataModel::AttributeQualityFlags>(), Access::Privilege::kView,
                                                          std::nullopt);
} // namespace PreviousTargetHeaterTemperature
namespace HeaterMaximumPower {
inline constexpr DataModel::AttributeEntry kMetadataEntry(HeaterMaximumPower::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, Access::Privilege::kOperate);
} // namespace HeaterMaximumPower
namespace DiagnosticsConfirmTimeList {
inline constexpr DataModel::AttributeEntry
    kMetadataEntry(DiagnosticsConfirmTimeList::Id,
                   BitFlags<DataModel::AttributeQualityFlags>(DataModel::AttributeQualityFlags::kListAttribute),
                   Access::Privilege::kView, Access::Privilege::kOperate);
} // namespace DiagnosticsConfirmTimeList
namespace DiagnosticsRehabTimeList {
inline constexpr DataModel::AttributeEntry
    kMetadataEntry(DiagnosticsRehabTimeList::Id,
                   BitFlags<DataModel::AttributeQualityFlags>(DataModel::AttributeQualityFlags::kListAttribute),
                   Access::Privilege::kView, Access::Privilege::kOperate);
} // namespace DiagnosticsRehabTimeList
namespace RequiresAnodeChange {
inline constexpr DataModel::AttributeEntry kMetadataEntry(RequiresAnodeChange::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace RequiresAnodeChange
namespace MaximumBoostTime {
inline constexpr DataModel::AttributeEntry kMetadataEntry(MaximumBoostTime::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, Access::Privilege::kOperate);
} // namespace MaximumBoostTime
namespace CurrentBoostModeSetpoint {
inline constexpr DataModel::AttributeEntry kMetadataEntry(CurrentBoostModeSetpoint::Id,
                                                          BitFlags<DataModel::AttributeQualityFlags>(), Access::Privilege::kView,
                                                          std::nullopt);
} // namespace CurrentBoostModeSetpoint
namespace ErrorCode {
inline constexpr DataModel::AttributeEntry kMetadataEntry(ErrorCode::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace ErrorCode
namespace AntiLegionellaState {
inline constexpr DataModel::AttributeEntry kMetadataEntry(AntiLegionellaState::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace AntiLegionellaState
namespace EnergyReportInterval {
inline constexpr DataModel::AttributeEntry kMetadataEntry(EnergyReportInterval::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, Access::Privilege::kOperate);
} // namespace EnergyReportInterval
constexpr std::array<DataModel::AttributeEntry, 30> kMandatoryMetadata = {
    ColdWaterTemperature::kMetadataEntry,
    ShowerTemperature::kMetadataEntry,
    ShowerHysteresis::kMetadataEntry,
    ShowerState::kMetadataEntry,
    DefaultShowerFlowLPM::kMetadataEntry,
    StandardModeSetpoint::kMetadataEntry,
    EcoModeSetpoint::kMetadataEntry,
    DefaultBoostModeSetpoint::kMetadataEntry,
    DisplayTemperatureStep::kMetadataEntry,
    ResetTimeout::kMetadataEntry,
    CoolDownTimeout::kMetadataEntry,
    ResetCounterTimeout::kMetadataEntry,
    DisplayActiveTimeout::kMetadataEntry,
    DisplayErrorTimeout::kMetadataEntry,
    DisplayTargetTimeout::kMetadataEntry,
    TemperatureSensorMinValid::kMetadataEntry,
    TemperatureSensorMaxValid::kMetadataEntry,
    OverheatThresholdTemperature::kMetadataEntry,
    RapidRiseDelta::kMetadataEntry,
    RapidRiseWindow::kMetadataEntry,
    PreviousTargetHeaterTemperature::kMetadataEntry,
    HeaterMaximumPower::kMetadataEntry,
    DiagnosticsConfirmTimeList::kMetadataEntry,
    DiagnosticsRehabTimeList::kMetadataEntry,
    RequiresAnodeChange::kMetadataEntry,
    MaximumBoostTime::kMetadataEntry,
    CurrentBoostModeSetpoint::kMetadataEntry,
    ErrorCode::kMetadataEntry,
    AntiLegionellaState::kMetadataEntry,
    EnergyReportInterval::kMetadataEntry,

};

} // namespace Attributes

namespace Commands {

namespace AnodeChangeRequest {
inline constexpr DataModel::AcceptedCommandEntry kMetadataEntry(AnodeChangeRequest::Id, BitFlags<DataModel::CommandQualityFlags>(),
                                                                Access::Privilege::kAdminister);
} // namespace AnodeChangeRequest
namespace AnodeChangeConfirmed {
inline constexpr DataModel::AcceptedCommandEntry
    kMetadataEntry(AnodeChangeConfirmed::Id, BitFlags<DataModel::CommandQualityFlags>(), Access::Privilege::kAdminister);
} // namespace AnodeChangeConfirmed

} // namespace Commands

namespace Events {
namespace AntiLegionellaCycleStarted {
inline constexpr DataModel::EventEntry kMetadataEntry{ Access::Privilege::kView };
} // namespace AntiLegionellaCycleStarted
namespace AntiLegionellaCycleCompleted {
inline constexpr DataModel::EventEntry kMetadataEntry{ Access::Privilege::kView };
} // namespace AntiLegionellaCycleCompleted

} // namespace Events
} // namespace FreshWaterHeaterController
} // namespace Clusters
} // namespace app
} // namespace chip

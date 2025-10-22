// DO NOT EDIT MANUALLY - Generated file
//
// Cluster metadata information for cluster FreshWaterHeaterController (cluster code: 367524869/0x15E7FC05)
// based on src/controller/data_model/controller-clusters.matter
#pragma once

#include <app/data-model-provider/MetadataTypes.h>
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
                                                          Access::Privilege::kView, std::nullopt);
} // namespace ColdWaterTemperature
namespace ShowerTemperature {
inline constexpr DataModel::AttributeEntry kMetadataEntry(ShowerTemperature::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace ShowerTemperature
namespace ShowerHysteresis {
inline constexpr DataModel::AttributeEntry kMetadataEntry(ShowerHysteresis::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace ShowerHysteresis
namespace ShowerState {
inline constexpr DataModel::AttributeEntry kMetadataEntry(ShowerState::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace ShowerState
namespace DefaultShowerFlowLPM {
inline constexpr DataModel::AttributeEntry kMetadataEntry(DefaultShowerFlowLPM::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace DefaultShowerFlowLPM
namespace StandardModeSetpoint {
inline constexpr DataModel::AttributeEntry kMetadataEntry(StandardModeSetpoint::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace StandardModeSetpoint
namespace EcoModeSetpoint {
inline constexpr DataModel::AttributeEntry kMetadataEntry(EcoModeSetpoint::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace EcoModeSetpoint
namespace BoostModeSetpoint {
inline constexpr DataModel::AttributeEntry kMetadataEntry(BoostModeSetpoint::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace BoostModeSetpoint
namespace DisplayTemperatureStep {
inline constexpr DataModel::AttributeEntry kMetadataEntry(DisplayTemperatureStep::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace DisplayTemperatureStep
namespace ResetTimeout {
inline constexpr DataModel::AttributeEntry kMetadataEntry(ResetTimeout::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace ResetTimeout
namespace CoolDownTimeout {
inline constexpr DataModel::AttributeEntry kMetadataEntry(CoolDownTimeout::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace CoolDownTimeout
namespace ResetCounterTimeout {
inline constexpr DataModel::AttributeEntry kMetadataEntry(ResetCounterTimeout::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace ResetCounterTimeout
namespace DisplayActiveTimeout {
inline constexpr DataModel::AttributeEntry kMetadataEntry(DisplayActiveTimeout::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace DisplayActiveTimeout
namespace DisplayErrorTimeout {
inline constexpr DataModel::AttributeEntry kMetadataEntry(DisplayErrorTimeout::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace DisplayErrorTimeout
namespace DisplayTargetTimeout {
inline constexpr DataModel::AttributeEntry kMetadataEntry(DisplayTargetTimeout::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace DisplayTargetTimeout
namespace TemperatureSensorMinValid {
inline constexpr DataModel::AttributeEntry kMetadataEntry(TemperatureSensorMinValid::Id,
                                                          BitFlags<DataModel::AttributeQualityFlags>(), Access::Privilege::kView,
                                                          std::nullopt);
} // namespace TemperatureSensorMinValid
namespace TemperatureSensorMaxValid {
inline constexpr DataModel::AttributeEntry kMetadataEntry(TemperatureSensorMaxValid::Id,
                                                          BitFlags<DataModel::AttributeQualityFlags>(), Access::Privilege::kView,
                                                          std::nullopt);
} // namespace TemperatureSensorMaxValid
namespace OverheatThresholdTemperature {
inline constexpr DataModel::AttributeEntry kMetadataEntry(OverheatThresholdTemperature::Id,
                                                          BitFlags<DataModel::AttributeQualityFlags>(), Access::Privilege::kView,
                                                          std::nullopt);
} // namespace OverheatThresholdTemperature
namespace RapidRiseDelta {
inline constexpr DataModel::AttributeEntry kMetadataEntry(RapidRiseDelta::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace RapidRiseDelta
namespace RapidRiseWindow {
inline constexpr DataModel::AttributeEntry kMetadataEntry(RapidRiseWindow::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace RapidRiseWindow
namespace PreviousTargetHeaterTemperature {
inline constexpr DataModel::AttributeEntry kMetadataEntry(PreviousTargetHeaterTemperature::Id,
                                                          BitFlags<DataModel::AttributeQualityFlags>(), Access::Privilege::kView,
                                                          std::nullopt);
} // namespace PreviousTargetHeaterTemperature
namespace HeaterMaximumPower {
inline constexpr DataModel::AttributeEntry kMetadataEntry(HeaterMaximumPower::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace HeaterMaximumPower
namespace DiagnosticsConfirmTimeList {
inline constexpr DataModel::AttributeEntry
    kMetadataEntry(DiagnosticsConfirmTimeList::Id,
                   BitFlags<DataModel::AttributeQualityFlags>(DataModel::AttributeQualityFlags::kListAttribute),
                   Access::Privilege::kView, std::nullopt);
} // namespace DiagnosticsConfirmTimeList
namespace DiagnosticsRehabTimeList {
inline constexpr DataModel::AttributeEntry
    kMetadataEntry(DiagnosticsRehabTimeList::Id,
                   BitFlags<DataModel::AttributeQualityFlags>(DataModel::AttributeQualityFlags::kListAttribute),
                   Access::Privilege::kView, std::nullopt);
} // namespace DiagnosticsRehabTimeList

} // namespace Attributes

namespace Commands {
namespace AnodeChangeRequest {
inline constexpr DataModel::AcceptedCommandEntry kMetadataEntry(AnodeChangeRequest::Id, BitFlags<DataModel::CommandQualityFlags>(),
                                                                Access::Privilege::kAdminister);
} // namespace AnodeChangeRequest

} // namespace Commands
} // namespace FreshWaterHeaterController
} // namespace Clusters
} // namespace app
} // namespace chip

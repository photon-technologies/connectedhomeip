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
namespace ShowerPercent {
inline constexpr DataModel::AttributeEntry kMetadataEntry(ShowerPercent::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace ShowerPercent
namespace ShowerState {
inline constexpr DataModel::AttributeEntry kMetadataEntry(ShowerState::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace ShowerState
namespace DisplayUpdateInterval {
inline constexpr DataModel::AttributeEntry kMetadataEntry(DisplayUpdateInterval::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace DisplayUpdateInterval
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

// DO NOT EDIT MANUALLY - Generated file
//
// Cluster metadata information for cluster FreshRefrigeratorController (cluster code: 367524867/0x15E7FC03)
// based on src/controller/data_model/controller-clusters.matter
#pragma once

#include <app/data-model-provider/MetadataTypes.h>
#include <lib/core/DataModelTypes.h>

#include <cstdint>

#include <clusters/FreshRefrigeratorController/Ids.h>

namespace chip {
namespace app {
namespace Clusters {
namespace FreshRefrigeratorController {

inline constexpr uint32_t kRevision = 1;

namespace Attributes {
namespace FridgeTemperatureDefault {
inline constexpr DataModel::AttributeEntry kMetadataEntry(FridgeTemperatureDefault::Id,
                                                          BitFlags<DataModel::AttributeQualityFlags>(), Access::Privilege::kView,
                                                          Access::Privilege::kOperate);
} // namespace FridgeTemperatureDefault
namespace FreezerTemperatureDefault {
inline constexpr DataModel::AttributeEntry kMetadataEntry(FreezerTemperatureDefault::Id,
                                                          BitFlags<DataModel::AttributeQualityFlags>(), Access::Privilege::kView,
                                                          Access::Privilege::kOperate);
} // namespace FreezerTemperatureDefault
namespace FridgePreviousTemperature {
inline constexpr DataModel::AttributeEntry kMetadataEntry(FridgePreviousTemperature::Id,
                                                          BitFlags<DataModel::AttributeQualityFlags>(), Access::Privilege::kView,
                                                          std::nullopt);
} // namespace FridgePreviousTemperature
namespace FreezerPreviousTemperature {
inline constexpr DataModel::AttributeEntry kMetadataEntry(FreezerPreviousTemperature::Id,
                                                          BitFlags<DataModel::AttributeQualityFlags>(), Access::Privilege::kView,
                                                          std::nullopt);
} // namespace FreezerPreviousTemperature
namespace SuperCoolTime {
inline constexpr DataModel::AttributeEntry kMetadataEntry(SuperCoolTime::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, Access::Privilege::kOperate);
} // namespace SuperCoolTime
namespace SuperFreezeTime {
inline constexpr DataModel::AttributeEntry kMetadataEntry(SuperFreezeTime::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, Access::Privilege::kOperate);
} // namespace SuperFreezeTime
namespace AlarmTime {
inline constexpr DataModel::AttributeEntry kMetadataEntry(AlarmTime::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, Access::Privilege::kOperate);
} // namespace AlarmTime
namespace ResetTimeout {
inline constexpr DataModel::AttributeEntry kMetadataEntry(ResetTimeout::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, Access::Privilege::kOperate);
} // namespace ResetTimeout
namespace DisplayActiveTime {
inline constexpr DataModel::AttributeEntry kMetadataEntry(DisplayActiveTime::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, Access::Privilege::kOperate);
} // namespace DisplayActiveTime
namespace DisplayErrorTime {
inline constexpr DataModel::AttributeEntry kMetadataEntry(DisplayErrorTime::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, Access::Privilege::kOperate);
} // namespace DisplayErrorTime
namespace CompressorState {
inline constexpr DataModel::AttributeEntry kMetadataEntry(CompressorState::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace CompressorState
namespace DefrostState {
inline constexpr DataModel::AttributeEntry kMetadataEntry(DefrostState::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace DefrostState
namespace FridgeErrorMargin {
inline constexpr DataModel::AttributeEntry kMetadataEntry(FridgeErrorMargin::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, Access::Privilege::kOperate);
} // namespace FridgeErrorMargin
namespace FreezerErrorMargin {
inline constexpr DataModel::AttributeEntry kMetadataEntry(FreezerErrorMargin::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, Access::Privilege::kOperate);
} // namespace FreezerErrorMargin
namespace TemperatureErrorTime {
inline constexpr DataModel::AttributeEntry kMetadataEntry(TemperatureErrorTime::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, Access::Privilege::kOperate);
} // namespace TemperatureErrorTime
namespace FridgeDoorState {
inline constexpr DataModel::AttributeEntry kMetadataEntry(FridgeDoorState::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace FridgeDoorState
namespace FreezerDoorState {
inline constexpr DataModel::AttributeEntry kMetadataEntry(FreezerDoorState::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace FreezerDoorState
namespace DefrostTemperature {
inline constexpr DataModel::AttributeEntry kMetadataEntry(DefrostTemperature::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace DefrostTemperature

} // namespace Attributes

namespace Commands {} // namespace Commands
} // namespace FreshRefrigeratorController
} // namespace Clusters
} // namespace app
} // namespace chip

// DO NOT EDIT MANUALLY - Generated file
//
// Cluster metadata information for cluster FreshMideaController (cluster code: 367524868/0x15E7FC04)
// based on src/controller/data_model/controller-clusters.matter
#pragma once

#include <app/data-model-provider/MetadataTypes.h>
#include <lib/core/DataModelTypes.h>

#include <cstdint>

#include <clusters/FreshMideaController/Ids.h>

namespace chip {
namespace app {
namespace Clusters {
namespace FreshMideaController {

inline constexpr uint32_t kRevision = 1;

namespace Attributes {
namespace Beep {
inline constexpr DataModel::AttributeEntry kMetadataEntry(Beep::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, Access::Privilege::kOperate);
} // namespace Beep
namespace Light {
inline constexpr DataModel::AttributeEntry kMetadataEntry(Light::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, Access::Privilege::kOperate);
} // namespace Light
namespace TurboMode {
inline constexpr DataModel::AttributeEntry kMetadataEntry(TurboMode::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, Access::Privilege::kOperate);
} // namespace TurboMode
namespace EcoMode {
inline constexpr DataModel::AttributeEntry kMetadataEntry(EcoMode::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, Access::Privilege::kOperate);
} // namespace EcoMode
namespace FrostProtectionMode {
inline constexpr DataModel::AttributeEntry kMetadataEntry(FrostProtectionMode::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, Access::Privilege::kOperate);
} // namespace FrostProtectionMode
namespace SleepMode {
inline constexpr DataModel::AttributeEntry kMetadataEntry(SleepMode::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, Access::Privilege::kOperate);
} // namespace SleepMode
namespace TemperatureUnit {
inline constexpr DataModel::AttributeEntry kMetadataEntry(TemperatureUnit::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, Access::Privilege::kOperate);
} // namespace TemperatureUnit
namespace CleanState {
inline constexpr DataModel::AttributeEntry kMetadataEntry(CleanState::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace CleanState
namespace OffTimer {
inline constexpr DataModel::AttributeEntry kMetadataEntry(OffTimer::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace OffTimer
namespace OffTimerHours {
inline constexpr DataModel::AttributeEntry kMetadataEntry(OffTimerHours::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace OffTimerHours
namespace OffTimerMinutes {
inline constexpr DataModel::AttributeEntry kMetadataEntry(OffTimerMinutes::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace OffTimerMinutes
namespace OnTimer {
inline constexpr DataModel::AttributeEntry kMetadataEntry(OnTimer::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace OnTimer
namespace OnTimerHours {
inline constexpr DataModel::AttributeEntry kMetadataEntry(OnTimerHours::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace OnTimerHours
namespace OnTimerMinutes {
inline constexpr DataModel::AttributeEntry kMetadataEntry(OnTimerMinutes::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace OnTimerMinutes
namespace PlasmaMode {
inline constexpr DataModel::AttributeEntry kMetadataEntry(PlasmaMode::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, Access::Privilege::kOperate);
} // namespace PlasmaMode
namespace ErrorCode {
inline constexpr DataModel::AttributeEntry kMetadataEntry(ErrorCode::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace ErrorCode

} // namespace Attributes

namespace Commands {
namespace Clean {
inline constexpr DataModel::AcceptedCommandEntry kMetadataEntry(Clean::Id, BitFlags<DataModel::CommandQualityFlags>(),
                                                                Access::Privilege::kOperate);
} // namespace Clean
namespace CancelClean {
inline constexpr DataModel::AcceptedCommandEntry kMetadataEntry(CancelClean::Id, BitFlags<DataModel::CommandQualityFlags>(),
                                                                Access::Privilege::kOperate);
} // namespace CancelClean
namespace SetTimer {
inline constexpr DataModel::AcceptedCommandEntry kMetadataEntry(SetTimer::Id, BitFlags<DataModel::CommandQualityFlags>(),
                                                                Access::Privilege::kOperate);
} // namespace SetTimer
namespace CancelTimer {
inline constexpr DataModel::AcceptedCommandEntry kMetadataEntry(CancelTimer::Id, BitFlags<DataModel::CommandQualityFlags>(),
                                                                Access::Privilege::kOperate);
} // namespace CancelTimer

} // namespace Commands
} // namespace FreshMideaController
} // namespace Clusters
} // namespace app
} // namespace chip

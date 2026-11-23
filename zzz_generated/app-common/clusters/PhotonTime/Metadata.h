// DO NOT EDIT MANUALLY - Generated file
//
// Cluster metadata information for cluster PhotonTime (cluster code: 367524870/0x15E7FC06)
// based on src/controller/data_model/controller-clusters.matter
#pragma once

#include <app/data-model-provider/MetadataTypes.h>
#include <lib/core/DataModelTypes.h>

#include <cstdint>

#include <clusters/PhotonTime/Ids.h>

namespace chip {
namespace app {
namespace Clusters {
namespace PhotonTime {

inline constexpr uint32_t kRevision = 1;

namespace Attributes {
namespace PosixRule {
inline constexpr DataModel::AttributeEntry kMetadataEntry(PosixRule::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace PosixRule
namespace RuleSource {
inline constexpr DataModel::AttributeEntry kMetadataEntry(RuleSource::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace RuleSource
namespace UTCOffset {
inline constexpr DataModel::AttributeEntry kMetadataEntry(UTCOffset::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace UTCOffset
namespace DSTActive {
inline constexpr DataModel::AttributeEntry kMetadataEntry(DSTActive::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace DSTActive
namespace ZoneName {
inline constexpr DataModel::AttributeEntry kMetadataEntry(ZoneName::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace ZoneName

} // namespace Attributes

namespace Commands {
namespace SetTimeZone {
inline constexpr DataModel::AcceptedCommandEntry kMetadataEntry(SetTimeZone::Id, BitFlags<DataModel::CommandQualityFlags>(),
                                                                Access::Privilege::kManage);
} // namespace SetTimeZone

} // namespace Commands
} // namespace PhotonTime
} // namespace Clusters
} // namespace app
} // namespace chip

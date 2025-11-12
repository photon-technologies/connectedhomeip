// DO NOT EDIT MANUALLY - Generated file
//
// Cluster metadata information for cluster PhotonSmart (cluster code: 367524864/0x15E7FC00)
// based on src/controller/data_model/controller-clusters.matter
#pragma once

#include <app/data-model-provider/MetadataTypes.h>
#include <lib/core/DataModelTypes.h>

#include <cstdint>

#include <clusters/PhotonSmart/Ids.h>

namespace chip {
namespace app {
namespace Clusters {
namespace PhotonSmart {

inline constexpr uint32_t kRevision = 1;

namespace Attributes {
namespace DeviceId {
inline constexpr DataModel::AttributeEntry kMetadataEntry(DeviceId::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kAdminister, std::nullopt);
} // namespace DeviceId
namespace ShouldReboot {
inline constexpr DataModel::AttributeEntry kMetadataEntry(ShouldReboot::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kView, std::nullopt);
} // namespace ShouldReboot
namespace MqttConfig {
inline constexpr DataModel::AttributeEntry kMetadataEntry(MqttConfig::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kAdminister, Access::Privilege::kAdminister);
} // namespace MqttConfig
namespace MqttReportEnabled {
inline constexpr DataModel::AttributeEntry kMetadataEntry(MqttReportEnabled::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kAdminister, Access::Privilege::kAdminister);
} // namespace MqttReportEnabled
namespace InsightsEnabled {
inline constexpr DataModel::AttributeEntry kMetadataEntry(InsightsEnabled::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kAdminister, Access::Privilege::kAdminister);
} // namespace InsightsEnabled
namespace InsightsParams {
inline constexpr DataModel::AttributeEntry kMetadataEntry(InsightsParams::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kAdminister, Access::Privilege::kAdminister);
} // namespace InsightsParams
namespace PublicIpv4Address {
inline constexpr DataModel::AttributeEntry kMetadataEntry(PublicIpv4Address::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kAdminister, std::nullopt);
} // namespace PublicIpv4Address
namespace PublicIpv4Enabled {
inline constexpr DataModel::AttributeEntry kMetadataEntry(PublicIpv4Enabled::Id, BitFlags<DataModel::AttributeQualityFlags>(),
                                                          Access::Privilege::kAdminister, Access::Privilege::kAdminister);
} // namespace PublicIpv4Enabled

} // namespace Attributes

namespace Commands {
namespace Reboot {
inline constexpr DataModel::AcceptedCommandEntry kMetadataEntry(Reboot::Id, BitFlags<DataModel::CommandQualityFlags>(),
                                                                Access::Privilege::kAdminister);
} // namespace Reboot
namespace FactoryReset {
inline constexpr DataModel::AcceptedCommandEntry kMetadataEntry(FactoryReset::Id, BitFlags<DataModel::CommandQualityFlags>(),
                                                                Access::Privilege::kAdminister);
} // namespace FactoryReset

} // namespace Commands
} // namespace PhotonSmart
} // namespace Clusters
} // namespace app
} // namespace chip

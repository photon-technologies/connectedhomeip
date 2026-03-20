// DO NOT EDIT MANUALLY - Generated file
//
// Identifier constant values for cluster PhotonSmart (cluster code: 367524864/0x15E7FC00)
// based on src/controller/data_model/controller-clusters.matter
#pragma once

#include <clusters/shared/GlobalIds.h>
#include <lib/core/DataModelTypes.h>

namespace chip {
namespace app {
namespace Clusters {
namespace PhotonSmart {
namespace Attributes {

// Total number of attributes supported by the cluster, including global attributes
inline constexpr uint32_t kAttributesCount = 13;

namespace DeviceId {
inline constexpr AttributeId Id = 0x00000000;
} // namespace DeviceId

namespace ShouldReboot {
inline constexpr AttributeId Id = 0x00000001;
} // namespace ShouldReboot

namespace MqttConfig {
inline constexpr AttributeId Id = 0x00000002;
} // namespace MqttConfig

namespace MqttReportEnabled {
inline constexpr AttributeId Id = 0x00000003;
} // namespace MqttReportEnabled

namespace InsightsEnabled {
inline constexpr AttributeId Id = 0x00000004;
} // namespace InsightsEnabled

namespace InsightsParams {
inline constexpr AttributeId Id = 0x00000005;
} // namespace InsightsParams

namespace PublicIpv4Address {
inline constexpr AttributeId Id = 0x00000006;
} // namespace PublicIpv4Address

namespace PublicIpv4Enabled {
inline constexpr AttributeId Id = 0x00000007;
} // namespace PublicIpv4Enabled

namespace GeneratedCommandList {
inline constexpr AttributeId Id = Globals::Attributes::GeneratedCommandList::Id;
} // namespace GeneratedCommandList

namespace AcceptedCommandList {
inline constexpr AttributeId Id = Globals::Attributes::AcceptedCommandList::Id;
} // namespace AcceptedCommandList

namespace AttributeList {
inline constexpr AttributeId Id = Globals::Attributes::AttributeList::Id;
} // namespace AttributeList

namespace FeatureMap {
inline constexpr AttributeId Id = Globals::Attributes::FeatureMap::Id;
} // namespace FeatureMap

namespace ClusterRevision {
inline constexpr AttributeId Id = Globals::Attributes::ClusterRevision::Id;
} // namespace ClusterRevision

} // namespace Attributes
} // namespace PhotonSmart
} // namespace Clusters
} // namespace app
} // namespace chip

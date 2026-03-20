// DO NOT EDIT MANUALLY - Generated file
//
// Identifier constant values for cluster FreshRefrigeratorController (cluster code: 367524867/0x15E7FC03)
// based on src/controller/data_model/controller-clusters.matter
#pragma once

#include <clusters/shared/GlobalIds.h>
#include <lib/core/DataModelTypes.h>

namespace chip {
namespace app {
namespace Clusters {
namespace FreshRefrigeratorController {
namespace Attributes {

// Total number of attributes supported by the cluster, including global attributes
inline constexpr uint32_t kAttributesCount = 23;

namespace FridgeTemperatureDefault {
inline constexpr AttributeId Id = 0x00000000;
} // namespace FridgeTemperatureDefault

namespace FreezerTemperatureDefault {
inline constexpr AttributeId Id = 0x00000001;
} // namespace FreezerTemperatureDefault

namespace FridgePreviousTemperature {
inline constexpr AttributeId Id = 0x00000002;
} // namespace FridgePreviousTemperature

namespace FreezerPreviousTemperature {
inline constexpr AttributeId Id = 0x00000003;
} // namespace FreezerPreviousTemperature

namespace SuperCoolTime {
inline constexpr AttributeId Id = 0x00000004;
} // namespace SuperCoolTime

namespace SuperFreezeTime {
inline constexpr AttributeId Id = 0x00000005;
} // namespace SuperFreezeTime

namespace AlarmTime {
inline constexpr AttributeId Id = 0x00000006;
} // namespace AlarmTime

namespace ResetTimeout {
inline constexpr AttributeId Id = 0x00000007;
} // namespace ResetTimeout

namespace DisplayActiveTime {
inline constexpr AttributeId Id = 0x00000008;
} // namespace DisplayActiveTime

namespace DisplayErrorTime {
inline constexpr AttributeId Id = 0x00000009;
} // namespace DisplayErrorTime

namespace CompressorState {
inline constexpr AttributeId Id = 0x0000000A;
} // namespace CompressorState

namespace DefrostState {
inline constexpr AttributeId Id = 0x0000000B;
} // namespace DefrostState

namespace FridgeErrorMargin {
inline constexpr AttributeId Id = 0x0000000C;
} // namespace FridgeErrorMargin

namespace FreezerErrorMargin {
inline constexpr AttributeId Id = 0x0000000D;
} // namespace FreezerErrorMargin

namespace TemperatureErrorTime {
inline constexpr AttributeId Id = 0x0000000E;
} // namespace TemperatureErrorTime

namespace FridgeDoorState {
inline constexpr AttributeId Id = 0x0000000F;
} // namespace FridgeDoorState

namespace FreezerDoorState {
inline constexpr AttributeId Id = 0x00000010;
} // namespace FreezerDoorState

namespace DefrostTemperature {
inline constexpr AttributeId Id = 0x00000011;
} // namespace DefrostTemperature

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
} // namespace FreshRefrigeratorController
} // namespace Clusters
} // namespace app
} // namespace chip

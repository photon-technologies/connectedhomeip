// DO NOT EDIT MANUALLY - Generated file
//
// Identifier constant values for cluster PhotonSmart (cluster code: 367524864/0x15E7FC00)
// based on src/controller/data_model/controller-clusters.matter
#pragma once

#include <lib/core/DataModelTypes.h>

namespace chip {
namespace app {
namespace Clusters {
namespace PhotonSmart {
namespace Commands {

// Total number of client to server commands supported by the cluster
inline constexpr uint32_t kAcceptedCommandsCount = 2;

// Total number of server to client commands supported by the cluster (response commands)
inline constexpr uint32_t kGeneratedCommandsCount = 0;

namespace Reboot {
inline constexpr CommandId Id = 0x00000000;
} // namespace Reboot

namespace FactoryReset {
inline constexpr CommandId Id = 0x00000001;
} // namespace FactoryReset

} // namespace Commands
} // namespace PhotonSmart
} // namespace Clusters
} // namespace app
} // namespace chip

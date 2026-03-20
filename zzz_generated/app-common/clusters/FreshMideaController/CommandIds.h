// DO NOT EDIT MANUALLY - Generated file
//
// Identifier constant values for cluster FreshMideaController (cluster code: 367524868/0x15E7FC04)
// based on src/controller/data_model/controller-clusters.matter
#pragma once

#include <lib/core/DataModelTypes.h>

namespace chip {
namespace app {
namespace Clusters {
namespace FreshMideaController {
namespace Commands {

// Total number of client to server commands supported by the cluster
inline constexpr uint32_t kAcceptedCommandsCount = 4;

// Total number of server to client commands supported by the cluster (response commands)
inline constexpr uint32_t kGeneratedCommandsCount = 0;

namespace Clean {
inline constexpr CommandId Id = 0x00000000;
} // namespace Clean

namespace CancelClean {
inline constexpr CommandId Id = 0x00000001;
} // namespace CancelClean

namespace SetTimer {
inline constexpr CommandId Id = 0x00000002;
} // namespace SetTimer

namespace CancelTimer {
inline constexpr CommandId Id = 0x00000003;
} // namespace CancelTimer

} // namespace Commands
} // namespace FreshMideaController
} // namespace Clusters
} // namespace app
} // namespace chip

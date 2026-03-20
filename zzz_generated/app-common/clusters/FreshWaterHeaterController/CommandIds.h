// DO NOT EDIT MANUALLY - Generated file
//
// Identifier constant values for cluster FreshWaterHeaterController (cluster code: 367524869/0x15E7FC05)
// based on src/controller/data_model/controller-clusters.matter
#pragma once

#include <lib/core/DataModelTypes.h>

namespace chip {
namespace app {
namespace Clusters {
namespace FreshWaterHeaterController {
namespace Commands {

// Total number of client to server commands supported by the cluster
inline constexpr uint32_t kAcceptedCommandsCount = 2;

// Total number of server to client commands supported by the cluster (response commands)
inline constexpr uint32_t kGeneratedCommandsCount = 0;

namespace AnodeChangeRequest {
inline constexpr CommandId Id = 0x00000000;
} // namespace AnodeChangeRequest

namespace AnodeChangeConfirmed {
inline constexpr CommandId Id = 0x00000001;
} // namespace AnodeChangeConfirmed

} // namespace Commands
} // namespace FreshWaterHeaterController
} // namespace Clusters
} // namespace app
} // namespace chip

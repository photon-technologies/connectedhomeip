// DO NOT EDIT MANUALLY - Generated file
//
// Cluster metadata information for cluster FreshRefrigeratorController (cluster code: 367524867/0x15E7FC03)
// based on src/controller/data_model/controller-clusters.matter
#pragma once

#include <optional>

#include <app/data-model-provider/ClusterMetadataProvider.h>
#include <app/data-model-provider/MetadataTypes.h>
#include <clusters/FreshRefrigeratorController/Ids.h>
#include <clusters/FreshRefrigeratorController/Metadata.h>

namespace chip {
namespace app {
namespace DataModel {

template <>
struct ClusterMetadataProvider<DataModel::AttributeEntry, Clusters::FreshRefrigeratorController::Id>
{
    static constexpr std::optional<DataModel::AttributeEntry> EntryFor(AttributeId attributeId)
    {
        using namespace Clusters::FreshRefrigeratorController::Attributes;
        switch (attributeId)
        {
        case FridgeTemperatureDefault::Id:
            return FridgeTemperatureDefault::kMetadataEntry;
        case FreezerTemperatureDefault::Id:
            return FreezerTemperatureDefault::kMetadataEntry;
        case FridgePreviousTemperature::Id:
            return FridgePreviousTemperature::kMetadataEntry;
        case FreezerPreviousTemperature::Id:
            return FreezerPreviousTemperature::kMetadataEntry;
        case SuperCoolTime::Id:
            return SuperCoolTime::kMetadataEntry;
        case SuperFreezeTime::Id:
            return SuperFreezeTime::kMetadataEntry;
        case AlarmTime::Id:
            return AlarmTime::kMetadataEntry;
        case ResetTimeout::Id:
            return ResetTimeout::kMetadataEntry;
        case DisplayActiveTime::Id:
            return DisplayActiveTime::kMetadataEntry;
        case DisplayErrorTime::Id:
            return DisplayErrorTime::kMetadataEntry;
        case CompressorState::Id:
            return CompressorState::kMetadataEntry;
        case DefrostState::Id:
            return DefrostState::kMetadataEntry;
        case FridgeErrorMargin::Id:
            return FridgeErrorMargin::kMetadataEntry;
        case FreezerErrorMargin::Id:
            return FreezerErrorMargin::kMetadataEntry;
        case TemperatureErrorTime::Id:
            return TemperatureErrorTime::kMetadataEntry;
        case FridgeDoorState::Id:
            return FridgeDoorState::kMetadataEntry;
        case FreezerDoorState::Id:
            return FreezerDoorState::kMetadataEntry;
        case DefrostTemperature::Id:
            return DefrostTemperature::kMetadataEntry;
        default:
            return std::nullopt;
        }
    }
};

template <>
struct ClusterMetadataProvider<DataModel::AcceptedCommandEntry, Clusters::FreshRefrigeratorController::Id>
{
    static constexpr std::optional<DataModel::AcceptedCommandEntry> EntryFor(CommandId commandId)
    {
        using namespace Clusters::FreshRefrigeratorController::Commands;
        switch (commandId)
        {

        default:
            return std::nullopt;
        }
    }
};

} // namespace DataModel
} // namespace app
} // namespace chip

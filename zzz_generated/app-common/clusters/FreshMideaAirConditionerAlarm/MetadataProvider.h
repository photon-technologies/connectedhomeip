// DO NOT EDIT MANUALLY - Generated file
//
// Cluster metadata information for cluster FreshMideaAirConditionerAlarm (cluster code: 367524865/0x15E7FC01)
// based on src/controller/data_model/controller-clusters.matter
#pragma once

#include <optional>

#include <app/data-model-provider/ClusterMetadataProvider.h>
#include <app/data-model-provider/MetadataTypes.h>
#include <clusters/FreshMideaAirConditionerAlarm/Ids.h>
#include <clusters/FreshMideaAirConditionerAlarm/Metadata.h>

namespace chip {
namespace app {
namespace DataModel {

template <>
struct ClusterMetadataProvider<DataModel::AttributeEntry, Clusters::FreshMideaAirConditionerAlarm::Id>
{
    static constexpr std::optional<DataModel::AttributeEntry> EntryFor(AttributeId attributeId)
    {
        using namespace Clusters::FreshMideaAirConditionerAlarm::Attributes;
        switch (attributeId)
        {
        case Mask::Id:
            return Mask::kMetadataEntry;
        case Latch::Id:
            return Latch::kMetadataEntry;
        case State::Id:
            return State::kMetadataEntry;
        case Supported::Id:
            return Supported::kMetadataEntry;
        default:
            return std::nullopt;
        }
    }
};

template <>
struct ClusterMetadataProvider<DataModel::AcceptedCommandEntry, Clusters::FreshMideaAirConditionerAlarm::Id>
{
    static constexpr std::optional<DataModel::AcceptedCommandEntry> EntryFor(CommandId commandId)
    {
        using namespace Clusters::FreshMideaAirConditionerAlarm::Commands;
        switch (commandId)
        {
        case Reset::Id:
            return Reset::kMetadataEntry;

        default:
            return std::nullopt;
        }
    }
};

} // namespace DataModel
} // namespace app
} // namespace chip

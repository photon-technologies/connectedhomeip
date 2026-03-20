// DO NOT EDIT MANUALLY - Generated file
//
// Cluster metadata information for cluster FreshWaterHeaterErrorsAlarm (cluster code: 367524870/0x15E7FC06)
// based on src/controller/data_model/controller-clusters.matter
#pragma once

#include <optional>

#include <app/data-model-provider/ClusterMetadataProvider.h>
#include <app/data-model-provider/MetadataTypes.h>
#include <clusters/FreshWaterHeaterErrorsAlarm/Ids.h>
#include <clusters/FreshWaterHeaterErrorsAlarm/Metadata.h>

namespace chip {
namespace app {
namespace DataModel {

template <>
struct ClusterMetadataProvider<DataModel::AttributeEntry, Clusters::FreshWaterHeaterErrorsAlarm::Id>
{
    static constexpr std::optional<DataModel::AttributeEntry> EntryFor(AttributeId attributeId)
    {
        using namespace Clusters::FreshWaterHeaterErrorsAlarm::Attributes;
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
struct ClusterMetadataProvider<DataModel::AcceptedCommandEntry, Clusters::FreshWaterHeaterErrorsAlarm::Id>
{
    static constexpr std::optional<DataModel::AcceptedCommandEntry> EntryFor(CommandId commandId)
    {
        using namespace Clusters::FreshWaterHeaterErrorsAlarm::Commands;
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

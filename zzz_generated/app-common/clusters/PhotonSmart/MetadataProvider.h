// DO NOT EDIT MANUALLY - Generated file
//
// Cluster metadata information for cluster PhotonSmart (cluster code: 367524864/0x15E7FC00)
// based on src/controller/data_model/controller-clusters.matter
#pragma once

#include <optional>

#include <app/data-model-provider/ClusterMetadataProvider.h>
#include <app/data-model-provider/MetadataTypes.h>
#include <clusters/PhotonSmart/Ids.h>
#include <clusters/PhotonSmart/Metadata.h>

namespace chip {
namespace app {
namespace DataModel {

template <>
struct ClusterMetadataProvider<DataModel::AttributeEntry, Clusters::PhotonSmart::Id>
{
    static constexpr std::optional<DataModel::AttributeEntry> EntryFor(AttributeId attributeId)
    {
        using namespace Clusters::PhotonSmart::Attributes;
        switch (attributeId)
        {
        case DeviceId::Id:
            return DeviceId::kMetadataEntry;
        case ShouldReboot::Id:
            return ShouldReboot::kMetadataEntry;
        case MqttConfig::Id:
            return MqttConfig::kMetadataEntry;
        case MqttReportEnabled::Id:
            return MqttReportEnabled::kMetadataEntry;
        case InsightsEnabled::Id:
            return InsightsEnabled::kMetadataEntry;
        case InsightsParams::Id:
            return InsightsParams::kMetadataEntry;
        case PublicIpv4Address::Id:
            return PublicIpv4Address::kMetadataEntry;
        case PublicIpv4Enabled::Id:
            return PublicIpv4Enabled::kMetadataEntry;
        default:
            return std::nullopt;
        }
    }
};

template <>
struct ClusterMetadataProvider<DataModel::AcceptedCommandEntry, Clusters::PhotonSmart::Id>
{
    static constexpr std::optional<DataModel::AcceptedCommandEntry> EntryFor(CommandId commandId)
    {
        using namespace Clusters::PhotonSmart::Commands;
        switch (commandId)
        {
        case Reboot::Id:
            return Reboot::kMetadataEntry;
        case FactoryReset::Id:
            return FactoryReset::kMetadataEntry;

        default:
            return std::nullopt;
        }
    }
};

} // namespace DataModel
} // namespace app
} // namespace chip

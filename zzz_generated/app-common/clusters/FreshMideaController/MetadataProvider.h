// DO NOT EDIT MANUALLY - Generated file
//
// Cluster metadata information for cluster FreshMideaController (cluster code: 367524868/0x15E7FC04)
// based on src/controller/data_model/controller-clusters.matter
#pragma once

#include <optional>

#include <app/data-model-provider/ClusterMetadataProvider.h>
#include <app/data-model-provider/MetadataTypes.h>
#include <clusters/FreshMideaController/Ids.h>
#include <clusters/FreshMideaController/Metadata.h>

namespace chip {
namespace app {
namespace DataModel {

template <>
struct ClusterMetadataProvider<DataModel::AttributeEntry, Clusters::FreshMideaController::Id>
{
    static constexpr std::optional<DataModel::AttributeEntry> EntryFor(AttributeId attributeId)
    {
        using namespace Clusters::FreshMideaController::Attributes;
        switch (attributeId)
        {
        case Beep::Id:
            return Beep::kMetadataEntry;
        case Light::Id:
            return Light::kMetadataEntry;
        case TurboMode::Id:
            return TurboMode::kMetadataEntry;
        case EcoMode::Id:
            return EcoMode::kMetadataEntry;
        case FrostProtectionMode::Id:
            return FrostProtectionMode::kMetadataEntry;
        case SleepMode::Id:
            return SleepMode::kMetadataEntry;
        case TemperatureUnit::Id:
            return TemperatureUnit::kMetadataEntry;
        case CleanState::Id:
            return CleanState::kMetadataEntry;
        case OffTimer::Id:
            return OffTimer::kMetadataEntry;
        case OffTimerHours::Id:
            return OffTimerHours::kMetadataEntry;
        case OffTimerMinutes::Id:
            return OffTimerMinutes::kMetadataEntry;
        case OnTimer::Id:
            return OnTimer::kMetadataEntry;
        case OnTimerHours::Id:
            return OnTimerHours::kMetadataEntry;
        case OnTimerMinutes::Id:
            return OnTimerMinutes::kMetadataEntry;
        case PlasmaMode::Id:
            return PlasmaMode::kMetadataEntry;
        case BreezeAwayMode::Id:
            return BreezeAwayMode::kMetadataEntry;
        case ErrorCode::Id:
            return ErrorCode::kMetadataEntry;
        case HorizontalLouverPosition::Id:
            return HorizontalLouverPosition::kMetadataEntry;
        default:
            return std::nullopt;
        }
    }
};

template <>
struct ClusterMetadataProvider<DataModel::AcceptedCommandEntry, Clusters::FreshMideaController::Id>
{
    static constexpr std::optional<DataModel::AcceptedCommandEntry> EntryFor(CommandId commandId)
    {
        using namespace Clusters::FreshMideaController::Commands;
        switch (commandId)
        {
        case Clean::Id:
            return Clean::kMetadataEntry;
        case CancelClean::Id:
            return CancelClean::kMetadataEntry;
        case SetTimer::Id:
            return SetTimer::kMetadataEntry;
        case CancelTimer::Id:
            return CancelTimer::kMetadataEntry;

        default:
            return std::nullopt;
        }
    }
};

} // namespace DataModel
} // namespace app
} // namespace chip

// DO NOT EDIT MANUALLY - Generated file
//
// Cluster metadata information for cluster FreshWaterHeaterController (cluster code: 367524869/0x15E7FC05)
// based on src/controller/data_model/controller-clusters.matter
#pragma once

#include <optional>

#include <app/data-model-provider/ClusterMetadataProvider.h>
#include <app/data-model-provider/MetadataTypes.h>
#include <clusters/FreshWaterHeaterController/Ids.h>
#include <clusters/FreshWaterHeaterController/Metadata.h>

namespace chip {
namespace app {
namespace DataModel {

template <>
struct ClusterMetadataProvider<DataModel::AttributeEntry, Clusters::FreshWaterHeaterController::Id>
{
    static constexpr std::optional<DataModel::AttributeEntry> EntryFor(AttributeId attributeId)
    {
        using namespace Clusters::FreshWaterHeaterController::Attributes;
        switch (attributeId)
        {
        case ColdWaterTemperature::Id:
            return ColdWaterTemperature::kMetadataEntry;
        case ShowerTemperature::Id:
            return ShowerTemperature::kMetadataEntry;
        case ShowerHysteresis::Id:
            return ShowerHysteresis::kMetadataEntry;
        case ShowerState::Id:
            return ShowerState::kMetadataEntry;
        case DefaultShowerFlowLPM::Id:
            return DefaultShowerFlowLPM::kMetadataEntry;
        case StandardModeSetpoint::Id:
            return StandardModeSetpoint::kMetadataEntry;
        case EcoModeSetpoint::Id:
            return EcoModeSetpoint::kMetadataEntry;
        case DefaultBoostModeSetpoint::Id:
            return DefaultBoostModeSetpoint::kMetadataEntry;
        case DisplayTemperatureStep::Id:
            return DisplayTemperatureStep::kMetadataEntry;
        case ResetTimeout::Id:
            return ResetTimeout::kMetadataEntry;
        case CoolDownTimeout::Id:
            return CoolDownTimeout::kMetadataEntry;
        case ResetCounterTimeout::Id:
            return ResetCounterTimeout::kMetadataEntry;
        case DisplayActiveTimeout::Id:
            return DisplayActiveTimeout::kMetadataEntry;
        case DisplayErrorTimeout::Id:
            return DisplayErrorTimeout::kMetadataEntry;
        case DisplayTargetTimeout::Id:
            return DisplayTargetTimeout::kMetadataEntry;
        case TemperatureSensorMinValid::Id:
            return TemperatureSensorMinValid::kMetadataEntry;
        case TemperatureSensorMaxValid::Id:
            return TemperatureSensorMaxValid::kMetadataEntry;
        case OverheatThresholdTemperature::Id:
            return OverheatThresholdTemperature::kMetadataEntry;
        case RapidRiseDelta::Id:
            return RapidRiseDelta::kMetadataEntry;
        case RapidRiseWindow::Id:
            return RapidRiseWindow::kMetadataEntry;
        case PreviousTargetHeaterTemperature::Id:
            return PreviousTargetHeaterTemperature::kMetadataEntry;
        case HeaterMaximumPower::Id:
            return HeaterMaximumPower::kMetadataEntry;
        case DiagnosticsConfirmTimeList::Id:
            return DiagnosticsConfirmTimeList::kMetadataEntry;
        case DiagnosticsRehabTimeList::Id:
            return DiagnosticsRehabTimeList::kMetadataEntry;
        case RequiresAnodeChange::Id:
            return RequiresAnodeChange::kMetadataEntry;
        case MaximumBoostTime::Id:
            return MaximumBoostTime::kMetadataEntry;
        case CurrentBoostModeSetpoint::Id:
            return CurrentBoostModeSetpoint::kMetadataEntry;
        case ErrorCode::Id:
            return ErrorCode::kMetadataEntry;
        case AntiLegionellaState::Id:
            return AntiLegionellaState::kMetadataEntry;
        case EnergyReportInterval::Id:
            return EnergyReportInterval::kMetadataEntry;
        default:
            return std::nullopt;
        }
    }
};

template <>
struct ClusterMetadataProvider<DataModel::AcceptedCommandEntry, Clusters::FreshWaterHeaterController::Id>
{
    static constexpr std::optional<DataModel::AcceptedCommandEntry> EntryFor(CommandId commandId)
    {
        using namespace Clusters::FreshWaterHeaterController::Commands;
        switch (commandId)
        {
        case AnodeChangeRequest::Id:
            return AnodeChangeRequest::kMetadataEntry;
        case AnodeChangeConfirmed::Id:
            return AnodeChangeConfirmed::kMetadataEntry;

        default:
            return std::nullopt;
        }
    }
};

} // namespace DataModel
} // namespace app
} // namespace chip

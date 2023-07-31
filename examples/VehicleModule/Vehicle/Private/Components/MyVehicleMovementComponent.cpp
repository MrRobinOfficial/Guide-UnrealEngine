// Copyright 2023 MrRobin. All Rights Reserved.

#include "Components/MyVehicleMovementComponent.h"

UMyVehicleMovementComponent::UMyVehicleMovementComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UMyVehicleMovementComponent::SetClutchInput(float Clutch)
{
    RawClutchInput = FMath::Clamp(Clutch, 0.0f, 1.0f);
}

void UMyVehicleMovementComponent::IncreaseClutchInput(float ClutchDelta)
{
    RawClutchInput = FMath::Clamp(RawClutchInput + ClutchDelta, 0.f, 1.0f);
}

void UMyVehicleMovementComponent::DecreaseClutchInput(float ClutchDelta)
{
    RawClutchInput = FMath::Clamp(RawClutchInput - ClutchDelta, 0.f, 1.0f);
}

void UMyVehicleMovementComponent::ToggleEngineState() { SetEngineState(!GetEngineState()); }

void UMyVehicleMovementComponent::SetEngineState(bool bEnabled)
{
    if (bMechanicalSimEnabled == bEnabled)
        return;

	OnEngineStateChanged.Broadcast(bMechanicalSimEnabled, bEnabled);

    bMechanicalSimEnabled = bEnabled;
}

float UMyVehicleMovementComponent::GetTorqueFromRPM(float EngineRPM)
{
    return EngineSetup.GetTorqueFromRPM(EngineRPM);
}

void UMyVehicleMovementComponent::ClearRawInput()
{
    Super::ClearRawInput();

    RawClutchInput = 0.0f;
}

float UMyVehicleMovementComponent::GetTorqueReductionFactor() const
{
    if (RawClutchInput >= ClutchEngageThreshold)
        return 1.0f;

    return FMath::GetMappedRangeValueClamped(
        FVector2D(0.0f, ClutchEngageThreshold),
        FVector2D(1.0f, ClutchDisengageFactor),
        RawClutchInput
    );
}

float UMyVehicleMovementComponent::GetEngineRPM() const
{
    float EngineRPM = 0.f;

    if (bMechanicalSimEnabled && PVehicleOutput)
    {
        EngineRPM = PVehicleOutput->EngineRPM;
    }

    return EngineRPM;
}

void UMyChaosWheeledVehicleSimulation::FillOutputState(FChaosVehicleAsyncOutput& Output)
{
	// #Note: remember to copy/interpolate values from the physics thread output in UChaosVehicleMovementComponent::ParallelUpdate
	const auto& VehicleWheels = PVehicle->Wheels;
	auto& VehicleSuspension = PVehicle->Suspension;
	if (PVehicle->HasTransmission())
	{
		auto& Transmission = PVehicle->GetTransmission();
		Output.VehicleSimOutput.CurrentGear = Transmission.GetCurrentGear();
		Output.VehicleSimOutput.TargetGear = Transmission.GetTargetGear();
		Output.VehicleSimOutput.TransmissionRPM = Transmission.GetTransmissionRPM();

		// TODO: Add clutch support

		Output.VehicleSimOutput.TransmissionTorque = Transmission.GetTransmissionTorque(PVehicle->GetEngine().GetTorqueFromRPM(true));
	}
	if (PVehicle->HasEngine())
	{
		auto& Engine = PVehicle->GetEngine();
		Output.VehicleSimOutput.EngineRPM = Engine.GetEngineRPM();
		Output.VehicleSimOutput.EngineTorque = Engine.GetEngineTorque();
	}

	// #TODO: can we avoid copies when async is turned off
	for (int WheelIdx = 0; WheelIdx < VehicleWheels.Num(); WheelIdx++)
	{
		FWheelsOutput WheelsOut;
		WheelsOut.InContact = VehicleWheels[WheelIdx].InContact();
		WheelsOut.SteeringAngle = VehicleWheels[WheelIdx].GetSteeringAngle();
		WheelsOut.AngularPosition = VehicleWheels[WheelIdx].GetAngularPosition();
		WheelsOut.AngularVelocity = VehicleWheels[WheelIdx].GetAngularVelocity();
		WheelsOut.WheelRadius = VehicleWheels[WheelIdx].GetEffectiveRadius();

		WheelsOut.LateralAdhesiveLimit = VehicleWheels[WheelIdx].LateralAdhesiveLimit;
		WheelsOut.LongitudinalAdhesiveLimit = VehicleWheels[WheelIdx].LongitudinalAdhesiveLimit;

		WheelsOut.bIsSlipping = VehicleWheels[WheelIdx].IsSlipping();
		WheelsOut.SlipMagnitude = VehicleWheels[WheelIdx].GetSlipMagnitude();
		WheelsOut.bIsSkidding = VehicleWheels[WheelIdx].IsSkidding();
		WheelsOut.SkidMagnitude = VehicleWheels[WheelIdx].GetSkidMagnitude();
		WheelsOut.SkidNormal = WheelState.WorldWheelVelocity[WheelIdx].GetSafeNormal();
		WheelsOut.SlipAngle = VehicleWheels[WheelIdx].GetSlipAngle();

		WheelsOut.SuspensionOffset = VehicleSuspension[WheelIdx].GetSuspensionOffset();
		WheelsOut.SpringForce = VehicleSuspension[WheelIdx].GetSuspensionForce();
		WheelsOut.NormalizedSuspensionLength = VehicleSuspension[WheelIdx].GetNormalizedLength();

		WheelsOut.DriveTorque = Chaos::TorqueCmToM(VehicleWheels[WheelIdx].GetDriveTorque());
		WheelsOut.BrakeTorque = Chaos::TorqueCmToM(VehicleWheels[WheelIdx].GetBrakeTorque());

		WheelsOut.bABSActivated = VehicleWheels[WheelIdx].IsABSActivated();
		WheelsOut.bBlockingHit = WheelState.TraceResult[WheelIdx].bBlockingHit;
		WheelsOut.ImpactPoint = WheelState.TraceResult[WheelIdx].ImpactPoint;
		WheelsOut.HitLocation = WheelState.TraceResult[WheelIdx].Location;
		WheelsOut.PhysMaterial = WheelState.TraceResult[WheelIdx].PhysMaterial;

		Output.VehicleSimOutput.Wheels.Add(WheelsOut);
	}
}
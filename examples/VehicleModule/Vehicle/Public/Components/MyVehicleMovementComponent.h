// Copyright 2023 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "MyVehicleMovementComponent.generated.h"

class VEHICLE_API UMyChaosWheeledVehicleSimulation : public UChaosWheeledVehicleSimulation
{
public:
    virtual void FillOutputState(FChaosVehicleAsyncOutput& Output) override;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEngineStateChangedSignature, bool, bOldState, bool, bNewState);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGearChangedSignature, int32, OldGearNum, int32, NewGearNum);

UCLASS(ClassGroup = (Physics), meta = (BlueprintSpawnableComponent), 
    HideCategories = (PlanarMovement, "Components|Movement|Planar", Activation, 
    "Components|Activation"))
class VEHICLE_API UMyVehicleMovementComponent : public UChaosWheeledVehicleMovementComponent
{
    GENERATED_BODY()

public:
    UMyVehicleMovementComponent();

    UPROPERTY(BlueprintAssignable)
    FOnEngineStateChangedSignature OnEngineStateChanged;

    UPROPERTY(BlueprintAssignable)
    FOnGearChangedSignature OnGearChanged;

public:
    /**  */
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Game|Components|ChaosVehicleMovement")
    FORCEINLINE float GetClutchInput() const { return RawClutchInput; }

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Game|Components|ChaosVehicleMovement")
    float GetTorqueReductionFactor() const;

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Game|Components|ChaosVehicleMovement")
    float GetEngineRPM() const;

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Game|Components|ChaosVehicleMovement")
    FORCEINLINE float GetEngineIdleRPM() const { return EngineSetup.EngineIdleRPM; }

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Game|Components|ChaosVehicleMovement")
    FORCEINLINE float GetEngineMaxRPM() const { return EngineSetup.MaxRPM; }

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Game|Components|ChaosVehicleMovement")
    FORCEINLINE float GetEngineMaxTorque() const { return EngineSetup.MaxTorque; }

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Game|Components|ChaosVehicleMovement")
    FORCEINLINE FRuntimeFloatCurve GetEngineCurve() const { return EngineSetup.TorqueCurve; }

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Game|Components|ChaosVehicleMovement", meta = (DisplayName = "Get Forward Speed [m/s]"))
    FORCEINLINE float GetForwardSpeedMS() const { return GetForwardSpeedKmh() / 3.6f; }

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Game|Components|ChaosVehicleMovement", meta = (DisplayName = "Get Forward Speed [km/h]"))
    FORCEINLINE float GetForwardSpeedKmh() const { return Chaos::CmSToKmH(GetForwardSpeed()); }

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Game|Components|ChaosVehicleMovement")
    FORCEINLINE bool GetEngineState() const { return  bMechanicalSimEnabled; }

public:
    UFUNCTION(BlueprintCallable, Category="Game|Components|ChaosVehicleMovement")
    void SetClutchInput(float Clutch);

    UFUNCTION(BlueprintCallable, Category="Game|Components|ChaosVehicleMovement")
    void IncreaseClutchInput(float ClutchDelta);

    UFUNCTION(BlueprintCallable, Category="Game|Components|ChaosVehicleMovement")
    void DecreaseClutchInput(float ClutchDelta);

public:
    UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosVehicleMovement")
    void ToggleEngineState();

    UFUNCTION(BlueprintCallable, Category="Game|Components|ChaosVehicleMovement")
    void SetEngineState(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosVehicleMovement")
    float GetTorqueFromRPM(float EngineRPM);

protected:
    virtual void ClearRawInput() override;

    ///** */
    virtual TUniquePtr<Chaos::FSimpleWheeledVehicle> CreatePhysicsVehicle() override
    {
        // Make the Vehicle Simulation class that will be updated from the physics thread async callback
        VehicleSimulationPT = MakeUnique<UMyChaosWheeledVehicleSimulation>();

        return UChaosVehicleMovementComponent::CreatePhysicsVehicle();
    }

protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0"))
    float ClutchEngageThreshold = 0.5f;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0"))
    float ClutchDisengageFactor = 0.1f;

protected:
    UPROPERTY(Transient)
    float RawClutchInput;
};
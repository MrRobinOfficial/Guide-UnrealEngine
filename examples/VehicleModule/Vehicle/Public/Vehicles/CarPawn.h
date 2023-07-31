// Copyright 2023 MrRobin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "CarPawn.generated.h"

UENUM(BlueprintType)
enum class ELightState : uint8
{
    Off,
    LowBeam,
    HighBeam,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCarPawnOnLightStateChanged, ELightState, OldState, ELightState, NewState);

UCLASS(Abstract, Blueprintable)
class VEHICLE_API ACarPawn : public AWheeledVehiclePawn
{
    GENERATED_BODY()

public:
    ACarPawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(BlueprintAssignable)
    FCarPawnOnLightStateChanged OnLightStateChanged;

public:
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Car Pawn")
    FORCEINLINE ELightState GetLightState() const { return LightState; }

public:
    UFUNCTION(BlueprintCallable, Category = "Car Pawn")
    void SetLightState(ELightState NewState);

    UFUNCTION(BlueprintCallable, Category = "Car Pawn")
    void ToggleLightState();

public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Car Pawn")
    void Honk();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Car Pawn")
    void Explode();

#if WITH_EDITORONLY_DATA
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    TObjectPtr<class UArrowComponent> Arrow;
#endif

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TObjectPtr<class UMyVehicleMovementComponent> MyVehicleMovementComponent;

protected:
    UPROPERTY(Transient)
    ELightState LightState;
};
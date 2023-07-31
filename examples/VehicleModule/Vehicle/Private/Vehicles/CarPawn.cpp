// Copyright 2023 MrRobin. All Rights Reserved.

#include "Vehicles/CarPawn.h"

#include "Components/ArrowComponent.h"
#include "Components/MyVehicleMovementComponent.h"

ACarPawn::ACarPawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UMyVehicleMovementComponent>(AWheeledVehiclePawn::VehicleMovementComponentName))
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;

    MyVehicleMovementComponent = CastChecked<UMyVehicleMovementComponent>(GetVehicleMovement());

    checkf(MyVehicleMovementComponent, TEXT("MyVehicleMovementComponent cannot be a 'nullptr'!"));

#if WITH_EDITORONLY_DATA
    Arrow = CreateEditorOnlyDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
    Arrow->ArrowColor = FColor::Yellow;
    Arrow->bTreatAsASprite = true;
    Arrow->SetupAttachment(GetMesh());
    Arrow->bLightAttachment = true;
    Arrow->bIsScreenSizeScaled = true;
#endif
}

void ACarPawn::Explode_Implementation()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Explode!"));
}

void ACarPawn::SetLightState(ELightState NewState)
{
    if (LightState == NewState)
        return;

    OnLightStateChanged.Broadcast(LightState, NewState);

    LightState = NewState;
}

void ACarPawn::ToggleLightState()
{
    switch (LightState)
    {
        case ELightState::Off:
            SetLightState(ELightState::LowBeam);
            break;

        case ELightState::LowBeam:
            SetLightState(ELightState::HighBeam);
            break;

        case ELightState::HighBeam:
            SetLightState(ELightState::Off);
            break;
    }
}
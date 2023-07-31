```cpp
// YourActor.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "YourActor.generated.h"

UCLASS()
class YOURPROJECT_API AYourActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AYourActor();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UFUNCTION()
    void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

private:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* SphereMesh;
};
```

```cpp
// YourActor.cpp

#include "YourActor.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"

// Sets default values
AYourActor::AYourActor()
{
    // Set this actor to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;

    SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
    RootComponent = SphereMesh;
}

// Called when the game starts or when spawned
void AYourActor::BeginPlay()
{
    Super::BeginPlay();

    // Bind the OnHit function to the OnActorHit event
    OnActorHit.AddDynamic(this, &AYourActor::OnHit);
}

// Called every frame
void AYourActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Perform a sweep test to detect overlapping actors with a sphere
    FVector StartLocation = GetActorLocation();
    FVector EndLocation = GetActorLocation() + FVector(100.f, 0.f, 0.f);
    FCollisionShape SphereShape = FCollisionShape::MakeSphere(100.f);

    TArray<FHitResult> OutHits;
    FCollisionQueryParams CollisionParams;

    if (GetWorld()->SweepMultiByChannel(OutHits, StartLocation, EndLocation, FQuat::Identity, ECC_WorldStatic, SphereShape, CollisionParams))
    {
        // Loop through all the hit results
        for (const FHitResult& Hit : OutHits)
        {
            // Draw a debug sphere at the location of the hit
            DrawDebugSphere(GetWorld(), Hit.Location, 100.f, 12, FColor::Green, false, 5.f);

            // Print a debug message on the screen with the name of the hit actor
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Hit Actor: %s"), *Hit.GetActor()->GetName()));
        }
    }
}

void AYourActor::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
    // Handle the hit event here
    // ...
}
```

In this example, we have a custom `AYourActor` class that inherits from `AActor`. Inside the class, we create a `UStaticMeshComponent` named `SphereMesh` to represent our actor. In the `BeginPlay` function, we bind the `OnHit` function to the `OnActorHit` event.

In the `Tick` function, we perform a sweep test using `SweepMultiByChannel` to detect overlapping actors with a sphere starting from the actor's location and extending 100 units in the X direction. If any hits are detected, we draw a debug sphere at each hit location using `DrawDebugSphere`, and we also print a debug message on the screen using `GEngine->AddOnScreenDebugMessage` with the name of the hit actor.

> **Note**
> That you'll need to add the appropriate includes and include `UnrealEd` and `DrawDebugHelpers` modules in your project's Build.cs file for this code to work.
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
    void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                        bool bFromSweep, const FHitResult& SweepResult);
};
```

```cpp
// YourActor.cpp

#include "YourActor.h"

// Sets default values
AYourActor::AYourActor()
{
    // Set this actor to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;

    // Create a static mesh component and attach it as the root component
    UStaticMeshComponent* SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
    RootComponent = SphereMesh;

    // Set up the OnComponentBeginOverlap event
    SphereMesh->OnComponentBeginOverlap.AddDynamic(this, &AYourActor::OnBeginOverlap);
}

// Called when the game starts or when spawned
void AYourActor::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AYourActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AYourActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                bool bFromSweep, const FHitResult& SweepResult)
{
    // Destroy the actor when it overlaps with another actor
    Destroy();
}
```

In this example, we have a custom `AYourActor` class that inherits from `AActor`. Inside the class, we create a `UStaticMeshComponent` named `SphereMesh` to represent our actor and attach it as the root component. We then set up the `OnComponentBeginOverlap` event for the `SphereMesh` component and bind it to the `OnBeginOverlap` function.

In the `OnBeginOverlap` function, we simply call the `Destroy` function to destroy the actor whenever it overlaps with another actor.
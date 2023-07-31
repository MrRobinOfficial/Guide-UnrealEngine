```cpp
#include "YourCustomComponent.h"

void UYourCustomComponent::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                          FVector NormalImpulse, const FHitResult& Hit)
{
    Super::OnComponentHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);

    // Check if the collision was with another actor
    if (OtherActor && OtherActor != GetOwner())
    {
        // Do something with the OtherActor (e.g., apply damage, play sound, etc.)
    }

    // Check if the collision was with another component on the same actor
    if (OtherComp && OtherComp != this)
    {
        // Do something with the OtherComp (e.g., bounce off, apply force, etc.)
    }

    // Access the hit result data for additional information
    FVector ImpactPoint = Hit.ImpactPoint;
    FVector ImpactNormal = Hit.ImpactNormal;

    // Perform further actions based on the collision data
    // ...
}
```

Here's an example of how to subscribe and unsubscribe from the `OnComponentHit` delegate in Unreal Engine using C++:

```cpp
// MyCustomComponent.h

#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "MyCustomComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class YOURPROJECT_API UMyCustomComponent : public UPrimitiveComponent
{
    GENERATED_BODY()

public:
    // Constructor
    UMyCustomComponent();

    // Called when the component is hit by something
    UFUNCTION()
    void HandleComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                            FVector NormalImpulse, const FHitResult& Hit);

    // Subscribe to the OnComponentHit delegate
    virtual void BeginPlay() override;

    // Unsubscribe from the OnComponentHit delegate
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
```

```cpp
// MyCustomComponent.cpp

#include "MyCustomComponent.h"

UMyCustomComponent::UMyCustomComponent()
{
    // Enable collision for this component
    SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void UMyCustomComponent::HandleComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                            FVector NormalImpulse, const FHitResult& Hit)
{
    // Handle the hit event here
    // ...
}

void UMyCustomComponent::BeginPlay()
{
    Super::BeginPlay();

    // Subscribe to the OnComponentHit delegate
    OnComponentHit.AddDynamic(this, &UMyCustomComponent::HandleComponentHit);
}

void UMyCustomComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    // Unsubscribe from the OnComponentHit delegate
    OnComponentHit.RemoveDynamic(this, &UMyCustomComponent::HandleComponentHit);

    Super::EndPlay(EndPlayReason);
}
```
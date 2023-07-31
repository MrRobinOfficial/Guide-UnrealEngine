```cpp
#include "YourPlayerController.h"
#include "DrawDebugHelpers.h"

void AYourPlayerController::LineTraceFromCamera()
{
    // Get the player's viewpoint
    FVector CameraLocation;
    FRotator CameraRotation;
    GetPlayerViewPoint(CameraLocation, CameraRotation);

    // Calculate the end location of the line trace
    FVector TraceEnd = CameraLocation + (CameraRotation.Vector() * TraceDistance);

    // Set up trace parameters
    FCollisionQueryParams TraceParams(FName(TEXT("LineTrace")), true, this);

    // Perform the line trace
    FHitResult HitResult;
    GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, TraceEnd, ECC_Visibility, TraceParams);

    // Check if the trace hit something
    if (HitResult.bBlockingHit)
    {
        // Access information about the hit object
        AActor* HitActor = HitResult.GetActor();
        if (HitActor)
        {
            // Do something with the hit actor
            // For example, print its name
            FString ActorName = HitActor->GetName();
            UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *ActorName);
        }

        // Draw a debug line to visualize the trace
        DrawDebugLine(GetWorld(), CameraLocation, HitResult.ImpactPoint, FColor::Green, false, 2.0f);
    }
    else
    {
        // If the trace didn't hit anything, draw a debug line to the maximum trace distance
        DrawDebugLine(GetWorld(), CameraLocation, TraceEnd, FColor::Red, false, 2.0f);
    }
}
```
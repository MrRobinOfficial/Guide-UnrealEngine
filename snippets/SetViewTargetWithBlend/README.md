```cpp
#include "YourPlayerController.h"

// YourPlayerController.cpp

void AYourPlayerController::ChangeCameraView(AActor* NewViewTarget, float BlendTime)
{
    if (IsValid(NewViewTarget))
    {
        // Set the new view target with blending
        SetViewTargetWithBlend(NewViewTarget, BlendTime);
    }
}
```

In this example, we have a custom `AYourPlayerController` class that inherits from `APlayerController`. Inside the class, we have a function named `ChangeCameraView`, which takes an `AActor*` parameter called `NewViewTarget` and a `float` parameter called `BlendTime`.

The `SetViewTargetWithBlend` function is a member of the `APlayerController` class, and it allows you to smoothly transition the camera view to a new target (another actor) with a specified blend time. The function takes the new view target as the first parameter and the blend time as the second parameter.

In the `ChangeCameraView` function, we first check if the `NewViewTarget` is a valid actor using the `IsValid` function. If it's valid, we call `SetViewTargetWithBlend` to change the camera view to the new target with the specified blend time.

You can call this `ChangeCameraView` function from your player controller to smoothly switch the camera's view to a different actor in your game.
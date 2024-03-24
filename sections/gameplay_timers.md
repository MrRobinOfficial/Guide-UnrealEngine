## ⏳ Gameplay Timers

Timer construct for performing delayed or repeated actions. Timers are incredibly helpful for gameplay scenarios.

**Timers** schedule actions to be performed after a delay, or over a period of time. For example, you may want to make the player invulnerable after obtaining a power-up item, then restore vulnerability after 10 seconds. Or you may want to apply damage once per second while the player moves through a room filled with toxic gas. Such actions can be achieved through the use of timers.

> [!NOTE]
> Timers will be canceled automatically if the Object that they are going to be called on, such as an Actor, is destroyed before the time is up. In this case, the timer handle will become invalid and the function will not be called.

```cpp
// .h

/* Handle to manage the timer */
FTimerHandle TimerHandle;

// Must mark a function with UFUNCTION, as UHT needs it, in order to find it.
UFUNCTION()
void OnExplode();
```

```cpp
// .cpp

/* Activate the bomb to explode after 1.5 seconds */
void ABombActor::OnUsed(APawn* InstigatorPawn)
{
    float Delay = 1.5f; // In seconds
    bool bLooping = false; // If we want to repeat this.

    GetWorld()->GetTimerManager().SetTimer(
        TimerHandle, // handle to cancel timer at a later time
        this, // the owning object
        &ABombActor::OnExplode, // function to call on elapsed
        Delay,
        bLooping
    );
}

void ABombActor::OnExplode()
{
    // ...
}
```

Instead of calling `SetTimer()`, you can create delegate object with a bind function.

```cpp
FTimerHandle TimerHandle;
FTimerDelegate Delegate; // Delegate to bind function with parameters

Delegate.BindUFunction(this, &ABombActor::OnExplode);

float Delay = 1.5f;
bool bLooping = false;

GetWorld()->GetTimerManager().SetTimer(TimerHandle, Delegate, Delay, bLooping);
```

You can also specify parameters, if you wish to pass to the bounded function:

```cpp
Delegate.BindUFunction(this, &APlayerCharacter::Heal, 150, true);

void Heal(int32 HealAmount, bool bReviveIfDead)
{
    // ...
}
```

If we wish to stop any of the timer, we can either call `ClearTimer()` or `ClearAllTimersForObject()`:

```cpp
// Clear the specified timer handle
GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

// Alternatively you can clear ALL timers that belong to this (Actor) instance.
GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
```

> [!TIP]
> Calling `SetTimer()` with a rate less than or equal to zero is identical to calling `ClearTimer()`.

To pause or unpause a timer, you can call either `PauseTimer()` or `UnPauseTimer()` function:

```cpp
// Pause the specified timer handle
GetWorld()->GetTimerManager().PauseTimer(TimerHandle);

// Unpause the specified timer handle
GetWorld()->GetTimerManager().UnPauseTimer(TimerHandle);
```

To check if a timer is running, you can call `IsTimerActive()` function:

```cpp
// Is this weapon waiting to be able to fire again?
GetWorldTimerManager().IsTimerActive(this, &AUTWeapon::RefireCheckTimer);
```

You can also access the current rate (time between activations) of a timer from its timer handle:

```cpp
// This weapon's rate of fire changes as it warms up. Is it currently waiting to fire, and if so, how long is the current delay between shots?
GetWorldTimerManager().GetTimerRate(this, &AUTWeapon::RefireCheckTimer);
```

If you want the elapsed and remaining time, you can access via `GetTimerElapsed()` function:

```cpp
// How long will it be until this weapon is ready to fire again? If the answer comes back as -1, it is ready now.
GetWorldTimerManager().GetTimerElapsed(this, &AUTWeapon::RefireCheckTimer);
```

You can read more about [Gameplay Timers on Unreal's docs](https://docs.unrealengine.com/5.3/en-US/gameplay-timers-in-unreal-engine/).

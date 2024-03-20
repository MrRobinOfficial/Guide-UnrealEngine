## 🏛 Create custom class

<table><tr><td>
This section was NOT written in conjunction with ChatGPT.
</td></tr></table>

<figure>
    <img src="static/img/ActorLifeCycle.png" alt="Lifecycle breakdown" />
    <figcaption>Lifecycle breakdown</figcaption>
</figure>

You can read more about [Actor's lifecycle at Unreal's docs](https://docs.unrealengine.com/5.3/en-US/unreal-engine-actor-lifecycle/).

### AActor

By inheriting from `AActor` class, you have these popular functions:

```cpp
/**
 * This function is called after the class's constructor, inside the Editor.
 * It's a safe way to initialize components inside the editor.
 */
void PostInitComponents();

/**
 * "Awake/Start" method
 *
 * This function is called when an actor is spawned or respawned.
 *
 * It's the perfect place to set up default values for your actor's
 * properties, initialize components, and start any asynchronous work
 * that needs to occur when the actor is first created.
 */
void BeginPlay();

/**
 * "Update" method
 *
 * This function is called every frame, with the time since the last
 * update as its parameter.
 *
 * Use this function to update your actor's state, like checking
 * whether it's colliding with something or not.
 *
 * NOTE; Try to avoid overusing Tick() function. Since, Unreal's core logic, is simply as runs for loop and calling each function for each lickable UObject. Which can be very expensive, with many and unnecessary update calls.
 * Here are some tips to overcome this issue:
 *      - Change your workflow to an event based driven system. Either by using delegates or single call functions.
 *      - Change your tick interval to a slower interval. If you require for UObject to tick, but don't require updating a single frame (then this is a perfect fit).
 *
 * @param DeltaTime Time since last update
 */
void Tick(float DeltaTime);

/**
 * "Destroy" method
 *
 * This function is called when an actor is destroyed, or when it's
 * forced to be destroyed (e.g. when its outermost `UWorld` is shut
 * down).
 *
 * It's a good place to clean up any resources that your actor
 * allocated during its lifetime. Like delegates (NOTE; some delegates are bind directly to UObject and don't require to unbind directly).
 */
void EndPlay();

/**
 * Returns the location of the RootComponent of this Actor
 *
 * @return Location of the RootComponent
 */
FVector GetActorLocation() const;

/**
 * Returns the rotation of the RootComponent of this Actor
 *
 * @return Rotation of the RootComponent
 */
FRotator GetActorRotation() const;

/**
 * Returns the Actor's world-space scale.
 *
 * @return The world-space scale of the actor
 */
FVector GetActorScale3D() const;

/**
 * Getter for the cached world pointer, will return null if the actor is not actually spawned in a level
 *
 * @return The world pointer
 */
UWorld* GetWorld() const;

/**
 * Get the owner of this Actor, used primarily for network replication.
 *
 * @return The owner of this Actor
 */
AActor* GetOwner() const;

/**
 * Find all Actors which are attached directly to a component in this actor
 *
 * @param[out] OutActors       The array to fill with the attached actors
 * @param bResetArray          Whether to reset the array before adding new Actors
 * @param bRecursivelyIncludeAttachedActors Whether to include attached actors of attached actors also
 */
void GetAttachedActors(TArray<AActor*>& OutActors, bool bResetArray = true, bool bRecursivelyIncludeAttachedActors = false) const;

/**
 * Get all components derived from specified ComponentClass and fill in the OutComponents array with the result.
 *
 * @tparam AllocatorType       The allocator type to use for OutComponents
 * @tparam ComponentType       The type of the components to get
 * @param ComponentClass       The class of the components to get
 * @param[out] OutComponents  The array to fill with the found components
 * @param bIncludeFromChildActors Whether to include components from Child Actors also
 */
template<class AllocatorType, class ComponentType>
void GetComponents(TSubclassOf<UActorComponent> ComponentClass, TArray<ComponentType*, AllocatorType>& OutComponents, bool bIncludeFromChildActors = false) const;

/**
 * Searches components array and returns first encountered component of the specified class
 *
 * @param ComponentClass    The class of the component to search for
 * @return The found component or nullptr if not found
 */
UActorComponent* GetComponentByClass(TSubclassOf<UActorComponent> ComponentClass) const;
```

### UActorComponent

By inheriting from `UActorComponent` class, you have these popular functions:

```cpp
/**
 * Returns the owner of this component
 *
 * @return Owner of this component
 */
UObject* GetOwner() const;

/**
 * Returns the SceneComponent this component is attached to, or nullptr if not attached.
 *
 * @return The SceneComponent this component is attached to, or nullptr if not attached
 */
UWorld* GetWorld() const;

/**
 * Returns whether the component is active or not
 */
bool IsActive() const;

/**
 * Returns whether this component has tick enabled or not
 */
bool IsComponentTickEnabled() const;

/**
 * Activates the SceneComponent, should be overridden by native child classes.
 *
 * @param bReset If true, reset the component before activating it
 */
void Activate(bool bReset);

/**
 * Deactivates the SceneComponent.
 */
void Deactivate();

/**
 * Set this component's tick functions to be enabled or disabled.
 *
 * @param bEnabled If true, enable the tick functions, otherwise disable
 */
void SetComponentTickEnabled(bool bEnabled);

/**
 * Sets the tick interval for this component's primary tick function.
 *
 * @param TickInterval The tick interval in seconds
 */
void SetComponentTickInterval(float TickInterval);

/**
 * Function called every frame on this ActorComponent.
 *
 * @param DeltaTime The time since the last frame in seconds
 * @param TickType The kind of tick this is (LEVELTICK_All, LEVELTICK_Editor, LEVELTICK_TimeOnly)
 * @param ThisTickFunction Pointer to the original function that is being called
 */
void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);
```

### USceneComponent

By inheriting from `USceneComponent` class, you have these popular functions:

```cpp
/**
 * Returns the SceneComponent this component is attached to, or nullptr if not attached.
 *
 * @return The SceneComponent this component is attached to, or nullptr if not attached
 */
USceneComponent* GetAttachmentRoot() const;

/**
 * Detaches this component from its parent component.
 *
 * @param bMaintainWorldTransform Whether to maintain the world transform of this component
 */
void DetachFromComponent(bool bMaintainWorldTransform = false);

/**
 * Attaches this component to the supplied parent component.
 *
 * @param Parent                The component to attach to
 * @param SocketName            If the parent is a USkeletalMeshComponent, this is the name of the socket to attach to
 * @param AttachLocation        The location in world space to attach this component
 */
void AttachToComponent(USceneComponent* Parent, FName SocketName = NAME_None, const FAttachmentTransformRules& AttachRules = AttachmentTransformRules::KeepRelativeTransform);

/**
 * Attaches this component to the supplied parent component.
 *
 * @param Parent                The component to attach to
 * @param AttachLocation        The location in world space to attach this component
 */
void AttachToComponent(USceneComponent* Parent, const FTransform& AttachLocation, const FAttachmentTransformRules& AttachRules  FAttachmentTransformRules::KeepRelativeTransform);

/**
 * Attaches this component to the supplied parent component.
 *
 * @param Parent                The component to attach to
 */
void AttachTo(USceneComponent* Parent);

/**
 * Attaches this component to the supplied parent component.
 *
 * @param Parent                The component to attach to
 */
void AttachTo(AActor* Parent);

/**
 * Attaches this component to the supplied parent component.
 *
 * @param Parent                The component to attach to
 */
void AttachToComponent(UActorComponent* Parent, const FAttachmentTransformRules& AttachRules = AttachmentTransformRules::KeepRelativeTransform);

/**
 * Attaches this component to the supplied parent component.
 *
 * @param Parent                The component to attach to
 */
void AttachToComponent(UActorComponent* Parent, const FTransform& AttachLocation, const FAttachmentTransformRules& AttachRules  FAttachmentTransformRules::KeepRelativeTransform);

/**
 * Attaches this component to the supplied parent component.
 *
 * @param Parent                The component to attach to
 */
void AttachTo(UActorComponent* Parent);

/**
 * Returns true if this component is currently attached to the supplied component
 *
 * @param InComponent           The component to check against
 * @return                      true if this component is currently attached to InComponent
 */
bool IsAttachedTo(const USceneComponent* InComponent) const;

/**
 * Returns true if this component is currently attached to the supplied component
 *
 * @param InComponent           The component to check against
 * @return                      true if this component is currently attached to InComponent
 */
bool IsAttachedTo(const UActorComponent* InComponent) const;

/**
 * Returns the Component to World transform, calculated from this component's AttachmentTransform,
 * unless overridden by any parents.
 */
const FTransform& GetComponentToWorld() const;

/**
 * Returns the Component to World transform, calculated from this component's AttachmentTransform,
 * unless overridden by any parents.
 */
FTransform CalcNewComponentToWorld(const FTransform& NewAttachmentTransform) const;
```

### APawn

By inheriting from `APawn` class, you have these popular functions:

```cpp

/**
 * Add movement input along the given world direction vector (usually normalized) scaled by 'ScaleValue'.
 *
 * This function is used to control movement of an actor without using physics or movement components.
 * For example, it can be used to move a character in a top-down game.
 *
 * @param WorldDirection Direction vector (in world space) in which movement is input.
 * @param ScaleValue Scale value for the input.
 * @param bForce If `true`, forces the input to be applied even if the component is not moving.
 */
void AddMovementInput(FVector WorldDirection, float ScaleValue, bool bForce);

/**
 * Add input (affecting Yaw) to the Controller's ControlRotation, if it is a local PlayerController.
 *
 * This function is used to control rotation of an actor without using a camera component.
 * For example, it can be used to rotate a character in a first-person shooter game.
 *
 * @param Val Input value (affecting Yaw) to be applied to the Controller's ControlRotation.
 */
void AddControllerYawInput(float Val);

/**
 * Add input (affecting Pitch) to the Controller's ControlRotation, if it is a local PlayerController.
 *
 * This function is used to control rotation of an actor without using a camera component.
 * For example, it can be used to rotate a character in a first-person shooter game.
 *
 * @param Val Input value (affecting Pitch) to be applied to the Controller's ControlRotation.
 */
void AddControllerPitchInput(float Val);

/**
 * Add input (affecting Roll) to the Controller's ControlRotation, if it is a local PlayerController.
 *
 * This function is used to control rotation of an actor without using a camera component.
 * For example, it can be used to rotate a character in a first-person shooter game.
 *
 * @param Val Input value (affecting Roll) to be applied to the Controller's ControlRotation.
 */
void AddControllerRollInput(float Val);

/**
 * Returns velocity (in cm/s (Unreal Units/second) of the rootcomponent if it is either using physics or has an associated ovementComponent
 *
 * This function is used to get the current velocity of an actor.
 *
 * @return Current velocity of the actor's root component (in cm/s (Unreal Units/second) or (0, 0, 0) if it doesn't have any ovement components.
 */
FVector GetVelocity();
```

### UObject

By inheriting from `UObject` class, you have these popular functions:

```cpp
/**
 * Returns the name of this object (with no path information)
 *
 * Name of the object.
 *
 * @return Name of the object (with no path information).
 */
FString GetName() const;

/**
 * Returns the UClass that defines the fields of this object
 *
 * @return UClass that defines the fields of this object.
 */
UClass* GetClass();

/**
 * Returns the UObject this object resides in (e.g. parent object)
 *
 * @return UObject this object resides in (e.g. parent object).
 */
UObject* GetOuter();

/**
 * Checks to see if the object appears to be valid
 *
 * @return true if the object appears to be valid, false otherwise.
 */
bool IsValidLowLevel();

/**
 * Returns true if this object is of the specified type.
 *
 * @param SomeBase The class to check this object against.
 * @return true if this object is of the specified type, false otherwise.
 */
template<typename OtherClassType>
bool IsA(OtherClassType SomeBase) const;
```

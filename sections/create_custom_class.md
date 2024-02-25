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
// Safe way to initialize components inside the editor
// Calls after the class's constructor
void PostInitComponents();

// "Awake/Start" method
// Calls when being spawned or respawned
void BeginPlay();

// "Update" method
void Tick(float DeltaTime);

// "Destroy" method
// Calls when despawning or when being force to destroy
void EndPlay();
```

### UActorComponent

By inheriting from `UActorComponent` class, you have these popular functions:

```cpp
// Code here
```

### APawn

By inheriting from `APawn` class, you have these popular functions:

```cpp
// Code here
```

### UObject

By inheriting from `UObject` class, you have these popular functions:

```cpp
// Code here
```

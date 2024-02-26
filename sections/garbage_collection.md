<!-- prettier-ignore-start -->

## 🗑️ Garbage Collection

<table><tr><td>
This section was written in conjunction with ChatGPT.
</td></tr></table>

Garbage Collection is an automatic memory management feature used in modern languages like C#[^12], Python[^11], and Javascript[^14], which automatically removes objects from memory when they are no longer in use.

In a garbage-collected environment, you can create objects, use them, and then set the variable pointing to them as null when done, and the garbage collector takes care of freeing up the memory. Unlike lower-level languages like C[^10] and C++, which require manual memory management, Unreal Engine has its own Garbage Collection system to simplify memory management for developers.

You can read more about [Stack vs Heap](#-stack-vs-heap) section. Which tells more about how the memory is management in programming languages.

You can also read more about [Unreal Object Handling on their docs](https://docs.unrealengine.com/5.2/en-US/unreal-object-handling-in-unreal-engine/).

### How does it work

When you create a UObject-derived object in Unreal Engine, it becomes part of the garbage collection system, which automatically identifies and removes unused objects every 30-60 seconds or as needed based on system memory. The garbage collection system maintains a "Root Set" of objects that should always be kept alive, and it uses reflection to trace object references and ensure objects are reachable. Objects outside the Root Set and not reachable are marked for garbage collection, and their memory is freed.

By properly using UE's decorators, you can avoid issues with dangling pointers and crashes caused by accessing garbage-collected objects.

#### Rules

Every member of a class should be declared as a `UPROPERTY`
> If an member is left “naked,” unreal will not know about it. So, an object you are pointing at could get deleted out from under you! It is safe to leave value types such as an `int` or a `bool` “naked” although they could not be saved, replicated, or appear in the editor.

Member pointers should only point at `UObject` or UObject-derived objects
> The garbage collector is only smart enough to recognize relationships to an object, so the object could get deleted out from under your pointer.

Any non-UObject pointer must be pointing to something “global” in the engine, or something within its own `UObject`
> The garbage collector could delete the object that owns what you are pointing at.

> [!WARNING]
> For the garbage collector to do its work of determining what is safe to delete (for a container), it must traverse every field of every object. While Unreal provides several types of containers (`TArray`, `TMap`, …) the garbage collector only considers pointers in `TArray`.

#### Examples

```cpp
UPROPERTY()
TArray<UWidget*> LotsOfWidgets;

TMap<int, TWeakObjectPtr<UWidget>> LotsOfWeakWidgets;
```

### Manual memory management

UObjects should never be created with `new`, but only with the default creation methods (`NewObject()`, `SpawnActor()`, `CreateDefaultSubobject()`).

### Collection and Mark as garbage

<table><tr><td>

## Conditions

* By having a strong reference (`UPROPERTY`) to them (from objects that are also referenced)

* By calling `UObject::AddReferencedObjects()` (from objects that are also referenced)

* By adding them to the root set with `UObject::AddToRoot()` (typically unnecessary)

</td></tr></table>

When objects do not fulfill any of the above conditions, on the next GC cycle they will be marked as unreachable and garbage collected (destroyed).

To force the destruction of objects that are still reachable, you can call `UObjectBaseUtility::MarkAsGarbage()` on them, and it will force their destruction on the next GC cycle (you generally want to avoid doing this, as that is what garbage collection is for, and some classes, like `AActor` and `UActorComponent` do not directly support it).

The destruction of an object doesn't necessarily all happen in the same frame, when garbage collection starts on it, it will first call `BeginDestroy()` (do not call this yourself), then, when ready `FinishDestroy()`.

> [!NOTE]
> Raw pointers declared with `UPROPERTY`, will be set to `nullptr`

### Validation

Whenever code references an `AActor` or a `UActorComponent`, it has to deal with the possibility that `AActor::Destroy()` could be called on the actor or `UActorComponent::DestroyComponent()` could be called on the component. These functions will mark them for pending kill, thus triggering their garbage collection at the first opportunity (note that destroying an actor also destroys all its components).

Since the garbage collector automatically nulls out `UPROPERTY` pointers when it actually gets to destroy them, null-checking an actor or component pointer is sufficient to know it's safe to use, though you might also want to check `IsPendingKill()` on them (through `IsValid()`) to avoid accessing them after they have been marked for destruction (`TWeakObjectPtr` already checks for this when retrieving the raw pointer).

```cpp
bool IsValid(const UObject* Test);
```

Global function that automatically checks if an object pointer is non-null and not pending kill.

```cpp
UObjectBase::IsValidLowLevel();
UObjectBase::IsValidLowLevelFast();
```

Should not be used for Garbage Collection checks, as on `UPROPERTY` pointers it will always return true, while on raw pointer it will return true or false depending on whether the object had already been destroyed, but in the latter case it's also likely to also crash the application as the pointed memory could have been overwritten.

<!-- prettier-ignore-end -->

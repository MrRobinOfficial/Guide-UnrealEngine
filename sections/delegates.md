## 🔔 Delegates

<table><tr><td>
This section was NOT written in conjunction with ChatGPT.
</td></tr></table>

![Delegates](static/img/Delegates.png)

A delegate is essentially a type-safe function pointer that can be used to bind one or more functions to an event, and then trigger those functions when the event occurs.

In Blueprint, you might have encounter "**Event Dispatcher**", which under the hood is just multicast delegate.

There are three types of delegates, that Unreal uses. **Single**, **Multicast** and **Dynamic**.

Dynamic or non-dynamic essential means if we want to support binding functions inside Blueprint via reflection system[^1], which tends to be slower in performance. And non-dynamic only support binding function inside C++ code.

Then, we have multicast and single delegate. Multicast support multiple listener and execute them all at once. Whist the single delegate only support one listener at all time.

You can read more about multicast delegates, at [Unreal's docs](https://docs.unrealengine.com/5.3/en-US/multicast-delegates-in-unreal-engine/).

### Define a delegate type

To define a dynamic multicast delegate, you can declare via this macro: `DECLARE_DYNAMIC_MULTICAST_DELEGATE()`, which takes the name of the delegate as an argument.

```cpp
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMyDelegate);
```

To define a non-dynamic multicast delegate, you can declare via this macro: `DECLARE_MULTICAST_DELEGATE()`, which takes the name of the delegate as an argument.

```cpp
DECLARE_MULTICAST_DELEGATE(FMyDelegate);
```

To define a dynamic single delegate, you can declare via this macro: `DECLARE_DYNAMIC_DELEGATE()`, which takes the name of the delegate as an argument.

```cpp
DECLARE_DYNAMIC_DELEGATE(FMyDelegate);
```

To define a non-dynamic single delegate, you can declare via this macro: `DECLARE_DELEGATE()`, which takes the name of the delegate as an argument.

```cpp
DECLARE_DELEGATE(FMyDelegate);
```

### Declare a delegate variable

Once you have defined a delegate type, you can declare a delegate variable of that type. This is done using the `UPROPERTY()` macro to ensure that the delegate variable is properly managed by the Unreal Engine.

```cpp
UPROPERTY(BlueprintAssignable)
FMyDelegate MyEvent;
```

### Bind functions to the delegate

With the dynamic delegate variable declared, you can now bind one or more functions to it using the `BindDynamic()` macro.

These are macros, will helps you to write smaller code. Behind the scenes, it will automatically generates the function name string. The macro takes a reference to the object that owns the function, the name of the function, and an optional user data parameter.

* `BindDynamic(UserObject, FuncName, ...)`
* `AddDynamic(UserObject, FuncName)`
* `RemoveDynamic(UserObject, FuncName)`

```cpp
MyEvent.BindDynamic(this, &AMyActor::MyFunction);
```

```cpp
MyEvent.AddDynamic(this, &AMyActor::MyFunction);
```

```cpp
MyEvent.RemoveDynamic(this, &AMyActor::MyFunction);
```

With some arguments:

```cpp
MyEvent.BindDynamic(this, &AMyActor::MyFunction, 100, true, TEXT("Hello, World!"));
```

<!-- DECLARE_DYNAMIC_DELEGATE[_RetVal, ...]( DelegateName ) -->
<!-- TODO: Fix this -->

Here is a list of binding functions for Non-Dynamic Single Delegate:

* `Bind()` - Binds to an existing delegate object.
* `BindLambda()` - Binds a functor. This is generally used for lambda functions.
* `BindRaw()` - Binds a raw C++ pointer delegate. Since raw pointers do not use any sort of reference, calling `Execute()` or `ExecuteIfBound()` after deleting the target object is unsafe.
* `BindStatic()` - Binds a raw C++ pointer global function delegate.
* `BindSP()` - Binds a shared pointer-based member function delegate. Shared pointer delegates keep a weak reference to your object. You can use `ExecuteIfBound()` to call them.
* `BindUFUnction()` - Lorem Ipsum
* `BindUObject()` - Binds a `UObject` member function delegate. `UObject` delegates keep a weak reference to the `UObject` you target. You can use `ExecuteIfBound()` to call them.
* `BindWeakLambda()` - Lorem Ipsum
* `BindThreadSafeSP()` - Lorem Ipsum
* `UnBind()` - Unbinds this delegate.

And here is the list of binding functions for Non-Dynamic Multicast Delegate:

* `Add()` - Adds a function delegate to this multi-cast delegate's invocation list.
* `AddLambda()` - Lorem Ipsum
* `AddRaw()` - Adds a raw C++ pointer delegate.
* `AddStatic()` - Adds a raw C++ pointer global function delegate.
* `AddSP()` - Adds a shared pointer-based (fast, not thread-safe) member function delegate. Shared pointer delegates keep a weak reference to your object.
* `AddUObject()` - Adds a UObject-based member function delegate. UObject delegates keep a weak reference to your object.
* `AddUFunction()` - Lorem Ipsum
* `AddWeakLambda()` - Lorem Ipsum
* `AddThreadSafeSP()` - Lorem Ipsum
* `Remove()` - Removes a function from this multi-cast delegate's invocation list (performance is O(N)). Note that the order of the delegates may not be preserved!
* `RemoveAll()` - Removes all functions from this multi-cast delegate's invocation list that are bound to the specified UserObject. Note that the order of the delegates may not be preserved!

### Trigger the delegate

Finally, you can trigger the multicast delegate by calling the `Broadcast()` method. This will cause all bound functions to be called with the specified parameters.

```cpp
MyEvent.Broadcast();
```

And you can also trigger a single delegate, by calling the `Execute()` or `ExecuteIfBound()` method. This will cause the bound function to be called with the  specified parameters.

```cpp
// If delegate is not bound, this will cause a crash.
MyEvent.Execute();

// Use this function, if you are unsure, if the delegate is bound or not.
MyEvent.ExecuteIfBound();

// You can also do manual checking, before calling ´Execute()´ function.
bool bIsBound = MyEvent.IsBound();
```

### Summary

By using delegates, developers can create modular and flexible event systems that can be easily extended and customized.

Delegates can be used to trigger events in response to user input, game state changes, or other types of events, and can be used to implement a wide variety of gameplay features and mechanics.

> [!TIP]
> Here is an [online tool by BenUI](https://benui.ca/unreal/delegates-advanced/#delegate-signature-tool) for helping you to create a delegate macro.

> [!TIP]
> Try to **USE** delegates where ticking is not necessary. This help save on performance on tick

> [!CAUTION]
> If you don't remove the binding afterward, when the `UObject` gets destroyed. This will cause a memory leak. Since, the binding is still alive, even though the `UObject` not be alive.

| Type                                         | Binds C++ Function | Binds `UFUNCTION` |
| -------------------------------------------- | ------------------ | ----------------- |
| Singlecast                                   | Yes                | Yes               |
| Multicast                                    | Yes                | No                |
| ~~Event~~ (**OBSOLETE**)                                        | Yes                | ?                 |
| Dynamic Singlecast                           | No                 | Yes               |
| Dynamic Multicast                            | No                 | Yes               |
| `FTimerDelegate` (Singlecast)                | Yes                | Yes               |
| `FTimerDynamicDelegate` (Dynamic Singlecast) | No                 | Yes               |

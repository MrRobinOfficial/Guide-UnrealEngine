<!-- prettier-ignore-start -->

## 🏛 Create custom interface

<table><tr><td>
This section was NOT written in conjunction with ChatGPT.
</td></tr></table>

Interface are very useful for handling functions in a generic way. It allows you to create a contract with specified functions, which a programmer can extend on top of a specified class.

For an example, IVehicle can contain functions such as `Honk()` or `StallEngine()`. However, these functions can be implemented in a range of classes. Such as `ACarPawn` or `ABoatPawn`.

When calling the interface function in C++, Unreal will check if the type extends the interface. If not, the call gets skipped. This allows you to call the interface function on `UObject` and is not limited to only types of `ACarPawn` or `ABoatPawn`.

This also allows you to extend the interface inside Blueprint instead. For an example, you don't have to create the interface logic inside C++, but rather create the logic at Blueprint level instead.

You can read more about interfaces, at [Unreal's docs](https://dev.epicgames.com/documentation/en-us/unreal-engine/interfaces-in-unreal-engine).

### Creating interface inside C++

Here's a template file for creating an interface inside C++:

```cpp
// IVehicle.h

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IVehicle.generated.h"

/*
This class does not need to be modified.
Empty class for reflection system visibility.
Uses the UINTERFACE macro.
Inherits from UInterface.
*/
UINTERFACE(MinimalAPI, Blueprintable)
class UVehicle : public UInterface
{
    GENERATED_BODY()
};

/* Actual Interface declaration. */
class IVehicle
{
    GENERATED_BODY()

    // Add interface functions to this class. This is the class that will be inherited to implement this interface.

public:
    // Add interface function declarations here

    // BlueprintNativeEvent - Allows you to overwrite the function in either C++ or Blueprint
    // BlueprintImplementableEvent - Allows the function to only be overwritten in Blueprint

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Vehicle")
    void Honk();

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Vehicle")
    void StallEngine();

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Vehicle")
    void Explode(bool bForce = true);
};
```

> [!WARNING]
> `BlueprintNativeEvent` allows you to overwrite the function in either C++ or Blueprint, but if you use `BlueprintImplementableEvent` it only allows the function to only be overwritten in Blueprint.

### Extending the interface function:

When adding an interface class to a C++ class, you must use the suffix of `_Implementation` for all the functions that you are overwriting. Otherwise, UHT[^2] will not recognize the function.

Here's an example, of extending the interface functions inside C++:

```cpp
// ACarPawn.h

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "IVehicle.h" // Include the interface's header
#include "CarPawn.generated.h"

UCLASS()
class ACarPawn : public APawn, public IVehicle
{
protected:
    void Honk_Implementation();
    void StallEngine_Implementation();
    void Explode_Implementation(bool bForce);
};
```

```cpp
// ACarPawn.cpp

void ACarPawn::Honk_Implementation()
{
    // Add code here...
}

void ACarPawn::StallEngine_Implementation()
{
    // Add code here...
}

void ACarPawn::Explode_Implementation(bool bForce)
{
    // Add code here...
}
```

### Calling the interface function

When calling the interface function inside C++, you are required to call the function with a prefix of `Execute`. If you don't use the prefix, you will get a warning from Unreal Engine.

> [!NOTE]
> You are calling the interface function from the interface itself. Meaning, instead of `ACarPawn->Explode()`, which is an interface function. You must call the function as: `IVehicle::Execute_Explode()` instead. With the parameter being on what object you want the interface function to be called on.

```cpp
UObject* CarObject = nullptr; // The UObject, that you wish to call the function on.
const bool bForce = true; // Parameters

// The syntax for calling the interface function
IVehicle::Execute_Explode(CarObject, bForce);
```

### Checking if the UObject extends the interface

Sometimes, you must check if the `UObject` has the interface class attach to it. You can either do by calling `Implements()` function, which returns a boolean. Or you can do a cast operation. The cast will return `nullptr`, if the operation failed.

```cpp
UObject* CarObject = nullptr; // The UObject, that you wish to call the function on.

bool bIsImplemented = CarObject->Implements<IVehicle>();
```

A longer version of `Implements()` function:

```cpp
UObject* CarObject = nullptr; // The UObject, that you wish to call the function on.

bool bIsImplemented = CarObject->GetClass()->ImplementsInterface(UVehicle::StaticClass());
```

And here is the cast version:

```cpp
UObject* CarObject = nullptr; // The UObject, that you wish to call the function on.

IVehicle* VehiclePtr = Cast<IVehicle>(CarObject);
```

> [!CAUTION]
> The `Cast<>` method only works, if the interface is implemented in a C++ class. If the interface was instead implemented in Blueprint, then the cast will return `nullptr`. You can use `TScriptInterface<>` to safely copy an interface pointer. In alternative, you have the weak interface pointer (`TWeakInterfacePtr`).

### Reference to an interface object

If you wish to reference an interface object, and you want safety grantee for both Blueprint and C++, then must you `TScriptInterface<>`.

```cpp
void DestroyVehicle(const TScriptInterface<IVehicle>& Vehicle)
{
    const bool bForce = true;
    IVehicle::Execute_Explode(Vehicle.GetObject(), bForce);
}
```

However, if you tend to use the interface pointer inside C++, you can either use a regular raw pointer to the interface.

```cpp
UObject* CarObject = nullptr; // The UObject, that you wish to call the function on.

IVehicle* VehiclePtr = Cast<IVehicle>(CarObject);
```

Or use a weak pointer (`TWeakInterfacePtr`). Note, that this pointer is weak. Meaning, the weak pointer will not prevent destruction of the object it references.

```cpp
TWeakInterfacePtr<IVehicle> VehiclePtr; // Weak pointer to the interface.
UObject* CarObject = nullptr; // The UObject, that you wish to call the function on.

VehiclePtr = Cast<IVehicle>(CarObject);

if (VehiclePtr.IsValid())
{
    // Check if the pointer is valid
}
```

For more information on weak pointers, you can read at [💾 Soft vs hard references](#-soft-vs-hard-references).

> [!TIP]
> `TScriptInterface` inside Blueprint is nicer to look at, than C++ version.

<!-- prettier-ignore-end -->

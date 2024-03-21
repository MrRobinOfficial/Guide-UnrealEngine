## 💎 Unreal Header Tool

<table><tr><td>
This section was written in conjunction with ChatGPT.
</td></tr></table>

Unreal Header Tool (UHT[^3]) is a code generator and reflection system in Unreal Engine. It processes special macros and meta tags in C++ header files and generates additional code to support Unreal Engine's reflection system, which enables various engine features like Blueprint integration, serialization, networking, and more.

Layout:

```cpp
UPROPERTY([specifier1=setting1, specifier2, ...], [meta=(key1="value1", key2="value2", ...))])
UFUNCTION([specifier1=setting1, specifier2, ...], [meta=(key1="value1", key2="value2", ...))])
UCLASS([specifier1=setting1, specifier2, ...], [meta=(key1="value1", key2="value2", ...))])
USTRUCT([specifier1=setting1, specifier2, ...], [meta=(key1="value1", key2="value2", ...))])
UENUM([specifier1=setting1, specifier2, ...])
UPARAM([specifier1=setting1, specifier2, ...])
UMETA([specifier1=setting1, specifier2, ...])
```

| Macro     | Description                                                                                                                                                       | Use Case                                                                                                             |
| --------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------- |
| UPROPERTY | Specifies properties of a class member, such as replication, serialization, editability, and blueprint visibility.                                                | Used to define properties of variables within a class to control how they are handled by Unreal Engine systems.      |
| UFUNCTION | Identifies a C++ function that can be accessed and called from Blueprint visual scripting or other systems in Unreal Engine.                                      | Used to expose C++ functions to Blueprint for easy use in visual scripting and integration with Unreal Engine.       |
| UCLASS    | Defines a C++ class that is exposed to Unreal Engine's reflection system, allowing it to be used in Blueprint and other engine features.                          | Used to define classes that can be used in Blueprint and integrated into Unreal Engine systems like the Editor.      |
| USTRUCT   | Specifies a C++ struct that can be used with Unreal Engine's reflection system, making it usable in Blueprint and other engine features.                          | Used to define structs that can be used in Blueprint and integrated into Unreal Engine systems like the Editor.      |
| UENUM     | Defines a C++ enumeration that can be used with Unreal Engine's reflection system, making it usable in Blueprint and other engine features.                       | Used to define enumerations that can be used in Blueprint and integrated into Unreal Engine systems like the Editor. |
| UPARAM    | Specifies how a function parameter should be treated when used in Blueprint or other Unreal Engine systems.                                                       | Used to define parameter properties, such as Blueprint read/write access, in C++ functions exposed to Blueprint.     |
| UMETA     | Provides additional metadata for UPROPERTY, UFUNCTION, UCLASS, USTRUCT, and UENUM, allowing customization of their behavior in Unreal Engine's reflection system. | Used to attach additional information or customizations to C++ entities exposed to Unreal Engine reflection.         |

### UPROPERTY

`UPROPERTY` is a macro used to declare a property within a class that needs to be exposed to the Unreal Engine's reflection system. It allows the property to be accessed and modified by the engine and Blueprint scripts.

#### Specifiers

-   `EditAnywhere`: Allows the property to be edited in the editor and during runtime for all instances of the class.
-   `EditDefaultsOnly`: Permits editing the property only for the class's default object in the editor.
-   `EditInstanceOnly`: Enables editing the property only for instances of the class during runtime.
-   `VisibleAnywhere`: Displays the property value in the editor for all instances of the class.
-   `VisibleDefaultsOnly`: Shows the property value in the editor for the class's default object.
-   `VisibleInstanceOnly`: Displays the property value in the editor only for instances of the class.
-   `BlueprintReadOnly`: Exposes the property to Blueprint scripts, but only for reading, not writing.
-   `BlueprintReadWrite`: Exposes the property to Blueprint scripts for both reading and writing.
-   `Category`: Organizes properties into named categories in the editor for better organization and readability.
-   `EditFixedSize`: Specifies that an `TArray` or `TMap` property should be editable in the Details Panel of the Unreal Editor with a fixed number of elements, preventing addition or removal.
-   `Transient`: Indicates that a property should not be serialized, making it non-persistent and not saved when saving the state of the object.
-   `Replicated`: Automatically replicates the property's value to clients in a multiplayer environment when the property changes on the server.
-   `ReplicatedUsing`: Specifies a custom function that should be called on both the server and clients to handle replication of the property's value.
-   `SimpleDisplay`: Indicates that the property's value should be displayed in a simple and concise manner in editor UI.
-   `AdvancedDisplay`: Indicates that the property's value should be displayed with advanced options in editor UI.
-   `Config`: Marks the property to be serialized to the project configuration file for external customization.
-   `GlobalConfig`: Marks the property to be serialized to the global configuration file for external customization across all projects.

#### Meta tags

-   `DisplayName`: Sets a custom display name for the property in the Unreal Editor.
-   `Tooltip`: Provides a tooltip description for the property in the Unreal Editor.
-   `ClampMin`: Sets the minimum allowed value for the property in the Unreal Editor.
-   `ClampMax`: Sets the maximum allowed value for the property in the Unreal Editor.
-   `AllowPrivateAccess`: Allows access to private members within the class it belongs to.
-   `Units`: Provides a human-readable unit label for the property in the Unreal Editor.

#### Examples

```cpp
UPROPERTY(EditAnywhere, Category="Hello|Cruel|World")
int32 EditAnywhereNumber;
```

```cpp
UPROPERTY(Transient, Replicated)
int32 CurrentHealth;

UPROPERTY(Transient, ReplicatedUsing=OnArmorChanged)
int32 CurrentArmor;

UFUNCTION()
void OnArmorChanged();
```

```cpp
UPROPERTY(EditAnywhere, SimpleDisplay)
int32 MaxHealth = 100;

UPROPERTY(EditAnywhere, AdvancedDisplay)
float HealthRegenerationTime = 5.0f;
```

```cpp
// Must mark UCLASS with Config specifier

// Config can be overriden from the base class.
UPROPERTY(Config, BlueprintReadOnly)
bool bRegenerateHealth;

// GlobalConfig CANNOT be overridden from the base class.
UPROPERTY(GlobalConfig, BlueprintReadOnly)
bool bEnableHealthSimulation;
```

```cpp
UPROPERTY(EditAnywhere, EditFixedSize)
TArray<FName> Usernames = { TEXT("JohnDoe"), TEXT("MrRobin"), TEXT("JaneDoe") };
```

```cpp
UPROPERTY(EditAnywhere, meta=(Units="Celsius"))
float CookingTemperature;

UPROPERTY(EditAnywhere, meta=(Units="Kilograms"))
float TigerWeight;

UPROPERTY(EditAnywhere, meta=(Units="GB"))
float DiskSpace;

UPROPERTY(EditAnywhere, meta=(Units="Percent"))
float Happiness;

UPROPERTY(EditAnywhere, meta=(Units="times"))
float Deliciousness;
```

You can read more about [UPROPERTY by BenUi](https://benui.ca/unreal/uproperty/).

### UFUNCTION

`UFUNCTION` is a macro used to declare a function within a class that needs to be exposed to the Unreal Engine's reflection system. It allows the function to be used in Blueprint scripts and network replication.

#### Common Specifiers

-   `BlueprintCallable`: Exposes the function to Blueprint scripts, allowing it to be called from within Blueprint graphs.
-   `BlueprintPure`: Indicates that the function is a pure computation and does not modify any state, making it safe to use in Blueprint graphs without side effects.
-   `BlueprintImplementableEvent`: Serves as a placeholder function in C++ that can be overridden and implemented in Blueprint.
-   `BlueprintNativeEvent`: Similar to `BlueprintImplementableEvent`, but it also provides a C++ implementation that can be optionally overridden in Blueprint.
-   `Category`: Organizes properties into named categories in the editor for better organization and readability.

#### Common Meta tags

-   `DisplayName`: Sets a custom display name for the function in the Unreal Editor.
-   `Tooltip`: Provides a tooltip description for the function in the Unreal Editor.
-   `ShortToolTip`: Provides a short tooltip description for the function in the Unreal Editor.
-   `AllowPrivateAccess`: Allows access to private members within the class it belongs to.
-   `HideSelfPin`: Hides the "self" pin, which indicates the object on which the function is being called. The "self" pin is automatically hidden on `BlueprintPure` functions that are compatible with the calling Blueprint's Class. Functions that use the `HideSelfPin` Meta Tag frequently also use the `DefaultToSelf` Specifier.
-   `BlueprintInternalUseOnly`: This function is an internal implementation detail, used to implement another function or node. It is never directly exposed in a Blueprint graph.
-   `BlueprintProtected`: This function can only be called on the owning Object in a Blueprint. It cannot be called on another instance.
-   `DeprecatedFunction`: Any Blueprint references to this function will cause compilation warnings telling the user that the function is deprecated. You can add to the deprecation warning message (for example, to provide instructions on replacing the deprecated function) using the `DeprecationMessage` metadata specifier.

#### Examples

```cpp
UFUNCTION(BlueprintPure)
int32 BlueprintPureFunction();

UFUNCTION(BlueprintCallable)
int32 BlueprintCallableFunction();

UFUNCTION(BlueprintCallable)
int32 BlueprintCallableConstFunction() const;

UFUNCTION(BlueprintPure=false)
int32 BlueprintPureFalseFunction() const;
```

```cpp
UFUNCTION(BlueprintCallable, Category = "Doggy Daycare", meta=(ReturnDisplayName = "Success"))
bool TryPetDog(const FName Name);
```

You can read more about [UPROPERTY by BenUi](https://benui.ca/unreal/ufunction/).

### UCLASS

`UCLASS` is a macro used to declare a class that is intended to be used in Unreal Engine's reflection system. It allows the class to be instantiated, exposed to Blueprint, and used in various engine systems.

#### Common Specifiers

-   `Blueprintable`: Allows the class to be used as a blueprint in the Unreal Editor.
-   `BlueprintType`: Specifies that the class can be instantiated and manipulated in Blueprint scripts.
-   `Abstract`: Indicates that the class is an abstract class and cannot be instantiated directly.
-   `Transient`: Excludes the class from being serialized and saved in the game's persistent data.
-   `MinimalAPI`: Restricts the class's visibility for export, making it more suitable for engine internal use.
-   `NotBlueprintType`: Prevents the class from being used as a blueprint.

#### Common Meta tags

-   `DisplayName`: Sets a custom display name for the class in the Unreal Editor.
-   `ToolTip`: Provides a tooltip description for the class in the Unreal Editor.
-   `HideCategories`: Hides specific property categories from being displayed in the Unreal Editor.
-   `ClassGroup`: Assigns the class to a specific group in the Unreal Editor's class picker.
-   `IncludePath`: Specifies the include path for the generated code of the class.
-   `BlueprintSpawnableComponent`: Marks a class derived from `USceneComponent` as spawnable in Blueprint.

#### Examples

```cpp
UCLASS(Blueprintable)
class MyActor : public AActor
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyActor")
    int32 MyIntProperty;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyActor")
    float MyFloatProperty;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyActor")
    FString MyStringProperty;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyActor")
    FMyStruct MyStructProperty;
};
```

</td></tr></table>

You can read more about [UCLASS by BenUi](https://benui.ca/unreal/uclass/).

### USTRUCT

`USTRUCT` is a macro used to declare a C++ struct that is intended to be used in Unreal Engine's reflection system. It enables the struct to be used as a property within UCLASSes and exposed to Blueprint.

#### Common Specifiers

-   `BlueprintType`: Specifies that the structure can be used in Blueprint scripts.
-   `Atomic`: Ensures that the structure is treated as an atomic type for replication in multiplayer games.
-   `NotReplicated`: Excludes the structure from being replicated across the network.

#### Common Meta tags

-   `DisplayName`: Sets a custom display name for the structure in the Unreal Editor.
-   `ToolTip`: Provides a tooltip description for the structure in the Unreal Editor.
-   `Category`: Specifies the category in which the structure will appear in the Unreal Editor.

#### Examples

```cpp
USTRUCT(BlueprintType)
struct FMyStruct
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "MyStruct")
    int32 Value1;

    UPROPERTY(BlueprintReadWrite, Category = "MyStruct")
    FString Value2;
};
```

</td></tr></table>

You can read more about [USTRUCT by BenUi](https://benui.ca/unreal/ustruct/).

### UENUM

`UENUM` is a macro used to declare an enumeration that is intended to be used in Unreal Engine's reflection system. It allows the enumeration to be exposed to Blueprint and used within `UCLASS`es.

#### Common Specifiers

-   `BlueprintType`: Specifies that the enumeration can be used in Blueprint scripts.
-   `DisplayNames`: Specifies a list of custom display names for each enumeration value in the Unreal Editor.

#### Common Meta tags

-   `DisplayName`: Sets a custom display name for the enumeration in the Unreal Editor.
-   `ToolTip`: Provides a tooltip description for the enumeration in the Unreal Editor.
-   `Hidden`: Hides the enumeration from being displayed in the Unreal Editor.
-   `Bitflags`: Indicates that the enumeration represents a set of bit flags.
-   `EnumRange`: Specifies the minimum and maximum values for the enumeration.

#### Examples

```cpp
UENUM(BlueprintType)
enum class EWeaponType
{
    Sword         UMETA(DisplayName = "Sword Weapon"),
    Axe           UMETA(DisplayName = "Axe Weapon"),
    Bow           UMETA(DisplayName = "Bow Weapon"),
    Wand          UMETA(DisplayName = "Magic Wand"),
};
```

You can read more about [UENUM by BenUi](https://benui.ca/unreal/uenum/).

### UPARAM

`UPARAM` is a macro used to provide additional information to the Unreal Header Tool. It is used with parameters of UFUNCTION and UPROPERTY to specify how the engine should handle the data.

-   `UPARAM(Ref)`: Used to mark a parameter that is passed by reference. It ensures that the parameter is treated as a reference during code generation, which may affect how the engine handles the parameter.

-   `UPARAM(DisplayName)`: Used to set a custom display name for a function parameter when it appears in the Unreal Editor's Blueprint node graph.

-   `UPARAM(BlueprintCallable, BlueprintPure)`: Used to apply multiple specifiers to a function parameter. For example, to mark a parameter as both BlueprintCallable and BlueprintPure.

-   `UPARAM(meta = (CustomMetaTag))`: Allows developers to create custom meta tags and use them in function parameters to provide additional information to the Unreal Header Tool.

#### Examples

```cpp
UCLASS()
class MyActor : public AActor
{
    GENERATED_BODY()

public:
    // A function that takes a parameter passed by reference
    UFUNCTION(BlueprintCallable, Category = "MyActor")
    void ModifyValue(UPARAM(Ref) int32& ValueToModify)
    {
        // Modify the value passed by reference
        ValueToModify *= 2;
    }
};
```

You can read more about [UPARAM by BenUi](https://benui.ca/unreal/uparam/).

### UMETA

`UMETA` is a macro used to specify additional metadata for an UENUM entry. It allows adding custom information to enum values for use in Blueprint, UI, and other engine systems.

#### Common Specifiers

-   `DisplayName`: Sets a custom display name for the enumeration value in the Unreal Editor.
-   `ToolTip`: Provides a tooltip description for the enumeration value in the Unreal Editor.
-   `Hidden`: Hides the enumeration value from being displayed in the Unreal Editor.
-   `DisplayPriority`: Specifies the display priority for the enumeration value in the Unreal Editor.
-   `DisplayThumbnail`: Allows attaching a custom thumbnail image to the enumeration value in the Unreal Editor.
-   `CustomMetaData`: Specifies custom metadata that developers can define and use as needed.

#### Examples

```cpp
UENUM(BlueprintType)
enum class EMyEnum
{
    Value1 UMETA(DisplayName = "First Value", ToolTip = "This is the first value"),
    Value2 UMETA(DisplayName = "Second Value", ToolTip = "This is the second value"),
    Value3 UMETA(Hidden),
};
```

You can read more about [UMETA by BenUi](https://benui.ca/unreal/umeta/).

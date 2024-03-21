<!-- prettier-ignore-start -->

## 🗝️ Deep dive

<table><tr><td>
This section was written in conjunction with ChatGPT.
</td></tr></table>

### 🔖 Keywords

Here is a video about [constants keywords in C++ by Cazz](https://www.youtube.com/watch?v=KBny6MZJR64)

-   `const` - Specifies that an object or variable is read-only and cannot be modified.
-   `constexpr` - Specifies that a function or variable can be evaluated at compile-time. `constexpr` can be used for inlining variables, without using macros[^4]. **Note**, the compiler does not guarantee compile-time evaluation (only it **CAN** be evaluated at compile-time).
-   `consteval` - Specifies that a function must be evaluated at compile-time. **Note**, the compiler has to evaluated at compile-time.
-   `constinit` - Specifies that an object with static or thread storage duration should be initialized only with constant expressions.
-   `auto` - Allows the compiler to deduce the type of a variable based on its initializer.
-   `static` - Specifies that a variable or function is associated with a class rather than with a specific instance of the class.
-   `virtual` - Specifies that a function should be polymorphic, meaning that it can be overridden by a derived class.
-   `override` - Indicates that a function in a derived class is intended to override a function in the base class.
-   `break` - Causes the program to exit a loop or switch statement.
-   `continue` - Causes the program to skip to the next iteration of a loop.
-   `class` and `struct` - Are used to define user-defined types that encapsulate data and functions.
-   `inline` - Specifies that a function should be inlined (i.e., its code should be inserted directly into the calling code rather than calling the function).
-   `force_inline` - Instructs the compiler to inline a function, regardless of whether it would normally do so.
-   `new` - Allocates memory for an object and calls its constructor.
-   `delete` - Deallocates memory that was allocated with new.
-   `dynamic_cast` - Performs a runtime check to determine whether an object can be cast to a different type.
-   `static_cast` - Performs a static cast, which allows an expression to be converted to a different data type at compile time.
-   `const_cast` - - Performs a const cast.
-   `explicit` - Specifies that a constructor or conversion operator cannot be used for implicit type conversions.
-   `namespace` - Defines a scope for identifiers to avoid naming conflicts.
-   `operator` - Declares a function as an overloaded operator.
-   `template` - Allows generic programming by defining a type or function with parameters that are specified at compile time.
-   `try` and `catch` - Implements exception handling by trying a block of code that may throw an exception and catching the exception if it is thrown.

Difference between a class and struct then?

> In native C++, the main difference between a struct and a class is that struct members are public by default, whereas class members are private by default. However, this difference is largely syntactic, and struct and class can be used interchangeably to define custom types.

> However, Unreal Engine structs are used to represent data types that are typically used for data storage and manipulation, whereas classes are used to represent objects that have behavior and state.

In Unreal Engine, it's recommended to use the built-in memory management functions like `NewObject()` and `MakeShared()` to allocate memory for objects, rather than using `new` and `delete`. Using `new` and `delete` can interfere with the garbage collector and cause memory leaks or crashes in your game. It's always best to follow Unreal Engine's recommended memory management practices to ensure the stability and performance of your game.

### K2Node

<!-- TODO: Write text here! -->

You can read more about [K2Node by Oscar Olsson](https://olssondev.github.io/2023-02-13-K2Nodes/).

### ➗ Math Expression Node

<table><tr><td>
This section was NOT written in conjunction with ChatGPT.
</td></tr></table>

The Math Expression node acts like a collapsed graph. It is a single node that you can Double-click to open the sub-graph that makes up its functionality. Initially, the name/expression is blank. Whenever you rename the node, then the new expression is parsed and a new sub-graph is generated.

![Math Node Example](static/img/math_node_example.png)

You can read more about math expression node at <a href="https://docs.unrealengine.com/5.2/en-US/math-expression-node-in-unreal-engine/" target="_blank">Unreal's docs</a>.

### Call function in editor

Expose a function to call inside the Blueprint editor. With C++, you can mark `UFUNCTION` specifier `CallInEditor`.

Here is an example:

```cpp
UFUNCTION(CallInEditor, BlueprintCallable)
void DebugMessage();
```

### Call function via Console Commands

In order to call a `UFUNCTION` inside the console command, you can use `Exec` specifier. This tells Unreal Engine to add the function into the console commands list.

Here's an example:

```cpp
UFUNCTION(Exec)
void KillCharacter();
```

However, there is a downside from using this approach. Because Unreal finds the function and map to the corresponding name, Unreal cannot call multiple instances of the same function. It only prioritizes the current pawn, which is currently under possession by the player.

To call a function with multiple instances, you can type `ke * FunctionName`.

Here's an example:

```console
$ ke * KillCharacter
```

> [!NOTE]
> In the context of a Command Line Interface (CLI), the dollar sign (`$`) is typically referred to as a "prompt symbol" or simply a "prompt." It indicates that the CLI is ready to receive input from the user. The specific appearance and behavior of the prompt may vary depending on the operating system and shell being used.

### Renaming variables without breaking references

<table><tr><td>
This section was NOT written in conjunction with ChatGPT.
</td></tr></table>

During development, there are occasions when you have to rename a property, function or a class. If you compile before changing the name in other location of your code, it can cause Unreal to no longer recognize existing Assets. And therefore replace with its default initialization value.

To address this issue, Unreal Engine uses Core Redirects. Core Redirects should be configured in your project's `DefaultEngine.ini` file, or, in the case of a Plugin, the prefixed, self-named .ini file for that Plugin (for example, `BasePaper2D.ini` for the Engine's Paper2D Plugin, or `Default<GamePluginName>.ini` for a game Plugin).

In either case, the Core Redirects will be placed in the "[CoreRedirects]" section. These Core Redirects will automatically remap obsolete data while loading Assets, thus preventing data loss resulting from the renaming process.

Here is the following structure for a redirect of a property value:

```dosini
+PropertyRedirect=(OldName="CurrentClass.OldVariableName", NewName="NewOldVariableName")
```

Here's a full example of different use cases with redirects:

```dosini
[CoreRedirects]
+PropertyRedirect=(OldName="PlayerCharacter.StartHealth", NewName="InitialHealth")

+ClassRedirects=(OldName="Pawn",NewName="MyPawn",InstanceOnly=true)

+ClassRedirects=(OldName="/Script/MyModule.MyOldClass",NewName="/Script/MyModule.MyNewClass")

+ClassRedirects=(OldName="PointLightComponent",NewName="PointLightComponent",ValueChanges=(("PointLightComponent0","LightComponent0")))

+ClassRedirects=(OldName="AnimNotify_PlayParticleEffect_C",NewName="/Script/Engine.AnimNotify_PlayParticleEffect",OverrideClassName="/Script/CoreUObject.Class")

+EnumRedirects=(OldName="ENumbers",NewName="ELetters",ValueChanges=(("NumberTwo","LetterB"),("NumberThree","LetterC")))

+FunctionRedirects=(OldName="MyOldActor.OldFunction",NewName="MyNewActor.NewFunction")
+FunctionRedirects=(OldName="MyActor.OldFunction",NewName="NewFunction")

+PackageRedirects=(OldName="OldPlugin",NewName="/NewPlugin/",MatchSubstring=true)
+PackageRedirects=(OldName="/Game/DeletedContentPackage",Removed=true)

+StructRedirects=(OldName="MyStruct",NewName="MyNewStruct")
```

You can read more about on [Unreal's docs](https://docs.unrealengine.com/5.3/en-US/core-redirects-in-unreal-engine/).

---

The `MatchSubstring` argument can be used in any Core Redirect type. If present and set to `true`, the `OldName` and `NewName` fields will be treated as substrings rather than requiring exact matches. This enables multiple matches with a single Core Redirect. In the following example, we will start with a struct and a class.

Original code and values:

```cpp
USTRUCT()
struct FMyStruct
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = "Documentation")
    int32 TestInt;

    UPROPERTY(EditAnywhere, Category = "Documentation")
    int32 TestIntFromStruct;
};

UCLASS()
class REDIRECTORSTEST_API AMyActor : public AActor
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, Category = "Documentation")
    int32 TestInt;

    UPROPERTY(EditAnywhere, Category = "Documentation")
    int32 MainClassTestInt;

    UPROPERTY(EditAnywhere, Category = "Documentation")
    FMyStruct TestStruct;
};
```

<figure>
    <img src="static/img/OriginalValues.jpg" alt="Original Values" />
    <figcaption>This is the original code and the original set of values we're saving into our `AMyActor` Asset.</figcaption>
</figure>

After creating and saving an `AMyActor` Asset with the values shown above, we can close the Editor and alter the the code in the `.h` file and the Core Redirects in the game's `.ini` file. We will change the code to read as follows, changing the names of our `int32` properties:

```cpp
USTRUCT()
struct FMyStruct
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = "Documentation")
    int32 TestInteger;

    UPROPERTY(EditAnywhere, Category = "Documentation")
    int32 TestIntegerFromStruct;
};

UCLASS()
class REDIRECTORSTEST_API AMyActor : public AActor
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, Category = "Documentation")
    int32 TestInteger;

    UPROPERTY(EditAnywhere, Category = "Documentation")
    int32 MainClassTestInteger;

    UPROPERTY(EditAnywhere, Category = "Documentation")
    FMyStruct TestStruct;
};
```

With this change, we can examine the effects of a Core Redirect, and in particular the impact of `MatchSubstring`.

Results follow:

<figure>
    <img src="static/img/NoCoreRedirect.jpg" alt="NoCoreRedirect" />
    <figcaption>The properties were renamed in code, but no Core Redirect was created. As a result, no data values have migrated to the new properties.</figcaption>
</figure>

<figure>
    <img src="static/img/CoreRedirectWithoutMatchSubstring.jpg" alt="CoreRedirectWithoutMatchSubstring" />
    <figcaption>`PropertyRedirects=(OldName="TestInt",NewName="TestInteger")` causes only the two preoperties with exact name matches to migrate their data.</figcaption>
</figure>

<figure>
    <img src="static/img/CoreRedirectWithMatchSubstring.jpg" alt="CoreRedirectWithMatchSubstring" />
    <figcaption>`PropertyRedirects=(OldName="TestInt",NewName="TestInteger",MatchSubstring=true)` causes all four of our properties to migrate, due to substring matching.</figcaption>
</figure>

> [!NOTE]
> Because `MatchSubtring` requires checking incoming Assets much more thoroughly, it can impact startup times. `MatchSubstring` is intended to be used temporarily as a fixup when making sweeping changes. It is recommended that Assets involved in these changes be resaved immediately and checked into your project's source control database with any related code changes, and that the Core Redirect be deleted without entering source control.

### Compiling a plugin for a new engine version

When you find a plugin and trying to install it, you might find out that it doesn't support your current engine version.
And the Unreal's marketplace won't let you download unless you have a version associated.

One trick to avoid this, is to build the plugin manually and fixing compiling issues (header file missing or API changes). By installing the plugin with the access of the source code. Then by access the plugin with the UHT (Unreal Build Tool), you can then rebuild the plugin into a different engine version.

Here is `.bat` file (Windows Only) to locate the current engine directory, and compile your custom made plugin into another engine version:

```
@echo off

:: Setting up config variables
set EngineVersion=<EngineVersion>
set PluginName=<PluginName>
set InputDirectory=<InputDirectory>
set OutputDirectory=<OutputDirectory>
set TargetPlatforms=Win64

set PluginPath="%cd%\%InputDirectory%\%PluginName%\%PluginName%.uplugin"
set OutputPath="%cd%\%OutputDirectory%\%EngineVersion%\%PluginName%"

:: Locating a registry key, in order to find Unreal Engine source location

for /f "skip=2 tokens=2*" %%a in ('reg query "HKEY_LOCAL_MACHINE\SOFTWARE\EpicGames\Unreal Engine\%EngineVersion%" /v "InstalledDirectory"') do set "EngineDirectory=%%b"

set AutomationToolPath="%EngineDirectory%\Engine\Build\BatchFiles\RunUAT.bat"

title Build Plugin
echo Automation Tool Path: "%AutomationToolPath%"
echo:

call %AutomationToolPath% BuildPlugin -Plugin=%PluginPath% -Package=%OutputPath% -Rocket -TargetPlatforms=%TargetPlatforms%
echo:
pause
exit 0
```

And here is the bash file (Linux Only) version:

```
#!/bin/bash

# Setting up config variables
EngineVersion="<EngineVersion>"
PluginName="<PluginName>"
InputDirectory="<InputDirectory>"
OutputDirectory="<OutputDirectory>"
TargetPlatforms="Win64"

PluginPath="$PWD/$InputDirectory/$PluginName/$PluginName.uplugin"
OutputPath="$PWD/$OutputDirectory/$EngineVersion/$PluginName"

# Locating a registry key, in order to find Unreal Engine source location
EngineDirectory=$(reg query "HKEY_LOCAL_MACHINE\SOFTWARE\EpicGames\Unreal Engine\$EngineVersion" -v "InstalledDirectory" | awk 'NR==3{print $NF}')

AutomationToolPath="$EngineDirectory/Engine/Build/BatchFiles/RunUAT.bat"

echo "Automation Tool Path: \"$AutomationToolPath\""
echo

$AutomationToolPath BuildPlugin -Plugin="$PluginPath" -Package="$OutputPath" -Rocket -TargetPlatforms="$TargetPlatforms"

echo
read -p "Press Enter to continue..."
exit 0
```

### Gameplay Timers

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

### Sampling a curve

Sometimes, you probably want to work with a curve. To access a curve inside C++, you can use `UCurveFloat` class. This class gives you access to interpolated points to evaluate over a given range.

You can create them from the **Content Browser** through **Miscellaneous → Curve**.

<table><tr><td>

Module: `Engine`

Header file:

```cpp
#include "Curves/CurveFloat.h"
```

</td></tr></table>

```cpp
// .h

UPROPERTY(EditAnywhere)
UCurveFloat TimeCycle;

UPROPERTY(EditAnywhere, meta = (ClampMin = 0.0, ClampMax = 1.0))
float TimeOfDay = 0.5f; // Range between 0 -> 1
```

```cpp
// .cpp

// This will be our output value from the curve
float SunIntensity = 0.0f;

// Check if the curve is valid before accessing it.
// Otherwise, if curve is a nullptr, a crash will happen.
if (IsValid(TimeCycle))
{
    // We read the curve at the current level, and assign the value to MaxHP
    SunIntensity = TimeCycle->GetFloatValue(TimeOfDay);
}
```

You can read more about [curves on Unreal's docs](https://docs.unrealengine.com/5.3/en-US/API/Runtime/Engine/Curves/UCurveFloat/).

### HTTP requests

<table><tr><td>

Module: `HTTP`

Header file:

```cpp
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "PlatformHttp.h"
#include "JsonObjectConverter.h" // Include this, if you want to send some JSON data into the request
```

</td></tr></table>

```cpp
// .h

UENUM(BlueprintType)
enum class EHTTPRequestType : uint8
{
    GET,
    POST,
    PUT,
    DELETE
};

// Delegate for the callback
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FHTTPRequest, const FString&, Result, int32 ResponseCode, bool, bWasSuccessful);

UFUNCTION(BlueprintCallable, Category = "MyPawn")
/**
* Send a request via HTTP protocol system.
*
* @param BaseURL - Base URL on which to process the request on.
* @param EndpointURL - Endpoint URL. Combined with base URL to get fully qualified URL for the request.
* @param RequestType - What type of request (GET, POST, PUT, DELETE)
* @param Callback - Callback of the request
* @return A boolean, if the request was successfully sent out.
*/
bool SendRequest(
    const FString BaseURL,
    const FString EndpointURL,
    const EHTTPRequestType RequestType,
    FString Payload,
    FHTTPRequest Callback
);
```

```cpp
// .cpp

bool YourClass::SendRequest(
	const FString BaseURL,
	const FString EndpointURL,
	const EHTTPRequestType RequestType,
	FString Payload,
	FHTTPRequest Callback)
{
    // Get a reference to the HTTP singleton and create a request object
    const FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

    // Creates a lambda function and stores to a variable.
    auto LambdaFunc = [this, Callback](FHttpRequestPtr Req, FHttpResponsePtr Res, bool bWasSuccessful)
    {
        FString Result;

        // Check the status code
        const int32 ResCode = Res->GetResponseCode();

        if (!bWasSuccessful || ResCode < 100 || ResCode > 300)
        {
            // Only accepting 200 -> 299 response code
            Callback.ExecuteIfBound(Result, ResCode, false);
            return;
        }

        Result = Res->GetContentAsString();

        Callback.ExecuteIfBound(Result, ResCode, true);
    };

    // Bind the lambda as the callback
    Request->OnProcessRequestComplete().BindLambda(LambdaFunc);

    Request->SetURL(BaseURL + EndpointURL);
    Request->SetVerb(UEnum::GetDisplayValueAsText(RequestType).ToString());

    switch (RequestType)
    {
        case EHTTPRequestType::POST:
        case EHTTPRequestType::PUT:
        case EHTTPRequestType::DELETE:
        {
            // To send data into the request, you must include this header
            // Which tells the request to expect a JSON data type
            Request->SetHeader("Content-Type", "application/json");

            // Payload is in JSON format. Use JsonObjectConverter to convert Unreal's data type into JSON format.
            Request->SetContentAsString(Payload);
        }
        break;
    }

    // Returns true if the HTTP request has started. Does NOT return the result of the callback lambda.
    return Request->ProcessRequest();
}
```

Then you can call `SendRequest()` function:

```cpp
void YourClass::SendTestRequest()
{
    // Final URL: BASE_URL + ENDPOINT_URL = "https://swapi.dev/api/planets/3/"
    // Helpful to split the endpoint, as you can switch to another endpoint.
    const FString BASE_URL = "https://swapi.dev/api/";
    const FString ENDPOINT_URL = "planets/3/"; // "starships/9/", "people/1/"

    FString JSON;
    FHTTPRequest Delegate;
    Delegate.BindDynamic(this, &YourClass::OnRequestCompleted);

    // Send the request with delegate passed into the parameters
    SendRequest(BASE_URL, ENDPOINT_URL, EHTTPRequestType::GET, "", Delegate);
}

void YourClass::OnRequestCompleted(const FString& Result, bool bWasSuccessful)
{
    if (!bWasSuccessful)
    {
        UE_LOGFMT(LogTemp, Log, "The Request was not successful!");
        return;
    }

    UE_LOGFMT(LogTemp, Log, "Request Output: {0}", Result);
}
```

> [!TIP]
> You can test out HTTP request via [Postman](https://www.postman.com/) with [Star Wars API](https://swapi.dev/) example.

You can read more about [HTTP module on Unreal's docs](https://docs.unrealengine.com/5.3/en-US/API/Runtime/HTTP/FHttpModule/).

### Encryption and Decryption

When working with encryption and decryption.

```cpp
// .h

// Encrypts Int32 using a 10 digit Alpha-Numeric Key into an FString
UFUNCTION(BlueprintCallable, Category = "Encryption")
static FString EncryptInt32(int32 InInt, FString EncryptionKey);

// Decrypts an encrypted FString back to Int32 using a 10 digit Alpha-Numeric Key
UFUNCTION(BlueprintCallable, Category = "Encryption")
static int32 DecryptToInt32(FString EncryptedValue, FString EncryptionKey);
```

```cpp
// .cpp

#include "Kismet/KismetStringLibrary.h"

FString YourClass::EncryptString(FString Data, FString EncryptionKey)
{
    FString EncryptedValue;

    TArray<TCHAR> ValueChars = Data.GetCharArray();
    TArray<TCHAR> KeyChars = EncryptionKey.GetCharArray();

    for (int32 i = 0; i < ValueChars.Num() -1; i++)
    {
        FString TempString;
        TempString.AppendChar(ValueChars[i]);
        EncryptedValue.AppendChar(KeyChars[UKismetStringLibrary::Conv_StringToInt(TempString)]);
    }

    return EncryptedValue;
}

FString YourClass::DecryptToString(FString EncryptedValue, FString EncryptionKey)
{
    TArray<TCHAR> ValueChars = EncryptedValue.GetCharArray();
    TArray<TCHAR> KeyChars = EncryptionKey.GetCharArray();

    FString OutString;

    for (int32 i = 0; i < ValueChars.Num() -1; i++)
    {
        OutString = (OutInt * 10) + KeyChars.Find(ValueChars[i]);
    }

    return OutString;
}
```

### 🐣 Tips and best practices

<table><tr><td>
This section was written in conjunction with ChatGPT.
</td></tr></table>

### Disable BlueprintPure

When creating a `UFUNCTION` and marking it as `const`, Unreal will interpret this function as pure function. A pure function will evaluate every time it's called (inside Blueprint), compare to a regular function, which Unreal caches the result and save for later.

Pure function are helpful for small or quick function to execute. For an example: **getters**.

With Blueprint, every time you drag a pin from the result, the function will be evaluated every single time. And the result may differ at different execution time.

This is not the same, as a regular function. With regular function, Blueprint will then cache the result. And when dragging multiple pins from the result of the function, the same value will be used.

If you want to mark a `UFUNCTION` as const without Unreal converting into a pure function, you can add this specifier:

```cpp
UFUNCTION(BlueprintCallable, BlueprintPure = false)
void ComplexFunction() const
{
    // Expensive calculations
}
```

### Switch case fall-through

When working with switch case, one benefits it's to have fall-through cases. Where, a case can fall under multiple cases and same performance.

Although, it may be harder to read and understand this code, then doing with if-statements.

```cpp
double DistanceUnificationFactor(EUnit From)
{
    // Convert to meters
    double Factor = 1;

    switch (From)
    {
        case EUnit::Micrometers:		return 0.000001;
        case EUnit::Millimeters:		return 0.001;
        case EUnit::Centimeters:		return 0.01;
        case EUnit::Kilometers:			return 1000;

        case EUnit::Lightyears:			return 9.4605284e15;

        case EUnit::Miles:				Factor *= 1760;				// fallthrough
        case EUnit::Yards:				Factor *= 3;				// fallthrough
        case EUnit::Feet:				Factor *= 12;				// fallthrough
        case EUnit::Inches:				Factor /= 39.3700787;		// fallthrough
        default: 						return Factor;				// return
    }
}
```

#### 📦 Refactoring

Refactoring is the process of making changes to the codebase to improve its structure, readability, and maintainability without changing its external behavior.

Refactoring is an essential practice in software development that helps keep the codebase clean, maintainable, and scalable. It involves making incremental improvements to the code without changing its external behavior, which is crucial for maintaining a healthy and sustainable codebase throughout the software development lifecycle.

##### Renaming

Renaming members, such as variables, functions, or classes, is a common refactoring technique used to give them more meaningful and descriptive names, making the code easier to understand and maintain.

Example:

```cpp
// Note, this is regular raw C++ code.

// Before refactoring
class Rectangle
{
private:
    int w; // Width
    int h; // Height

public:
    Rectangle(int width, int height) : w(width), h(height) {}

    int area() { return w * h; }
};

// After refactoring
class Rectangle
{
private:
    int width; // Descriptive name for width
    int height; // Descriptive name for height

public:
    Rectangle(int width, int height) : width(width), height(height) {}

    int area() { return width * height; }
};
```

##### Extract Method

Extract Method is a refactoring technique where you take a portion of code within a method and move it into a separate method. This helps improve code readability, encourages code reuse, and simplifies complex methods.

Example:

```cpp
// Note, this is regular raw C++ code.

// Before refactoring
void printFullName(std::string firstName, std::string lastName)
{
    std::cout << "Full Name: " << firstName << " " << lastName << std::endl;
    // Some other logic related to printing the full name
}

// After refactoring
void printFullName(std::string firstName, std::string lastName)
{
    print("Full Name: " + firstName + " " + lastName);
}

void print(const std::string& message)
{
    std::cout << message << std::endl;
}
```

##### Introduce/Inline typedef﻿s

Introducing a typedef can make complex type names more concise and easier to understand. On the other hand, inline typedefs are useful for reducing the complexity of code and improving code readability by avoiding unnecessary type aliases.

Example:

```cpp
// Note, this is regular raw C++ code.

// Before refactoring
typedef std::map<std::string, std::vector<int>> NameToNumbersMap;

NameToNumbersMap numbers;

// After refactoring (Introduce typedef)
using NumbersVector = std::vector<int>;
using NameToNumbersMap = std::map<std::string, NumbersVector>;

NameToNumbersMap numbers;

// After refactoring (Inline typedef)
std::map<std::string, std::vector<int>> numbers;
```

##### Introduce Variable

Introducing a variable can simplify complex expressions or improve code readability by giving meaningful names to intermediate results.

Example:

```cpp
// Note, this is regular raw C++ code.

// Before refactoring
int total = (price + tax) * quantity - discount + shippingCost;

// After refactoring
int netPrice = price + tax;
int totalPrice = netPrice * quantity - discount + shippingCost;
```

##### Invert 'if' statement to reduce nesting

Consider the following code snippet:

```cpp
void MyCharacter::DoSomething()
{
    if (bIsReadyToMove)
    {
        if (!bIsMoving)
        {
            MoveCharacter();
        }
        else
        {
            // Handle already moving
        }
    }
    else
    {
        // Handle not ready to move
    }
}
```

As you can see, the `if` blocks encompass the whole body of the method. This presents an opportunity to make code more readable by getting rid of the nested scope and adding `return` keyword[^1] as follows:

```cpp
void MyCharacter::DoSomething()
{
    if (!bIsReadyToMove)
    {
        // Handle not ready to move
        return;
    }

    if (!bIsMoving)
    {
        MoveCharacter();
    }
    else
    {
        // Handle already moving
    }
}
```

Here is a video explaining some of the best practices with Unreal Engine and C++.

There is a video about some of these best practices called [Best Practices (2019-2021) from Stephen Maloney](https://www.youtube.com/watch?v=g7WVBZZTRDk)

In the video, there is also a [Google documentation](https://docs.google.com/document/d/1kIgOM7VONlPtx3WPiKdNVRYquX-GTduqSw0mU7on5h8) (if video wasn't enough) for more details about some of his tips and tricks.

#### ⏱ Ticking

##### For actors

```cpp
PrimaryActorTick.bCanEverTick = false;
PrimaryActorTick.bStartWithTickEnabled = false;
```

##### For components

```cpp
PrimaryComponentTick.bCanEverTick =  false;
PrimaryComponentTick.bStartWithTickEnabled = false;
```

##### If you have to use tick

-   Set the tick interval to the maximum value you can get away with. Unfortunately this is often per frame for smoothly moving things

```cpp
PrimaryActorTick.TickInterval = 0.2f;
PrimaryComponentTick.TickInterval = 0.2f;
```

-   Enable/disable tick to only tick when required.

```cpp
SetActorTickEnabled()
SetComponentTickEnabled()
```

#### `FTickFunction`

Abstract base class for all tick functions.

Sample code to get started:

##### MyTickableThing.h

```cpp
#pragma once

#include "CoreMinimal.h"
#include "Tickable.h"

class FMyTickableThing : public FTickableGameObject
{
public:
    // FTickableGameObject Begin
    void Tick( float DeltaTime ) override;

    ETickableTickType GetTickableTickType() const override
    {
        return ETickableTickType::Always;
    }

    TStatId GetStatId() const override
    {
        RETURN_QUICK_DECLARE_CYCLE_STAT( FMyTickableThing, STATGROUP_Tickables );
    }

    bool IsTickableWhenPaused() const
    {
        return true;
    }

    bool IsTickableInEditor() const
    {
        return false;
    }
    // FTickableGameObject End

private:
	// The last frame number we were ticked.
	// We don't want to tick multiple times per frame
	uint32 LastFrameNumberWeTicked = INDEX_NONE;
};
```

##### MyTickableThing.cpp

```cpp
#include "MyTickableThing.h"

void FMyTickableThing::Tick( float DeltaTime )
{
	if ( LastFrameNumberWeTicked == GFrameCounter )
		return;

	// Do our tick
	// ...

	LastFrameNumberWeTicked = GFrameCounter;
}
```

> [!NOTE]
> Tick any object you want, `UObject` or not!

> [!WARNING]
> `USTRUCT` don't support expose functions with UHT[^2].

#### 🔌 Direct references

<table><tr><td>
This section was written in conjunction with ChatGPT.
</td></tr></table>

In C++, a direct reference is a reference variable that directly refers to the memory location of another variable. When you use a direct reference, you are essentially creating an alias or an alternative name for the original variable. This means any changes made to the reference will be reflected in the original variable, and vice versa.

Using direct references can be beneficial for performance in certain situations because it avoids creating unnecessary copies of data. When you pass large objects or structures as function arguments, using direct references instead of passing by value (copy) can save memory and processing time, especially for complex objects.

Using the `const` qualifier in a direct reference serves as a safety mechanism to prevent accidental modifications to the referenced variable. When you declare a variable as const, it means that its value cannot be changed after initialization.

In some cases, using `const` in direct references can also enable certain compiler optimizations, as it provides additional information to the compiler about the immutability of the referenced value.

```cpp
// Note, this is regular raw C++ code.

int a = 5;
int b = a; // Gets a copy

b = b * 2; // B = 10 and A = 5

int& c = 10;
int& d = c;

d = 20; // C = 20 and D = C, which is 20

const int& e = 10; // Direct reference (use const for stopping ability to modify the variable)
const int& f = e;

f = 11; // COMPILER ERROR!!! Cannot modify const variable!!
```

<!-- prettier-ignore-end -->

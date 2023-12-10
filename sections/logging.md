## 📜 Logging

<table><tr><td>
This section was NOT written in conjunction with ChatGPT.
</td></tr></table>

All logs will be saved at: `YourProjectName\Saved\Logs`.

In order to view the log history inside the editor, you can access the window via: `Window -> Developer Tools -> Output Log`.

You can also access the log history via console command, by typing: `showlog` into the console.

To log to the console with C++ in Unreal Engine, you can use `UE_LOG()` macro. This macro takes in a couple of arguments.

1. Log Category
2. Log Verbosity
3. The actual text to log to the console

<table><tr><td>

## Predefined log categories

* `LogPath`
* `LogController`
* `LogPhysics`
* `LogBlueprint`
* `LogBlueprintUserMessages`
* `LogAnimation`
* `LogRootMotion`
* `LogLevel`
* `LogSkeletalMesh`
* `LogStaticMesh`
* `LogNet`
* `LogRep`
* `LogNetPlayerMovement`
* `LogNetTraffic`
* `LogRepTraffic`
* `LogNetFastTArray`
* `LogNetDormancy`
* `LogSkeletalControl`
* `LogSubtitle`
* `LogTexture`
* `LogPlayerManagement`
* `LogSecurity`
* `LogEngineSessionManager`
* `LogHAL`
* `LogSerialization`
* `LogUnrealMath`
* `LogUnrealMatrix`
* `LogContentComparisonCommandlet`
* `LogNetPackageMap`
* `LogNetSerialization`
* `LogMemory`
* `LogProfilingDebugging`
* `LogCore`
* `LogOutputDevice`
* `LogSHA`
* `LogStats`
* `LogStreaming`
* `LogInit`
* `LogExit`
* `LogExec`
* `LogScript`
* `LogLocalization`
* `LogLongPackageNames`
* `LogProcess`
* `LogLoad`
* `LogTemp`

</td></tr></table>

The most common log category, that you will probably use, is `LogTemp` and `LogBlueprintUserMessages` for Blueprint messages.

You can also define your own log category, by using the `DECLARE_LOG_CATEGORY_EXTERN()` and `DEFINE_LOG_CATEGORY()` macros.

Inside you header file, you can write:

```cpp
// .h

// Arguments:
// 1. Name of your custom category. You can use LogTemp if you don't want to define a category.
// 2. Default verbosity when one is not specified. The most common value is Log.
// Valid verbosity levels are: Fatal, Error, Warning, Display, Log, Verbose, VeryVerbose
// 3. Maximum verbosity level to allow when compiling. Can also be All
DECLARE_LOG_CATEGORY_EXTERN(MyLogCategory, Log, All);
```

Then inside the source file, you can write:

```cpp
// .cpp

// Define the log category
DEFINE_LOG_CATEGORY(MyLogCategory);
```

Now you can reuse the log category, via including the header file.

Here is the list of types of verbosity levels:

| Verbosity Level | Printed in Console ? | Printed in Editor's Log? |                      Notes                       |
| ----------------- | --------------------- | -------------------------- | -------------------------------------------------- |
| Fatal | Yes | N / A | Crashes the session, even if logging is disabled |
| Error | Yes | Yes | Log text is coloured red                         |
| Warning | Yes | Yes | Log text is coloured yellow                      |
| Display | Yes | Yes | Log text is coloured grey                        |
| Log | No | Yes | Log text is coloured grey                        |
| Verbose | No | No                       |                                                  |
| VeryVerbose | No | No                       |                                                  |

You can also override some of the pre-existing verbosity levels. These settings can be set in either `Engine.ini` or `DefaultEngine.ini`.

Here's an example of verbosity settings:

```dosini
[Core.Log]
Global=<Category>=<DesiredVerbosityLevel>
```

**Here's a couple of examples:**

Log to the console with a simple string:

```cpp
UE_LOG(LogTemp, Warning, TEXT("Hello"));
```

Similar to `sprintf()` function in C++, where you can use specific different arguments into the string formatter. There are a couple of arguments type, that you need to know about.

<table><tr><td>

* `%s` - strings
* `%d` or `%i` - integers and booleans
* `%f` - floating point numbers (float and double)

</td></tr></table>

How to log to the console with `FString` as an argument:

```cpp
UE_LOG(LogTemp, Warning, TEXT("The Actor's name is: %s"), *YourActor->GetName());
```

> [!TIP]
> You can use `__func__`, `__FUNCTION__` or `__PRETTY_FUNCTION__` to get the name of the function and print it out in the log. However, to add this string, you must convert it into a TCHAR pointer. By using `ANSI_TO_TCHAR()` macro.

Sadly, `UE_LOG` does **NOT** support `bool` data type.

In order to print a boolean with `UE_LOG`, you can use `%i` or `%d` to convert a `bool` (boolean) into a `int32` (integer).

Log to the console with `bool` as an argument:

```cpp
bool bMyBoolean = true;

// You can either use %d or %i. Both will print an integer.
UE_LOG(LogTemp, Log, TEXT("The boolean value is: %i"), bMyBoolean); // The boolean value is: 1

// True -> 1
// False -> 0
```

You can also just convert the boolean into a string as well:

```cpp
bool bMyBoolean = false;

UE_LOG(LogTemp, Log, TEXT("The boolean value is: %s"), (bMyBoolean ? TEXT("true") : TEXT("false"))); // The boolean value is: false
```

Log to the console with `int32` as an argument:

```cpp
int32 MyInteger = 1337;
UE_LOG(LogTemp, Log, TEXT("The integer value is: %d"), MyInteger); // The integer value is: 1337
```

Log to the console with `float` as an argument:

```cpp
float MyFloat = 99.999999f;
UE_LOG(LogTemp, Log, TEXT("The float value is: %f"), MyFloat); // The float value is: 99.999999
```

Log to the console with `double` as an argument:

```cpp
double MyDouble = 3.1415926535897931;
UE_LOG(LogTemp, Log, TEXT("The double value is: %f"), MyDouble); // The double value is: 3.1415926535897931
```

Log to the console with `FVector` as an argument:

```cpp
FVector MyVector = FVector::OneVector;

// In order to log a FVector, you need to convert into a string.
UE_LOG(LogTemp, Log, TEXT("The vector value is: %s"), *MyVector.ToString()); // The vector value is: (1, 1, 1)
```

Log to the console with `FName` as an argument:

```cpp
// In order to log a FName, you need to convert into a string.
UE_LOG(LogTemp, Log, TEXT("The name is: %s"), *MyCharacter->GetFName().ToString());
```

You can also alter the decimal point, when printing floating point numbers.

This can help for readability’s sake.

Using `.2` will specify 2 digits after the decimal point.

Here's an example:

```cpp
double MyDouble = 3.1415926535897931;
UE_LOG(LogTemp, Log, TEXT("The double value is: %.2f"), MyDouble); // The double value is: 3.14
UE_LOG(LogTemp, Log, TEXT("The double value is: %.0f"), MyDouble); // The double value is: 3
UE_LOG(LogTemp, Log, TEXT("The double value is: %,2f"), MyDouble); // The double value is: 3,14
```

### UE_LOGFMT

<table><tr><td>

* UE_LOG is extremely verbose, requiring the developer to constantly wrap log text in the `TEXT` macro.
* UE_LOG is also incapable of printing basic types, such as `bool`, or `FStrings`, Unreal's standard String type.
* UE_LOG requires awareness of types when printing different variables such as float, integer, booleans, strings.

</td></tr></table>

In Unreal Engine 5.2, you can use `UE_LOGFMT()` macro instead! The new `UE_LOGFMT()` macro allows to alleviate many of these issues.

Here's an example of using it:

Include the header file:

```cpp
#include "Logging/StructuredLog.h"
```

Then to log to the console, just write:

```cpp
UE_LOGFMT(LogTemp, Log, "This message will print to my log");
```

And to add some arguments, you can write:

```cpp
FString Name("SomeName");
int32 Value = 999;

UE_LOGFMT(LogTemp, Log, "Printing my Name: {0} with Value: {1}", Name, Value); // Printing my Name: SomeName with Value: 999
```

Here's a couple of examples:

```cpp
UE_LOGFMT(LogCore, Warning, "Loading '{0}' failed with error {1}", Package->GetName(), ErrorCode);
```

```cpp
UE_LOGFMT(LogCore, Warning, "Loading '{Name}' failed with error {Error}", ("Error", ErrorCode), ("Name", Package->GetName()), ("Flags", LoadFlags));
```

> [!NOTE]
> `FText` is not supported with `UE_LOGFMT()`, in order to use `FText` you need to convert into `FString` by simply calling `ToString()` function.

### Log to game-view

Currently, we have only logged to the console. In order to display the console messages inside the game-view, we need to call `AddOnScreenDebugMessage()` function instead. You can access this function inside the global engine variable (`GEngine`).

Here's an example:

```cpp
/*

    void AddOnScreenDebugMessage
    (
        uint64 Key, // A unique key to prevent the same message from being added multiple times.
        float TimeToDisplay, // How long to display the message, in seconds.
        FColor DisplayColor, // The color to display the text in.
        const FString & DebugMessage, // The message to display.
        bool bNewerOnTop,
        const FVector2D & TextScale
    )

    Add a FString to the On-screen debug message system. bNewerOnTop only works with Key == INDEX_NONE
    This function will add a debug message to the onscreen message list. It will be displayed for FrameCount frames.

*/

GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, TEXT("This message will appear on the screen!"));
```

And to provide arguments to this function, you need to use `FString::Printf()`, which is similar to `sprintf()` function and `UE_LOG()` macro.

Here's an example, how to use `FString::Printf()` function `AddOnScreenDebugMessage()` function:

```cpp
GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Some variable values: x = %f, y = %f"), x, y));
```

## 🏛️ Libraries

<table><tr><td>
This section was written in conjunction with ChatGPT.
</td></tr></table>

Blueprint Function Libraries (`UBlueprintFunctionLibrary`) are a collection of static functions that provide utility functionality not tied to a particular gameplay object. These libraries can be grouped into logical function sets, e.g. AI Blueprint Library, or contain utility functions that provide access to many different functional areas, e.g. System Blueprint Library.

```cpp
UCLASS()
class UAnalyticsBlueprintLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_UCLASS_BODY()

public:
    /** Starts an analytics session without any custom attributes specified */
    UFUNCTION(BlueprintCallable, Category = "Analytics")
    static bool StartSession();
}
```

As you can see in the example above, a Blueprint Function Library is indirectly a `UObject` derived and therefore requires the standard `UCLASS()` and `GENERATED_UCLASS_BODY()` macros[^4]. It decorates the functions that are to be callable from Blueprints with the `UFUNCTION()` macro[^4]. Functions in a Blueprint Function Library can be designated as BlueprintCallable or BlueprintPure depending on whether the calls have side effects or not.

Below is the implementation of the `StartSession()` function:

```cpp
bool UAnalyticsBlueprintLibrary::StartSession()
{
    TSharedPtr<IAnalyticsProvider> Provider = FAnalytics::Get().GetDefaultConfiguredProvider();

    if (Provider.IsValid())
        return Provider->StartSession();
    else
    {
        UE_LOG(
            LogAnalyticsBPLib,
            Warning,
            TEXT("StartSession: Failed to get the default analytics provider. Double check your [Analytics] configuration in your INI")
        );
    }

    return false;
}
```

You can read more about [Blueprint Function Libraries here](https://docs.unrealengine.com/5.2/en-US/blueprint-function-libraries-in-unreal-engine/)!

### Kismet Library

* `UGameplayStatics` - `gameplay` utility functions that can be called from both Blueprint and C++
* `UKismetMathLibrary` - `math` utility functions that can be called from both Blueprint and C++
* `UKismetStringLibrary` - `string` utility functions that can be called from both Blueprint and C++
* `UKismetTextLibrary` - `text` utility functions that can be called from both Blueprint and C++
* `UKismetSystemLibrary` - `system` utility functions that can be called from both Blueprint and C++
* `UKismetMaterialLibrary` - `material` utility functions that can be called from both Blueprint and C++
* `UKismetInputLibrary` - `input` utility functions that can be called from both Blueprint and C++
* `UKismetGuidLibrary` - `guid` utility functions that can be called from both Blueprint and C++
* `UKismetArrayLibrary` - `array` utility functions that can be called from both Blueprint and C++

### Misc Library

* `FMath` - Math helper functions (Check `GenericPlatformMath.h` for additional math functions).
* `DrawDebugHelpers.h` - Header file contain debug draw functions. Read more about [here](https://unrealcpp.com/draw-debug-helpers/).

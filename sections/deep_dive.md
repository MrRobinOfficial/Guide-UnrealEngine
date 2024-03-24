<!-- prettier-ignore-start -->

## 🗝️ Deep dive

<table><tr><td>
This section was written in conjunction with ChatGPT.
</td></tr></table>

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

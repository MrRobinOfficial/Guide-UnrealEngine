## 📝 Preprocessor

<table><tr><td>
This section was written in conjunction with ChatGPT.
</td></tr></table>

In programming languages, including C++, the preprocessor is a component of the compiler that performs text manipulation before the actual compilation process. It operates on the source code and handles directives starting with a hash symbol <kbd>#</kbd>.

In C++, the preprocessor handles tasks such as macro expansion, file inclusion, and conditional compilation. It modifies the source code based on these directives before the code is compiled into machine-readable instructions.

The preprocessor can be used to define macros, which are text replacements performed by the preprocessor before the compilation stage. Macros[^4] allow for code reuse, conditional compilation, and other preprocessing operations. Directives like `#include` are used to include header files, and conditional directives like `#ifdef`, `#ifndef`, `#if`, and `#endif` are used for conditional compilation based on certain conditions.

You can read more about [Preprocessor from cppreference.com](https://en.cppreference.com/w/cpp/preprocessor).

You can also watch a video called [Preprocessor Directives" by NeuralNine](https://www.youtube.com/watch?v=voGGB5TGsV4).

### Pragma once

`#pragma once` is a preprocessor directive used in C++ header files to ensure that the header is included only once during the compilation of a source file, regardless of how many times it is referenced.

It is an alternative to traditional header guards, which involve using #ifndef and #define statements to prevent multiple inclusions.
`#pragma once` is a simpler and more efficient way to achieve the same effect, and is supported by most modern compilers.

Here is an example:

```cpp
#pragma once

#include "Vehicle.generated.h"

UINTERFACE(BlueprintType)
class COMMONVEHICLE_API UVehicle : public UInterface
{
    GENERATED_UINTERFACE_BODY()
};

class COMMONVEHICLE_API IVehicle
{
    GENERATED_IINTERFACE_BODY()
    // ...
};
```

### Strip out editor functionality

Using preprocessor directives to strip out editor functionality in Unreal Engine with C++ is a good habit, because it allows for efficient compilation and reduces the size of the final executable by excluding code that is specific to the editor but not needed in the final game build.

For an example, in this scenaro.

Here's an example:

```cpp
#if WITH_EDITORONLY_DATA
    UPROPERTY(VisibleAnywhere)
    UArrowComponent* ArrowComponent;
#endif

#if WITH_EDITOR
void SetupArrow()
{
  ArrowComponent->SetArrowColor(FLinearColor::Yellow);
}
#endif
```

In this scenario, `ArrowComponent` is not needed for the final build. Only inside the editor version. Therefore, with the use of preprocessor, we can mark it for stripping. Once Unreal Engine is building/packing the game, the piece of code will be removed.

You can also use `#elif` as `else if` or `#else` as `else`, in order to branch off the stripping processes.

Here is an updated example of this:

```cpp
#if WITH_EDITORONLY_DATA
    UPROPERTY(VisibleAnywhere)
    UArrowComponent* ArrowComponent;
#endif

void SetupArrow()
{
#if WITH_EDITOR
    ArrowComponent->SetArrowColor(FLinearColor::Yellow);
#else
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));
#endif
}

```

You can also used `UE_BUILD_SHIPPING` for negation to isolate debug code, so it wont be compiled in shipping build.

Example:

```cpp
void APlayerCharacter::Kill()
{
#if !UE_BUILD_SHIPPING
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello, World!"));
#endif
}
```

## 📃 Macros

Macros[^4] are preprocessor directives that perform text replacements before the compilation process. They are denoted by the <kbd>#</kbd> symbol and are used to define reusable code snippets, conditionally include or exclude code, and perform other preprocessing operations.

Creating a macro in C++ with Unreal Engine is straightforward. You can use the #define preprocessor directive to define a macro. Here's the basic syntax:

```cpp
#define MACRO_NAME(value) // Macro definition
```

Here's an example of PI macro:

```cpp
#define PI 3.14
#define PI_MULTIPLY(x) 3.14 * x
```

Here is a list of common macros in Unreal Engine:

-   `GENERATED_BODY()` - Boilerplate code required by the engine.

-   `TEXT()` - Used for specifying wide-character (UTF-16) encoding. This makes the string literal for being platform independent. Without this macro, you are using ANSI encoding (which can cause issue on other machines).
-   `TEXTVIEW()` - Calculates the length of a string from a string literal at compile time.
-   `INVTEXT()` - Mark text strings for localization. It stands for "Invariant Text" and is used to specify text that should remain unchanged during the localization process.
-   `LOCTEXT()` - Creating localized text. It stands for "Localized Text" and allows you to define text literals that can be localized for different languages.

-   `IN` and `OUT` - Function parameter decorators. They provide a hint about the intention and direction of data flow. `IN` indicates that the parameter is an input parameter, meaning it provides data to the function. `OUT` indicates that the parameter is an output parameter, meaning the function will modify or provide data through that parameter.

-   `LINE_TERMINATOR` - Represent the line terminator character sequence in Unreal Engine. It provides a platform-independent way of specifying line breaks in text files or strings.

-   `CONSTEXPR` - Declare a constant expression. It is used in conjunction with the `constexpr` keyword[^1] to specify that a function or variable can be evaluated at compile-time and treated as a constant expression.

-   `ABSTRACT` - Declare an abstract class. It indicates that a class cannot be instantiated directly and must be subclassed. An abstract class serves as a base class for other classes and provides a blueprint for their common functionality.

-   `UPROPERTY()` - Defines the type and behavior of the property, as well as its metadata and display names.
-   `UFUNCTION()` - Defines the parameters and return type of the function, as well as its behavior and metadata.
-   `UCLASS()` - Defines the properties and behavior of the class, including its inheritance hierarchy, default properties, and editor metadata.
-   `USTRUCT()` - Defines the properties and behavior of the struct, including its fields, default values, and editor metadata.
-   `UINTERFACE()` - Defines the values of the enumeration, as well as its metadata and display names.
-   `UPARAM()` - Specify additional metadata for function parameters in Unreal Engine. This metadata can be used for a variety of purposes, such as specifying the category or tooltip for the parameter in the editor.
-   `UENUM()` - Define an enumeration that can be used in Unreal Engine classes. This allows developers to define a set of named constants that can be used in a type-safe way.
-   `UMETA()` - Specify additional metadata for enumeration values in Unreal Engine. This metadata can be used for a variety of purposes, such as specifying the display name or tooltip for the value in the editor.

-   `INLINE` - Suggestion to the compiler that a function should be inlined, but the compiler is not required to honor it. (Replacement for `inline` keyword[^1])
-   `FORCEINLINE` - A stronger suggestion that the compiler should inline the function if possible, and it may even produce an error if the function cannot be inlined. (Replacement for `force_inline` keyword[^1])'

-   `UE_LOG` - Outputs the log message into the log file. The first input parameter it takes is the name of the logging category.

-   `check` and `checkf` (**NOT ALLOWED IN BUILDS**) - Halts execution if `Expression` is false. `checkf` outputs `FormattedText` to the log.
-   `verify` and `verifyf` (**ALLOWED IN BUILDS**) - Halts execution if `Expression` is false. `verifyf` outputs `FormattedText` to the log.
-   `ensure` and `ensureMsgf` (**ALLOWED IN BUILDS**) - Notifies the crash reporter on the first time `Expression` is false. `ensureMsgf` outputs `FormattedText` to the log.
-   `ensureAlways` and `ensureAlwaysMsgf` (**ALLOWED IN BUILDS**) - Notifies the crash reporter if Expression is false. `ensureAlwaysMsgf` outputs `FormattedText` to the log.

-   `unimplemented` - Halts execution if the line is ever hit, similar to `check(false)`, but intended for virtual functions that should be overridden and not called.

-   `checkCode` - Executes `Code` within a do-while loop structure that runs once; primarily useful as a way to prepare information that another Check requires.
-   `checkNoEntry` - Halts execution if the line is ever hit, similar to `check(false)`, but intended for code paths that should be unreachable
-   `checkNoReentry` - Halts execution if the line is hit more than once.
-   `checkNoRecursion` - Halts execution if the line is hit more than once without leaving scope.

What are inlined functions?

> When a function is inlined, the compiler replaces the function call with the actual code of the function, as if the code had been written directly in place of the call.
>
> This can improve performance by eliminating the overhead of a function call, but it can also increase the size of the executable.

Difference between a macro and function then?

> While both macros[^4] and `FORCEINLINE` functions can be used to improve performance and reduce code repetition, `FORCEINLINE` functions are generally preferred over macros[^4] in Unreal Engine, as they offer type safety, scoping and visibility rules, and better debugging support.

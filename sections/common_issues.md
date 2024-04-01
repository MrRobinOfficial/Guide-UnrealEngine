## ⚠️ Common Issues

<!-- TODO: Add more errors examples -->

<table><tr><td>
This section was NOT written in conjunction with ChatGPT.
</td></tr></table>

![Common Errors](static/img/Cpp_Errors.png)

There are different types of errors and issue, that you **WILL** encounter as you get familiar with programming. There are four types of category for defining an error/issue.

-   Syntax - Violations of the programming language's grammar and structure rules. Every language has its own set of rules and guidelines to follow. For an example, the Python language doesn't use semicolons nor the curly braces for defining a code block.

-   Linker - Issues that arise during the linking phase, such as unresolved references or conflicts between modules or libraries. A linker issue can also be very complex and hard to resolve, as it doesn't give a lot of information for you as the developer.

-   Runtime - Errors that occur during program execution and cause the program to crash or behave unexpectedly. A runtime error can be resolved quite quickly, if you have access to crash reporter, which usually contains the [call stack](https://en.wikipedia.org/wiki/Call_stack) (which can pinpoint the exact function or code, which caused the crash).

-   Semantic - Logical errors that occur when the code is syntactically correct but does not behave as intended or expected. A semantic error can be the hardest error to resolve, since you need to understand the code logical rather than syntactically.

The compiler will only give errors for **Syntax** and **Linker** issue. Compile error refers to a state when a [compiler](https://en.wikipedia.org/wiki/Compiler) fails to compile. Either due to errors in the code, or, more unusually, due to errors in the compiler itself.

The runtime errors can be resolved with a [crash reporter](https://en.wikipedia.org/wiki/Crash_reporter). And semantic errors can be resolved by understanding the logical reasoning of the code.

> [!TIP]
> If you feel stuck or can't think straight, then take a couple of minutes or even hours to do something else. Either is going outside, playing video games, listening to music or watching a film or a video. This can help you brain and rethink and resolve the issue quicker.

You can find all the compiler errors at [Microsoft website](https://learn.microsoft.com/en-us/cpp/error-messages/compiler-errors-1/compiler-errors-c2000-c3999).

### ⛔ Compiler Errors

Here are the common compilation errors, that you **WILL** encounter:

<!-- Variable not initialized -->
<!-- Incorrect syntax: ; ) } -->
<!-- Different scope -->
<!-- Variable not changing -->
<!-- Requires an instance of a class -->
<!-- Missing namespace -->
<!-- Missing include -->
<!-- Missing defines -->
<!-- Cannot access private members -->
<!-- Cannot convert type -->
<!-- Wrong case -->

#### Compiler Error C2007

**Description**

> No identifier appears after a `#define`. To resolve the error, use an identifier.

The following sample generates C2007:

```cpp
// C2007.cpp

#define   // C2007
```

Possible resolution:

```cpp
// C2007b.cpp

// compile with: /c
#define true 1
```

[Link](https://learn.microsoft.com/en-us/cpp/error-messages/compiler-errors-1/compiler-error-c2007) to error message.

#### Compiler Error C2065

**Description**

> The compiler doesn't recognize the identifier and, therefore, considers it undeclared. The compiler needs to be aware of the existence of identifiers before they can be used. By declaring an identifier, you provide the compiler with the necessary information about its name and type, allowing it to properly allocate memory or resolve references.

The following sample generates C2065:

```cpp
// C2065.cpp
#include <iostream>

int main()
{
    std::cout << x; // C2065 error
    return 0;
}
```

Possible resolution:

```cpp
// C2065.cpp
#include <iostream>

int main()
{
    int x = 5; // Declare and initialize the variable x
    std::cout << x;
    return 0;
}
```

[Link](https://learn.microsoft.com/en-us/cpp/error-messages/compiler-errors-1/compiler-error-c2065) to error message.

#### Compiler Error C2628

**Description**

> A semicolon may be missing.

The following sample generates C2628:

```cpp
// C2628.cpp
class CMyClass {} // C2628 error

int main()
{

}
```

Possible resolution:

```cpp
// C2628b.cpp
class CMyClass {};

int main()
{

}
```

[Link](https://learn.microsoft.com/en-us/cpp/error-messages/compiler-errors-2/compiler-error-c2628) to error message.

### 💣 Runtime Errors

A runtime error is a type of error that occurs when a program is being executed. It is a type of error, which is **NOT** detected at compile-time, but at runtime. It means that the code, which is being executed, is causing an error, which is not known until the program is being executed.

Here is a couple of examples, of a runtime error can occur:

```cpp

```

Without a [crash reporter](https://en.wikipedia.org/wiki/Crash_reporter), a runtime error can be extremely difficult to resolve. As the runtime error will lead to a crash and terminate of the application.

If you can't access a **crash reporter** for debugging these errors, then use `Visual Debugger` inside VS Code or Visual Studio. This tool is designed for caching runtime errors and helping you to debug your code. It also features a [call stack](https://en.wikipedia.org/wiki/Call_stack), which can be extremely helpful for these types of problems.

If you can't access the **visual debugger**, then the most **COMMON** and **PAINFULLY** method, would be to add a print message around your code. I do **NOT** recommend this approach, since it takes more time by tracking down the function or line of code, and adding a bunch of print statements. I instead, recommend you to use either a **crash reporter** or a **visual debugger**.

> [!TIP]
> You can also assertions to test your code for failure. But also add message to the failure, which will be picked up by the crash reporter. This will increase understandbility, when a crash might occur. You can read more about assertions in this [section](#-assertions).

For example, if you try to access an index of an array, which is out of bounds, it will cause a runtime error, as the program will try to access a memory location, which is not valid.

### 💀 Semantic Errors

#### 🔍 Overflow issues

There are two main types of overflows:

##### Integer overflow

When you perform an arithmetic operation on an integer, which exceeds the maximum value that the integer can hold, the result will be an overflow.

For an example:

```cpp
int32 MaxValueOfInt32 = 2147483647;

MaxValueOfInt32++; // Will cause an overflow.

// Since an int32 can only store, both negative and positive: 2,14,748,3647.
// If you only care about the positive numbers (ex: health values), then use unsigned numbers instead.
```

The same goes for the negative numbers as well:

```cpp
int32 MinValueOfInt32 = -2147483647;

MinValueOfInt32--; // Will cause an overflow.
```

To solve this overflow issue, either use a bigger data type (`int64`). Or use unsigned data types instead, such as `uint32` or `uint64`.

##### Array overflow

When you try to access an element of an array, which is outside of its bounds, the result will be an overflow. Unreal Engine uses the `TArray` and `TArrayView` types for arrays, and it's important to be aware of their maximum size.

For an example

```cpp
TArray<int32> ActiveYears = { 2020, 2021, 2022 };

int32 Year = ActiveYears[10]; // Will cause an overflow

// Since the index is out of bounds of array's memory block and therefore cannot be accessed.
```

#### 🔍 Scope issues

[Scope](<https://en.wikipedia.org/wiki/Scope_(computer_science)>) refers to the region of code, where a variable is accessible. In C++, a scope is defined by <kbd>{</kbd> and <kbd>}</kbd> ([curly brackets](https://en.wikipedia.org/wiki/Indentation_style#C/C++_styles)).

##### Local scope

A variable is in the local scope, if it's declared inside a function or a class. The variable is only accessible inside that function or class, and not outside of it.

For an example:

```cpp
void KillPlayer(APlayerCharacter* Player)
{
    {
        bool bIsDead = Player->Kill();

        // Able to access it
        if (bIsDead)
        {
            PrintDeath(Player);
        }
    }

    // Compile error! Cannot be accessed outside its defining scope.
    if (bIsDead)
    {

    }
}

// Same goes for this function scope

void PrintDeath(APlayerCharacter* Player)
{
    // Able to access it.
    // Since, it was defined as an argument, when the function was called.
    if (!IsValid(Player))
        return;

    // Compile error! Cannot be accessed inside another function.
    if (bIsDead)
    {

    }
}
```

##### Class scope

A variable is in the class scope, if it's declared inside a class. The variable is only accessible inside that class, and not outside of it.

For an example:

```cpp
UCLASS()
class APlayerCharacter : public ACharacter
{
private:
    int32 Health;

public:
    void Kill()
    {
        Health = 0;
    }
};

void KillPlayer()
{
    Health = 0; // Compile error! Cannot be accessed outside the class scope.
}
```

Here is the fixed version:

```cpp
void KillPlayer(APlayerCharacter* Player)
{
    // Able to access it.
    // Since, the function as defined and have correct access to the current context of scope.
    Player->Kill();

    Player->Health = 0; // Compile error! Cannot be accessed, since it requires a private scope.
    // Meaning, the variable can only be accessed inside class scope.
}
```

##### Global scope

A variable is in the global scope, if it's declared outside of any function or class. The variable is accessible from anywhere in the program.

For an example:

```cpp
int32 GPlayerHealth = 100;

UCLASS()
class AMyActor : public AActor
{
public:
    void DamagePlayer(int32 DamageAmount)
    {
        // Able to access it.
        // Since, the variable is defined in the global scope.
        GPlayerHealth -= DamageAmount;

        if (GPlayerHealth <= 0)
            GPlayerHealth = 0;
    }
};

UCLASS()
class APlayerCharacter : public ACharacter
{
public:
    void Kill()
    {
        // Able to access it.
        // Since, the variable is defined in the global scope.
        GPlayerHealth = 0;
    }
};
```

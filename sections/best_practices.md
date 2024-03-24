## 🐣 Tips and best practices

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

### 📦 Refactoring

Refactoring is the process of making changes to the codebase to improve its structure, readability, and maintainability without changing its external behavior.

Refactoring is an essential practice in software development that helps keep the codebase clean, maintainable, and scalable. It involves making incremental improvements to the code without changing its external behavior, which is crucial for maintaining a healthy and sustainable codebase throughout the software development lifecycle.

#### Renaming

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

#### Extract Method

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

#### Introduce/Inline typedefs

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

#### Introduce Variable

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

### Invert 'if' statement to reduce nesting

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

### ⏱ Ticking

#### For actors

```cpp
PrimaryActorTick.bCanEverTick = false;
PrimaryActorTick.bStartWithTickEnabled = false;
```

#### For components

```cpp
PrimaryComponentTick.bCanEverTick =  false;
PrimaryComponentTick.bStartWithTickEnabled = false;
```

#### If you have to use tick

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

> [!WARNING] > `USTRUCT` don't support expose functions with UHT[^2].

### 🔌 Direct references

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

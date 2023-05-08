# Getting started in Unreal Engine and C++

<p align="center">
  <img src="https://user-images.githubusercontent.com/61658252/236800368-1eb85849-0d4f-4e6e-90bf-3ada5219afc3.png" width="256" height="256">
</p>

**Are you interested in creating games with Unreal Engine using C++?**

*In this repo, we'll guide you through the basics of getting started with Unreal Engine and C++. We'll cover the fundamentals of C++ programming, such as data types and pointers, and show you how to use these concepts in the context of game development with Unreal Engine. We'll also introduce you to the Unreal Engine module system, which is an important aspect of organizing your game code into smaller, more manageable pieces.*

## Getting started with C++

Highly recommend taking a short class of C++. Here is a video link to ~1h long video, [click here](https://www.youtube.com/watch?v=ZzaPdXTrSb8).

Lorem ipsum dolor sit amet, consectetur adipiscing elit. Suspendisse dictum turpis a nisl vestibulum, ac malesuada enim pellentesque. In bibendum suscipit sem, in pulvinar tellus vestibulum vel. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. In at suscipit diam. Sed nec enim luctus, condimentum eros quis, porta felis. Vestibulum dignissim turpis in justo pulvinar dapibus. Phasellus sodales, sem vitae blandit dictum, magna risus viverra sapien, ut malesuada purus arcu ut tellus.

Integer nunc metus, faucibus a luctus a, porta at turpis. Praesent sem felis, cursus vitae nulla nec, tincidunt interdum sem. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Quisque semper auctor ex, quis mollis sapien aliquam sit amet. Interdum et malesuada fames ac ante ipsum primis in faucibus. Sed suscipit dapibus aliquet. Nulla id vestibulum enim. Aenean dui nisi, mollis vitae porttitor at, gravida ac nisl. In sit amet velit lacus. Vivamus feugiat purus faucibus tincidunt pulvinar. Suspendisse fringilla eleifend risus vitae vestibulum. Etiam condimentum maximus ipsum.

## Architecture

Lorem ipsum dolor sit amet, consectetur adipiscing elit. Suspendisse dictum turpis a nisl vestibulum, ac malesuada enim pellentesque. In bibendum suscipit sem, in pulvinar tellus vestibulum vel. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. In at suscipit diam. Sed nec enim luctus, condimentum eros quis, porta felis. Vestibulum dignissim turpis in justo pulvinar dapibus. Phasellus sodales, sem vitae blandit dictum, magna risus viverra sapien, ut malesuada purus arcu ut tellus.

Integer nunc metus, faucibus a luctus a, porta at turpis. Praesent sem felis, cursus vitae nulla nec, tincidunt interdum sem. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Quisque semper auctor ex, quis mollis sapien aliquam sit amet. Interdum et malesuada fames ac ante ipsum primis in faucibus. Sed suscipit dapibus aliquet. Nulla id vestibulum enim. Aenean dui nisi, mollis vitae porttitor at, gravida ac nisl. In sit amet velit lacus. Vivamus feugiat purus faucibus tincidunt pulvinar. Suspendisse fringilla eleifend risus vitae vestibulum. Etiam condimentum maximus ipsum.

## Naming Convention 

Lorem ipsum dolor sit amet, consectetur adipiscing elit. Suspendisse dictum turpis a nisl vestibulum, ac malesuada enim pellentesque. In bibendum suscipit sem, in pulvinar tellus vestibulum vel. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. In at suscipit diam. Sed nec enim luctus, condimentum eros quis, porta felis. Vestibulum dignissim turpis in justo pulvinar dapibus. Phasellus sodales, sem vitae blandit dictum, magna risus viverra sapien, ut malesuada purus arcu ut tellus.

Integer nunc metus, faucibus a luctus a, porta at turpis. Praesent sem felis, cursus vitae nulla nec, tincidunt interdum sem. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Quisque semper auctor ex, quis mollis sapien aliquam sit amet. Interdum et malesuada fames ac ante ipsum primis in faucibus. Sed suscipit dapibus aliquet. Nulla id vestibulum enim. Aenean dui nisi, mollis vitae porttitor at, gravida ac nisl. In sit amet velit lacus. Vivamus feugiat purus faucibus tincidunt pulvinar. Suspendisse fringilla eleifend risus vitae vestibulum. Etiam condimentum maximus ipsum.

## Data Types

We start off with simply variables types, such as boolean, int, float, string and pointers.

### Booleans

```cpp
bool bIsDead = true; // Unreal has prefixed of a 'b' (always lowercase) 

if (bIsDead)
{
  // Do some logic
}
```

### Integers

```cpp
int Health = 10; // Unreal always uses PascalCase naming convention.

if (Health <= 0)
{
  bIsDead = true;
  return;
}
```

**NOTE**: It is generally recommended to use ```int32``` instead of ```int``` for representing 32-bit signed integers. This is because the exact size of ```int``` is not defined by the C++ standard and can vary across different platforms and compilers. By using ```int32```, you can ensure that the size of the integer is consistent regardless of the platform.

So, here is the updated code:

```cpp
int32 Health = 10; // Unreal always uses PascalCase naming convention.

if (Health <= 0)
{
  bIsDead = true;
  return;
}
```

### Floating points (floats and doubles)

```cpp
float SpeedInMetersPerSecond = 5.5f; // C++ always uses 'f' or 'F' literal for defining a float variable.

float SpeedInKph = SpeedInMetersPerSecond * 3.6f;
```

```cpp
double SpeedInMetersPerSecond = 5.5; // C++ never uses a literal for defining a double variable.

double SpeedInKph = SpeedInMetersPerSecond * 3.6;
```

### Modifiers

Lorem ipsum dolor sit amet, consectetur adipiscing elit. Suspendisse dictum turpis a nisl vestibulum, ac malesuada enim pellentesque. In bibendum suscipit sem, in pulvinar tellus vestibulum vel. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. In at suscipit diam. Sed nec enim luctus, condimentum eros quis, porta felis. Vestibulum dignissim turpis in justo pulvinar dapibus. Phasellus sodales, sem vitae blandit dictum, magna risus viverra sapien, ut malesuada purus arcu ut tellus.

```cpp
// Can store postive and negative numbers
signed int32 a = -10;

// Can only store postive numbers
unsigned int32 b = 20;

// Can store 32 bits ()
int32 c = 50;

// Can only store 16 bits ()
short int32 d = 15;

// Can store up to 64 bits ()
long int32 e = 10;
```

### Strings

Strings differs in Unreal Engine and C++.

This is how you would define it in standard C++:

```cpp
std::string Message("Hello, World!"); // This is string in C++ standard library
```

And this is how you define it in Unreal Engine's C++:

```cpp
FString Message = TEXT("Hello, World!"); // Unreal always uses a macro called 'TEXT' to ensure the string is in Unicode characters.
```

You also have other data types for storing string/text. Here is other examples:

```cpp
// Helpful in the editor to localize the text into another language.
FText NewGameText = FText::FromString(TEXT("New Game"));

// Helpful for storing short name string.
// Also, FNames are case-insensitive, and are stored as a combination of an index into a table of unique strings and an instance number.
FName Username = FName(TEXT("mRrObIN"));
```

### Vectors and Quaternions

```cpp
FVector Location = FVector::ZeroVector; // X, Y and Z
FRotator Rotation = FRotator::Identify; // X, Y, Z and W
```

### Classes and structs

Lorem ipsum dolor sit amet, consectetur adipiscing elit. Suspendisse dictum turpis a nisl vestibulum, ac malesuada enim pellentesque. In bibendum suscipit sem, in pulvinar tellus vestibulum vel. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. In at suscipit diam. Sed nec enim luctus, condimentum eros quis, porta felis. Vestibulum dignissim turpis in justo pulvinar dapibus. Phasellus sodales, sem vitae blandit dictum, magna risus viverra sapien, ut malesuada purus arcu ut tellus.

Integer nunc metus, faucibus a luctus a, porta at turpis. Praesent sem felis, cursus vitae nulla nec, tincidunt interdum sem. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Quisque semper auctor ex, quis mollis sapien aliquam sit amet. Interdum et malesuada fames ac ante ipsum primis in faucibus. Sed suscipit dapibus aliquet. Nulla id vestibulum enim. Aenean dui nisi, mollis vitae porttitor at, gravida ac nisl. In sit amet velit lacus. Vivamus feugiat purus faucibus tincidunt pulvinar. Suspendisse fringilla eleifend risus vitae vestibulum. Etiam condimentum maximus ipsum.

### Collections

Lorem ipsum dolor sit amet, consectetur adipiscing elit. Suspendisse dictum turpis a nisl vestibulum, ac malesuada enim pellentesque. In bibendum suscipit sem, in pulvinar tellus vestibulum vel. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. In at suscipit diam. Sed nec enim luctus, condimentum eros quis, porta felis. Vestibulum dignissim turpis in justo pulvinar dapibus. Phasellus sodales, sem vitae blandit dictum, magna risus viverra sapien, ut malesuada purus arcu ut tellus.

Integer nunc metus, faucibus a luctus a, porta at turpis. Praesent sem felis, cursus vitae nulla nec, tincidunt interdum sem. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Quisque semper auctor ex, quis mollis sapien aliquam sit amet. Interdum et malesuada fames ac ante ipsum primis in faucibus. Sed suscipit dapibus aliquet. Nulla id vestibulum enim. Aenean dui nisi, mollis vitae porttitor at, gravida ac nisl. In sit amet velit lacus. Vivamus feugiat purus faucibus tincidunt pulvinar. Suspendisse fringilla eleifend risus vitae vestibulum. Etiam condimentum maximus ipsum.

### Pointers

And lastly, we have pointers. This section, will go over about raw pointers and smart pointers. If you have no clue about pointers, highly recommend watching Cherno video about [pointers](https://www.youtube.com/watch?v=DTxHyVn0ODg).

In a short summary, a pointer is like writing down the address of a building on a piece of paper. The address on the paper tells you where the building is located, just as the memory address stored in the pointer variable tells you where a variable is located in memory. Similarly, you can also pass the address on the paper to someone else, allowing them to find the building too, just as you can pass a pointer variable to a function or another part of your code, allowing it to access the variable in memory.

#### Raw pointers

A raw pointer can be sometime dangerous, because there is no validation when accessing this pointer. And when the pointer is pointing to nothing (meaning, the pointer is a 'nullptr'). The program will throw a null pointer exception, also known as a segmentation fault (segfault).

A segmentation fault occurs when a program tries to access a memory location that it does not have permission to access, which can happen when the program tries to dereference a null pointer. When this happens, the operating system will usually terminate the program and generate an error message.

To avoid this, you must check before if the pointer is valid, before using it.

To do this in Unreal Engine's C++, you would use the function called ```IsValid()``` for raw pointers. Here is an example:

```cpp
UPROPERTY()
AActor* ActorPtr = nullptr;

// Use UPROPERTY() macro, in order to the Unreal compiler, this pointer must be release into GC (garbage collector).
// If not, then this will cause a memory leak. Meaning, the pointer is still alive, even tough we are not using this memory block.

void KillActor()
{
  // IsValid() function also check if the pointer is not already destroyed by the GC (garbage collector).

  if (!IsValid(ActorPtr)) // The pointer has value of 'nullptr', therfore is NOT valid! 
      return;

  ActorPtr->Destroy();
}
```

After Unreal Engine (5.0) version, is now recommend to use ```TObjectPtr``` instead of ```*``` to mark raw pointers. ```TObjectPtr``` contains some optimization for the editor.

Here is the updated code:

```cpp
UPROPERTY()
TObjectPtr<AActor> ActorPtr = nullptr;
```

#### Smart pointers

Smart pointer is used for handling scenario, which a raw pointer does not entirely fit. For most cases, you probably want to go with smart pointers instead.

You can read more about at, [Unreal Smart Pointer Library](https://docs.unrealengine.com/5.1/en-US/smart-pointers-in-unreal-engine/)

You have:

* Weak pointer (```TWeakObjectPtr```)
* Soft pointer (```TSoftObjectPtr```)
* Soft class pointer (```TSoftClassPtr```)
* Shared pointer (```TSharedPtr```)

Lorem ipsum dolor sit amet, consectetur adipiscing elit. Suspendisse dictum turpis a nisl vestibulum, ac malesuada enim pellentesque. In bibendum suscipit sem, in pulvinar tellus vestibulum vel. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. In at suscipit diam. Sed nec enim luctus, condimentum eros quis, porta felis. Vestibulum dignissim turpis in justo pulvinar dapibus. Phasellus sodales, sem vitae blandit dictum, magna risus viverra sapien, ut malesuada purus arcu ut tellus.

### Macros

Lorem ipsum dolor sit amet, consectetur adipiscing elit. Suspendisse dictum turpis a nisl vestibulum, ac malesuada enim pellentesque. In bibendum suscipit sem, in pulvinar tellus vestibulum vel. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. In at suscipit diam. Sed nec enim luctus, condimentum eros quis, porta felis. Vestibulum dignissim turpis in justo pulvinar dapibus. Phasellus sodales, sem vitae blandit dictum, magna risus viverra sapien, ut malesuada purus arcu ut tellus.

Integer nunc metus, faucibus a luctus a, porta at turpis. Praesent sem felis, cursus vitae nulla nec, tincidunt interdum sem. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Quisque semper auctor ex, quis mollis sapien aliquam sit amet. Interdum et malesuada fames ac ante ipsum primis in faucibus. Sed suscipit dapibus aliquet. Nulla id vestibulum enim. Aenean dui nisi, mollis vitae porttitor at, gravida ac nisl. In sit amet velit lacus. Vivamus feugiat purus faucibus tincidunt pulvinar. Suspendisse fringilla eleifend risus vitae vestibulum. Etiam condimentum maximus ipsum.

### Delegates

Lorem ipsum dolor sit amet, consectetur adipiscing elit. Suspendisse dictum turpis a nisl vestibulum, ac malesuada enim pellentesque. In bibendum suscipit sem, in pulvinar tellus vestibulum vel. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. In at suscipit diam. Sed nec enim luctus, condimentum eros quis, porta felis. Vestibulum dignissim turpis in justo pulvinar dapibus. Phasellus sodales, sem vitae blandit dictum, magna risus viverra sapien, ut malesuada purus arcu ut tellus.

Integer nunc metus, faucibus a luctus a, porta at turpis. Praesent sem felis, cursus vitae nulla nec, tincidunt interdum sem. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Quisque semper auctor ex, quis mollis sapien aliquam sit amet. Interdum et malesuada fames ac ante ipsum primis in faucibus. Sed suscipit dapibus aliquet. Nulla id vestibulum enim. Aenean dui nisi, mollis vitae porttitor at, gravida ac nisl. In sit amet velit lacus. Vivamus feugiat purus faucibus tincidunt pulvinar. Suspendisse fringilla eleifend risus vitae vestibulum. Etiam condimentum maximus ipsum.

### Asserts

Lorem ipsum dolor sit amet, consectetur adipiscing elit. Suspendisse dictum turpis a nisl vestibulum, ac malesuada enim pellentesque. In bibendum suscipit sem, in pulvinar tellus vestibulum vel. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. In at suscipit diam. Sed nec enim luctus, condimentum eros quis, porta felis. Vestibulum dignissim turpis in justo pulvinar dapibus. Phasellus sodales, sem vitae blandit dictum, magna risus viverra sapien, ut malesuada purus arcu ut tellus.

Integer nunc metus, faucibus a luctus a, porta at turpis. Praesent sem felis, cursus vitae nulla nec, tincidunt interdum sem. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Quisque semper auctor ex, quis mollis sapien aliquam sit amet. Interdum et malesuada fames ac ante ipsum primis in faucibus. Sed suscipit dapibus aliquet. Nulla id vestibulum enim. Aenean dui nisi, mollis vitae porttitor at, gravida ac nisl. In sit amet velit lacus. Vivamus feugiat purus faucibus tincidunt pulvinar. Suspendisse fringilla eleifend risus vitae vestibulum. Etiam condimentum maximus ipsum.

## Create a module

You can read more about Unreal Engine's modules [here](https://docs.unrealengine.com/5.1/en-US/unreal-engine-modules/)!

In Unreal Engine, a module is a way to organize game code into smaller pieces, similar to Unity's Assembly Definitions. By separating code into modules, you can reduce compile times and keep your code more organized. For example, you could create a module called 'Vehicle' to contain all the code related to the vehicle system. This would allow you to isolate the vehicle code from other parts of the game, such as the inventory system, and make it easier to maintain and update.

**NOTE**: Unreal Engine modules are not related to C++ 20 modules.

Working with modules can also help you stay focused on the specific functionality you're implementing, as you only need to work with the code relevant to that module.

### Module structure

All modules should be placed in the Source directory for either a plugin or project. The module's root folder should have the same name as the corresponding module.

There should also be a [ModuleName].Build.csfile for each module in its root folder, and its C++ code should be contained in Private and Public folders.

![image](https://user-images.githubusercontent.com/61658252/236797649-1acb5aac-ab05-4676-86a4-959e443de404.png)

## Circular Dependency

It's possible to encounter circular dependencies when multiple modules access the same module. This occurs when module A depends on module B, and module B also depends on module A. To resolve circular dependencies, you can take several approaches.

* One option is to use the ```CircularlyReferencedDependentModules``` statement in the [ModuleName].Build.cs file. You can read more about [here](https://forums.unrealengine.com/t/workaround-for-circular-dependencies/264945)!

* Another option is to create another module to further separate the code into smaller pieces.

* Finally, you can also refactor your code to avoid circular dependencies altogether.

**The best solution will depend on your specific situation and the complexity of your code.**

## Create a plugin

Lorem ipsum dolor sit amet, consectetur adipiscing elit. Suspendisse dictum turpis a nisl vestibulum, ac malesuada enim pellentesque. In bibendum suscipit sem, in pulvinar tellus vestibulum vel. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. In at suscipit diam. Sed nec enim luctus, condimentum eros quis, porta felis. Vestibulum dignissim turpis in justo pulvinar dapibus. Phasellus sodales, sem vitae blandit dictum, magna risus viverra sapien, ut malesuada purus arcu ut tellus.

Integer nunc metus, faucibus a luctus a, porta at turpis. Praesent sem felis, cursus vitae nulla nec, tincidunt interdum sem. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Quisque semper auctor ex, quis mollis sapien aliquam sit amet. Interdum et malesuada fames ac ante ipsum primis in faucibus. Sed suscipit dapibus aliquet. Nulla id vestibulum enim. Aenean dui nisi, mollis vitae porttitor at, gravida ac nisl. In sit amet velit lacus. Vivamus feugiat purus faucibus tincidunt pulvinar. Suspendisse fringilla eleifend risus vitae vestibulum. Etiam condimentum maximus ipsum.

## Helpful links

| Type | Author | Title | Length | Link |
| ------------- | ------------- | ------------- | ------------- | ------------- |
| Video | Mosh Hamedani | C++ Tutorial for Beginners - Learn C++ in 1 Hour | 01:22:55 | https://www.youtube.com/watch?v=ZzaPdXTrSb8 |
| VS Tool | Naotsun | UnrealMacroGenerator | | https://marketplace.visualstudio.com/items?itemName=Naotsun.Naotsun-UE-UMG |
| Article | Ben | benui | | https://benui.ca/unreal/ |
| Article | Unreal Engine | Dev Community | | https://dev.epicgames.com/community/ |
| Article | Community-driven | Unreal Engine Community Wiki | | https://unrealcommunity.wiki/ |
| Video | Alex Forsythe | Blueprints vs. C++: How They Fit Together and Why You Should Use Both | 47:13 | https://www.youtube.com/watch?v=VMZftEVDuCE |
| Video | Alex Forsythe | The Unreal Engine Game Framework: From int main() to BeginPlay | 27:22 | https://www.youtube.com/watch?v=IaU2Hue-ApI |
| Video | Alex Forsythe | Multiplayer in Unreal Engine: How to Understand Network Replication | 22:07 | https://www.youtube.com/watch?v=JOJP0CvpB8w |
| Video | Alex Forsythe | What do you do when Unreal Editor crashes? | 13:04 | https://www.youtube.com/watch?v=TXZGIvpEhW8 |
| Video | Unreal Engine | Blockout and Asset Production in UE5 | 34:07 | https://www.youtube.com/watch?v=R5TsbnW4fk8 |
| Video | Unreal Engine | Building Open Worlds in Unreal Engine 5 | 49:41 | https://www.youtube.com/watch?v=EEf07ggFWRw |
| Video | Unreal Engine | 35 UE5 Features You Probably Don't Know About | 49:55 | https://www.youtube.com/watch?v=k2IP5DYQ0-0 |
| Video | Amir Ansari | Unreal Overloaded - Soft and Hard References | 01:13:35 | https://www.youtube.com/watch?v=giDf4G6Ndk8 |
| Video | UNF Games | Unreal Engine 5 Beginner Modeling Tutorial - Learn to Model Inside Unreal! | 02:12:34 | https://www.youtube.com/watch?v=9InU0xbX7l0 |

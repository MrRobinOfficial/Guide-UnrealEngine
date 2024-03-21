<!-- prettier-ignore-start -->

## 🧱 Data Types

<table><tr><td>
This section was written in conjunction with ChatGPT.
</td></tr></table>

![Data types](static/img/Data_types.png)

<details open>
  <summary>Click to expand</summary>

### Characters

In C++ native, you write a character by using `char` data type:

```cpp
char myChar = 'a';
```

In Unreal, there are couples or `char` data types:

* `ANSICHAR` - An ANSI character. Normally a signed type.
* `WIDECHAR` - A wide character. Normally a signed type.
* `TCHAR` - Either `ANSICHAR` or `WIDECHAR`, depending on whether the platform supports wide characters or the requirements of the licensee.
* `UTF8CHAR` - An 8-bit character containing a UTF8 (Unicode, 8-bit, variable-width) code unit.
* `UTF16CHAR` - An 16-bit character containing a UTF16 (Unicode, 16-bit, variable-width) code unit.
* `UTF32CHAR` - An 32-bit character containing a UTF32 (Unicode, 32-bit, fixed-width) code unit.

When working with Unreal, you are typical going to work with `TCHAR` data type as a `char` type.

Define `TCHAR`:

```cpp
TCHAR MyChar = 'A';
```

And to use the extra functions for these data types, you must use:

* `FChar` for `TCHAR`
* `FCharWide`  for `WIDECHAR`
* `FCharAnsi` for `ANSICHAR`

Here's a list of functions, you can access from `FChar`:

* `ToUpper()` - Only converts ASCII characters.
* `ToLower()` - Only converts ASCII characters.
* `IsUpper()` - Returns a boolean if the character is an uppercase letter.
* `IsLower()` - Returns a boolean if the character is a lowercase letter.
* `IsAlpha()` - Returns a boolean if the character is an alphabetic letter.
* `IsGraph()` - Returns a boolean if the character is a graphic character (printable and not a space).
* `IsPrint()` - Returns a boolean if the character is a printable character (including whitespace).
* `IsPunct()` - Returns a boolean if the character is a punctuation character (neither alphanumeric nor a whitespace).
* `IsAlnum()` - Returns a boolean if the character is an alphanumeric character (a letter or a digit).
* `IsDigit()` - Returns a boolean if the character is a hexadecimal digit (0-9, a-f or A-f).
* `IsHexDigit()` - Returns a boolean if the character is a decimal digit (0-9).
* `IsWhitespace()` - Returns a boolean if the character is a whitespace character (space, tab, newline, carriage return, vertical tab or form feed).
* `IsControl()` - Returns a boolean if the character is a control character (non-printing).
* `IsOctDigit()` - Returns a boolean if the character is an octal digit (0-7).
* `ConvertCharDigitToInt()` - Converts a character representing a decimal digit to an integer.
* `IsIdentifier()` - Returns a boolean if the character is an alphanumeric or underscore character.
* `IsUnderscore()` - Returns a boolean if the character is an underscore.
* `ToUnsigned()` - Convert a character to an unsigned integer to avoid sign extension problems with signed characters smaller than `int`.

Include the header file:

```cpp
#include "Misc/Char.h"
```

Here's an example, of using these functions from `FChar`:

```cpp
TCHAR MyChar = 'a';

MyChar = FChar::ToUpper(MyChar); // MyChar: A

bool bIsDigit = FChar::IsDigit(MyChar); // false
bool bIsDigit = FChar::IsAlpha(MyChar); // true
```

You can read more about [TCHAR on Unreal's docs](https://docs.unrealengine.com/5.3/en-US/API/Runtime/Core/Misc/TChar/).

### Booleans

```cpp
// Unreal uses a 'b' prefix for booleans (always in lowercase).
bool bIsDead = true;
```

### Integers

In C++ native, you write a integer by using `int` data type:

```cpp
int health = 10;
```

In Unreal, you write a integer by using `int32`:

```cpp
int32 Health = 10;
```

In Unreal, the availability of different integer types such as `int8`, `int16`, and `int64` alongside the standard `int32` provides developers with a range of options tailored to specific needs in terms of both data size and numerical range.

```cpp
int8 NumberA = 0;       // -128                             ->      127
int16 NumberB = 0;      // -32,768                           ->      32,767
int32 NumberC = 0;      // -2,147,483,648                   ->      2,147,483,647
int64 NumberD = 0;      // 9,223,372,036,854,775,808        ->      9,223,372,036,854,775,807
```

You also have unsigned (positive-only) integers as well:

```cpp
uint8 NumberA = 0;      // 0    ->      255
uint16 NumberB = 0;     // 0    ->      65,535
uint32 NumberC = 0;     // 0    ->      4,294,967,295
uint64 NumberD = 0;     // 0    ->      18,446,744,073,709,551,615
```

### Floating point numbers

```cpp
// C++ always uses 'f' or 'F' literal for defining a float variable.
float SpeedInMetersPerSecond = 5.5f;
```

```cpp
// C++ never uses a literal for defining a double variable.
double SpeedInMetersPerSecond = 5.5;
```

### 🛟 Size can vary

It is generally recommended to use Unreal's typedefs, such as `int32` instead of `int` for representing 32-bit signed integers. This is because the exact size of `int` is not defined by the C++ standard.

C++ implementation can define the size of a data type in bytes (`sizeof(type)`) to be any value, as long as:

* The expression `sizeof(type) * CHAR_BIT` evaluates to a number of bits high enough to contain required ranges.
* And the ordering of type is still valid (e.g. `sizeof(int) <= sizeof(long)`).

The `CHAR_BIT` is the number of bits in char. It is declared in “limits.h” header file in C++ language. It is of 8-bits per byte.

You can read more about data ranges in this [section](#-data-types).

So, the summary data sizes would be:

<table><tr><td>

* `char`, `signed char` and `unsigned char` are at least 8 bits

* `signed short`, `unsigned short`, `signed int` and `unsigned int` are at least 16 bits

* `signed long` and `unsigned long` are at least 32 bits

* `signed long long` and `unsigned long long` are at least 64 bits

</td></tr></table>

You can read more in-depth about this from [Alex on Stack Overflow](https://stackoverflow.com/a/589684/17067030).

---

Here's a full list of Unreal's data type sizes:

| Data Type | Signed | Size (bytes) |
| --------- | ------ | ------------ |
| `bool`   | -  | NEVER assume the size |
| `TCHAR`   | -  | NEVER assume the size |
| `uint8`   | false  | 1            |
| `int8`    | true   | 1            |
| `uint16`  | false  | 2            |
| `int16`   | true   | 2            |
| `uint32`  | false  | 4            |
| `int32`   | true   | 4            |
| `uint64`  | false  | 8            |
| `int64`   | true   | 8            |
| `float`   | true   | 4            |
| `double`  | true   | 8            |

### 🦺 Unreal Engine Typedefs

In Unreal Engine, instead of writing `signed long long` for a 64-bit integer, you can now write `int64` instead. These aliases are called **typedefs**, which you can read more about [typedef keyword in C++ docs](https://en.cppreference.com/w/cpp/language/typedef).

You can read more about C++ typedefs in [this section](#typedefs).

Here is a full list of Unreal Engine's typedefs:

```cpp
//~ Unsigned base types.
/// An 8-bit unsigned integer.
typedef FPlatformTypes::uint8		uint8;
/// A 16-bit unsigned integer.
typedef FPlatformTypes::uint16		uint16;
/// A 32-bit unsigned integer.
typedef FPlatformTypes::uint32		uint32;
/// A 64-bit unsigned integer.
typedef FPlatformTypes::uint64		uint64;

//~ Signed base types.
/// An 8-bit signed integer.
typedef	FPlatformTypes::int8		int8;
/// A 16-bit signed integer.
typedef FPlatformTypes::int16		int16;
/// A 32-bit signed integer.
typedef FPlatformTypes::int32		int32;
/// A 64-bit signed integer.
typedef FPlatformTypes::int64		int64;

//~ Character types.
/// An ANSI character. Normally a signed type.
typedef FPlatformTypes::ANSICHAR	ANSICHAR;
/// A wide character. Normally a signed type.
typedef FPlatformTypes::WIDECHAR	WIDECHAR;
/// Either ANSICHAR or WIDECHAR, depending on whether the platform supports wide characters or the requirements of the licensee.
typedef FPlatformTypes::TCHAR		TCHAR;
/// An 8-bit character containing a UTF8 (Unicode, 8-bit, variable-width) code unit.
typedef FPlatformTypes::UTF8CHAR	UTF8CHAR;
/// A 16-bit character containing a UCS2 (Unicode, 16-bit, fixed-width) code unit, used for compatibility with 'Windows TCHAR' across multiple platforms.
typedef FPlatformTypes::CHAR16		UCS2CHAR;
/// A 16-bit character containing a UTF16 (Unicode, 16-bit, variable-width) code unit.
typedef FPlatformTypes::CHAR16		UTF16CHAR;
/// A 32-bit character containing a UTF32 (Unicode, 32-bit, fixed-width) code unit.
typedef FPlatformTypes::CHAR32		UTF32CHAR;

/// An unsigned integer the same size as a pointer
typedef FPlatformTypes::UPTRINT UPTRINT;
/// A signed integer the same size as a pointer
typedef FPlatformTypes::PTRINT PTRINT;
/// An unsigned integer the same size as a pointer, the same as UPTRINT
typedef FPlatformTypes::SIZE_T SIZE_T;
/// An integer the same size as a pointer, the same as PTRINT
typedef FPlatformTypes::SSIZE_T SSIZE_T;

/// The type of the NULL constant.
typedef FPlatformTypes::TYPE_OF_NULL	TYPE_OF_NULL;
/// The type of the C++ nullptr keyword.
typedef FPlatformTypes::TYPE_OF_NULLPTR	TYPE_OF_NULLPTR;
```

> [!WARNING]
> `uint16`, `uint32`, `uint64`, `int8`, `int16` and `double` are not supported with UHT[^3]. Meaning, can't expose to Blueprint.

### 📖 String Data Types

String in programming languages are fundamental data types used to represent and manipulate sequences of characters, such as words, sentences, or even binary data. They are extensively used in various programming tasks, including input/output operations, text processing, data serialization, and more.

In Unreal Engine, strings play a crucial role in handling text-based information within the game or application. Unreal Engine provides several string-related classes to cater to different use cases and requirements.

You can read more about [string handling from the docs](https://docs.unrealengine.com/4.26/en-US/ProgrammingAndScripting/ProgrammingWithCPP/UnrealArchitecture/StringHandling/).

### Text Macros

<table><tr><td>

* `TEXT`: The `TEXT()` macro is used for specifying wide-character (UTF-16) encoding. This makes the string literal platform independent. Without this macro, you are using ANSI encoding (which can cause issues on other machines).

* `INVTEXT`: The `INVTEXT()` macro is calling FText::AsCultureInvariant(TEXT(InTextLiteral)) with InTextLiteral as parameter. Helpful creating culture invariant FText from the given string literal.

* `LOCTEXT`: The `LOCTEXT()` macro is used to create `FText` literals specifically for localization. It takes a namespace and a key to identify the localized string.

</td></tr></table>

#### FName

In Unreal Engine, `FName` is a specialized type used for identifying objects within the Unreal Engine object system. It is optimized for fast comparison and storage and is commonly used for referencing actors, components, or assets in a performance-efficient manner.

The `FName` class stores strings as hashed indices, making it a lightweight and fast alternative to regular strings. Because of this, `FName` are **immutable** string class.

**Here's an example:**

Include the header file:

```cpp
#include "UObject/NameTypes.h"
```

Declare `FName`:

```cpp
FName MyName = FName(TEXT("PlayerName"));
```

#### FText

<table><tr><td>
This section was NOT written in conjunction with ChatGPT.
</td></tr></table>

`FText` is a specialized string class designed for localization support in Unreal Engine. Because of this, `FText` are **immutable** string class. FText provides the ability to represent text in different languages and cultures, making it a crucial component for building multi-language games or applications.

You can read more about it on [Unreal's docs](https://docs.unrealengine.com/5.3/en-US/ftext-in-unreal-engine/).

**Here's an example:**

Include the header file:

```cpp
#include "Internationalization/Text.h"
```

Declare `FText` from a string literal (non-localized):

```cpp
// Avoid this! Since this cost more performance than initializing directly as FText.
FText NewGameText = FText::FromString(TEXT("New Game"));
```

To use a multi-line `FText` inside Unreal Editor, you can specify `UPROPERTY` with meta tag of `Multiline`:

```cpp
UPROPERTY(EditAnywhere, Category = "Details", meta = (MultiLine = "true"))
FText Description;
```

Declare `FText` from `INVTEXT()` macro. Which creates a culture invariant `FText` from a string literal:

```cpp
FText TooltipText = INVTEXT("Tooltip Text");

/*
    Inside Unreal Engine source code:

    // Creates a culture invariant FText from the given string literal.
    #define INVTEXT(InTextLiteral) FText::AsCultureInvariant(TEXT(InTextLiteral))
*/

// So, FText::AsCultureInvariant does the same thing as INVTEXT() macro.
FText NewTooltipText = FText::AsCultureInvariant(TEXT("This is another tooltip text"));
```

```cpp
// Define the namespace to use with LOCTEXT
// This is only valid within a single file, and must be undefined before the end of the file
#define LOCTEXT_NAMESPACE "MyNamespace"
// Create text literals
FText PlayGameText = LOCTEXT("PlayGame", "Spiel beginnen"); // German langauge

// Helpful in the editor to localize the text into another language.
FText QuitGameText = NSLOCTEXT("StartMenu", "QuitGame", "Avsluta spelet"); // Swedish language

uint32 VersionNumber = 1405476850;
FText MachineOS = INVTEXT("Windows 11 Pro, 22H2, 22621.2215");
FText UserName = INVTEXT("MrRobin");
int32 UserAge = 22;
int32 SpeedInKph = 30;
int32 FuelInPercentage = 80;

// Formatting with FText. The supported types is: int32, uint32, float, double, FText, ETextGender.
FText VersionMessageText = FText::Format(
    LOCTEXT("VersionMessage", "You current version is {0} and is running on {1}"),
    VersionNumber,
    MachineOS
);

// FString also has FString::Prinf() function for formatting. FString::Prinf() is also similar to the native C++ sprintf() function.

// Use FFormatNamedArguments for organizing the FText::Format function.
FFormatNamedArguments Args;
Args.Add(TEXT("Name"), UserName);
Args.Add(TEXT("Age"), UserAge);
FText UserText = FText::Format(LOCTEXT("UserData", "User's name is {UserName} and is {Age} years old."), Args);

// You can also use FText::FormatNamed() function for formatting as well. Great for inlining the code.
FText CarMessageText = FText::FormatNamed(
    LOCTEXT("VehicleMessage", "You current speed is {Speed} and the fuel is at {Fuel}%"),
    TEXT("Speed"), SpeedInKph,
    TEXT("Fuel"), FuelInPercentage
);

#undef LOCTEXT_NAMESPACE // Undefine the current namespace
```

You can convert specific data type into `FText` format. For an example, can you use `FText::AsNumber()` to convert a number into `FText` with specific `FNumberFormattingOptions` formatting options.

Here's an example:

```cpp
float Health = 99.8999f; // We want to round this up, like this: 100.00

bool bIncludeLeadingZero = true;
int32 Precision = 2; // Number of decimals after decimal point. (0.00)

FNumberFormattingOptions NumberFormat;
NumberFormat.MinimumIntegralDigits = (bIncludeLeadingZero) ? 1 : 0;
NumberFormat.MaximumIntegralDigits = 10000;
NumberFormat.MinimumFractionalDigits = Precision;
NumberFormat.MaximumFractionalDigits = Precision;

FText NumberText = FText::AsNumber(Health, &NumberFormat);
NumberText = FText::AsCultureInvariant(NumberText); // Disable the culture formatting
```

Lorem ipsum dolor sit amet, consectetur adipiscing elit. Mauris nec sem mollis, suscipit lorem et, tincidunt nibh. Fusce pulvinar accumsan tellus, eu ornare sapien finibus a. Etiam lorem ante, hendrerit nec consectetur nec, tempor sed est. Phasellus sollicitudin et libero sit amet hendrerit. Praesent cursus porta maximus. Curabitur ac diam vel felis finibus cursus eget pharetra magna. Praesent eu ante consectetur velit dapibus viverra ut et dolor. Phasellus ultrices sollicitudin mauris vitae blandit. Vivamus vitae dolor viverra, euismod lacus eget, tempus dui. Nulla facilisi. Aliquam vulputate aliquam est ac laoreet. Sed vitae viverra nunc. Curabitur auctor diam ipsum, in posuere enim efficitur consequat. Fusce non porttitor odio, sit amet placerat orci. Sed tristique magna ut leo pellentesque, id tincidunt enim luctus.

> [!NOTE]
> Useful information that users should know, even when skimming content.

#### FString

`FString` is a dynamic, **mutable** string type in Unreal Engine, which provides a more flexible approach to string manipulation. Unlike `FName`, `FString` allows for modifications, such as appending, inserting, or removing characters, making it suitable for general string operations. It is widely used for various tasks, such as displaying messages, concatenating text, or formatting output strings.

Example usage:

```cpp
#include "Containers/UnrealString.h"

FString MyString = FString("Hello, World!");
```

Replace a substring with another in a `FString`:

```cpp
FString OriginalString = FString("Hello, my friend.");
OriginalString.ReplaceInline(TEXT("friend"), TEXT("buddy")); // Output: "Hello, my buddy."
```

Split a `FString` into an array of substrings using a delimiter:

```cpp
FString Sentence = FString("This is a sentence.");
TArray<FString> Words;
Sentence.ParseIntoArray(Words, TEXT(" "), true); // Output: ["This", "is", "a", "sentence."]
```

Reverse a `FString`:

```cpp
FString Text = FString("abcde");
Text.ReverseString(); // Output: "edcba"
```

---

| Data Type | Description | Use Case |
|-----------|-------------|----------|
| `FName` | A fast and lightweight name identifier for objects in Unreal Engine. | Best used for identifying assets and objects within the engine to save memory and improve performance. |
| `FText` | A localized string that supports text localization and provides text display features. | Ideal for displaying text to users in the game, supporting multiple languages and localization. |
| `FString` | A dynamic string that can be modified and used for general-purpose string manipulation. | Suitable for general text handling and string operations within the game code. |

### 🚀 Math Data Types

> [!NOTE]
> In Unreal Engine 5.0+, by default, all math related data types are using `double` as backend data type. This allows Unreal to support [large world coordinates (LWC)](https://docs.unrealengine.com/5.3/en-US/large-world-coordinates-in-unreal-engine-5/).

#### Vector4

A struct representing a 4D vector, consisting of four float values for the `X`, `Y`, `Z`, and `W` components.

Declare and initialize a `FVector4`:

```cpp
FVector4 MyVector = FVector(1.0f, 2.0f, 3.0f, 4.0f);
```

You can also initalize by an pre-made vector:

```cpp
FVector4 OldLocation = FVector4::ZeroVector; // (0, 0, 0)
FVector4 NewLocation = FVector4::OneVector; // (1, 1, 1)
```

> [!NOTE]
> Use `FVector4f` for `float` and `FVector4d` for `double`, as explicit data type for the backend conversion.

---

To use the integer version of `FVector4`:

```cpp
FIntVector4 IntVector4; // Default to 32-bit
FInt32Vector4 Int32Vector4; // 32-bit
FInt64Vector4 Int64Vector4; // 64-bit

FUintVector4 UintVector4; // Default to unsigned 32-bit
FUint32Vector4 Uint32Vector4; // Unsigned 32-bit
FUint64Vector4 FUint64Vector4; // Unsigned 64-bit
```

#### Vector3

A struct representing a 3D vector, consisting of three float values for the `X`, `Y`, and `Z` components. It is often used to represent position or direction in 3D space, and provides many useful functions such as vector addition, subtraction, normalization, and dot and cross products.

Declare and initialize a `FVector`:

```cpp
FVector MyVector = FVector(1.0f, 2.0f, 3.0f);
```

You can also initalize by an pre-made vector:

```cpp
FVector OldLocation = FVector::ZeroVector; // (0, 0, 0)
FVector NewLocation = FVector::OneVector; // (1, 1, 1)
```

You can select each component separately:

```cpp
FVector Vec = FVector::OneVector;

double X = Vec.X;
double Y = Vec.Y;
double Z = Vec.Z;

// or

double& X = Vec[0];
double& Y = Vec[1];
double& Z = Vec[2];
```

> [!NOTE]
> Use `FVector3f` for `float` and `FVector3d` for `double`, as explicit data type for the backend conversion.

---

Common static functions to use:

* `FVector::Cross()` - Calculate cross product this and another vector.
* `FVector::CrossProduct()` - Calculate the cross product of two vectors.
* `FVector::Dot()` - Calculate the dot product between this and another vector.
* `FVector::DotProduct()` - Calculate the dot product of two vectors.
* `FVector::Dist()` or `FVector::Distance()` - Euclidean distance between two points.
* `FVector::Dist2D()` or `FVector::DistXY()` - Euclidean distance between two points in the XY plane (ignoring Z).
* `FVector::DistSquared()` - Squared distance between two points.
* `FVector::DistSquared2D()` or `FVector::DistSquaredXY()` - Squared distance between two points in the XY plane only.
* `FVector::AllComponentsEqual()` - Check whether all components of this vector are the same, within a tolerance.

> [!TIP]
> You can use `|` operator for calling the dot product.

> [!TIP]
> You can use `^` operator for calling the cross product.

Common local functions to use:

* `GetComponentForAxis()` - Get a specific component of the vector, given a specific axis by enum.
* `SetGetComponentForAxis()` - Set a specified component of the vector, given a specific axis by enum.
* `Set()` - Set the values of the vector directly.
* `GetMax()` - Get the maximum value of the vector's components.
* `GetAbsMax()` - Get the maximum absolute value of the vector's components.
* `GetMin()` - Get the minimum absolute value of the vector's components.
* `GetAbsMin()` - Get the minimum absolute value of the vector's components.
* `GetAbs()` - Get a copy of this vector with absolute value of each component.
* `Size()` or `Length()` - Get the length (magnitude) of this vector.
* `SizeSquared()` or `SquaredLength()` - Get the squared length of this vector.
* `Size2D()` - Get the length of the 2D components of this vector.
* `SizeSquared2D()` - Get the squared length of the 2D components of this vector.
* `HeadingAngle()` - Convert a direction vector into a 'heading' angle.
* `IsNearlyZero()` - Check whether vector is near to zero within a specified tolerance.
* `IsZero()` - Check whether all components of the vector are exactly zero.
* `IsUnit()` - Check if the vector is of unit length, with specified tolerance.
* `IsNormalized()` - Checks whether vector is normalized.
* `Normalize()` - Normalize this vector in-place if it is larger than a given tolerance. Leaves it unchanged, if not.
* `GetSignVector()` - Get a copy of the vector as sign only. Each component is set to +1 or -1, with the sign of zero treated as +1.
* `Projection()` - Projects 2D components of vector based Z.
* `GridSnap()` - Get a copy of this vector snapped to a grid.
* `IsUniform()` - Check whether X, Y and Z are nearly equal.
* `ConstainsNaN()` - Utility to check if there are any non-finite values (NaN or Inf) in this vector.
* `ToString()` - Get a textural representation of this vector.
* `ToCompactString()` - Get a short textural representation of this vector, for compact, readable logging.
* `ToText()` - Get a locale aware textural representation of this vector.
* `ToCompactText()` - Get a short locale aware textural representation of this vector, for compact, readable logging.

---

To use the integer version of `FVector`:

```cpp
FIntVector IntVector = FIntVector(5, 10, -25); // Default to 32-bit
FUintVector UintVector = FUintVector(5, 10, 25); // Default to unsigned 32-bit
```

Here's the more explicit versions:

```cpp
FIntVector3 IntVector3; // Default to 32-bit
FInt32Vector3 Int32Vector3; // 32-bit
FInt64Vector3 Int64Vector3; // 64-bit

FUintVector3 UintVector3; // Default to unsigned 32-bit
FUint32Vector3 Uint32Vector3; // Unsigned 32-bit
FUint64Vector3 FUint64Vector3; // Unsigned 64-bit
```

#### Vector2

A struct representing a 2D vector, consisting of two float values for the `X` and `Y` components.

Declare and initialize a `FVector2D`:

```cpp
FVector2D MyVector = FVector2D(1.0f, 2.0f, 3.0f);
```

You can also initalize by an pre-made vector:

```cpp
FVector2D OldLocation = FVector2D::ZeroVector; // (0, 0, 0)
FVector2D NewLocation = FVector2D::OneVector; // (1, 1, 1)
```

> [!NOTE]
> Use `FVector2f` for `float` and `FVector2d` for `double`, as explicit data type for the backend conversion.

---

To use the integer version of `FVector2D`:

```cpp
FIntVector2 IntVector2; // Default to 32-bit
FInt32Vector2 Int32Vector2; // 32-bit
FInt64Vector2 Int64Vector2; // 64-bit

FUintVector2 UintVector2; // Default to unsigned 32-bit
FUint32Vector2 Uint32Vector2; // Unsigned 32-bit
FUint64Vector2 FUint64Vector2; // Unsigned 64-bit
```

#### IntPoint

A struct representing a 2D integer points, consisting of two int values for the `X` and `Y` components.

Declare and initialize a `FIntPoint`:

```cpp
FIntPoint MinPoint = FIntPoint(-127, -127);
FIntPoint MaxPoint = FIntPoint(128, 128);
```

Declare and initialize a `FUIntPoint`:

```cpp
FUIntPoint UnsignedMinPoint = FUIntPoint(0, 0);
FUIntPoint UnsignedMaxPoint = FUIntPoint(255, 255);
```

> [!NOTE]
> Use `FInt32Point` for `int32`, `FUint32Point` for `uint32`, `FInt64Point` for `int64` and `FUint64Point` for `uint64`, as explicit data type for the backend conversion.

#### IntRect

A struct representing a 2D integer rectangles, consisting of two IntPoint values for the `Min` and `Max` components.

Declare and initialize a `FIntRect`:

```cpp
FIntPoint MinPoint = FIntPoint(-127, -127);
FIntPoint MaxPoint = FIntPoint(128, 128);
FIntReact Rect = FIntRect(MinPoint, MaxPoint);
```

Declare and initialize a `FUIntReact`:

```cpp
FUIntPoint UnsignedMinPoint = FUIntPoint(0, 0);
FUIntPoint UnsignedMaxPoint = FUIntPoint(255, 255);
FUIntReact UnsignedRect = FIntRect(UnsignedMinPoint, UnsignedMaxPoint);
```

> [!NOTE]
> Use `FInt32Rect` for `int32`, `FUint32Rect` for `uint32`, `FInt64Rect` for `int64` and `FUint64Rect` for `uint64`, as explicit data type for the backend conversion.

#### Rotator

A struct representing a rotation in 3D space, consisting of three float values for the `Pitch`, `Yaw`, and `Roll` angles. It is often used to represent the orientation of an object, and provides many useful functions such as conversion to and from quaternions, and rotation of other vectors and rotators.

Declare and initialize a `FRotator`:

```cpp
FRotator MyRotator = FRotator(0.0f, 90.0f, 0.0f);
```

You can also initalize by an pre-made rotator:

```cpp
FRotator MyRotator = FRotator::ZeroRotator; // (0, 0, 0)
```

> [!NOTE]
> Use `FRotator3f` for `float` and `FRotator3d` for `double`, as explicit data type for the backend conversion.

---

Common static functions to use:

* `FRotator::Vector()` - Convert a rotation into a unit vector facing in its direction.

Common local functions to use:

* `GetInverse()` - Returns the inverse of the rotator.
* `GridSnap()` - Get the rotation, snapped to specified degree segments.

#### Quaternion

A struct representing a quaternion in 3D space, consisting of three float values for the `X`, `Y`, `Z`, and `W` components. Quaternion a mathematical concept used to represent 3D rotations. It is commonly used in conjunction with `FVector` to represent orientations and rotations in 3D space.

Declare and initialize a `FQuat`:

```cpp
FQuat MyQuaternion = FQuat(0.0f, 90.0f, 0.0f, 0.0f);
```

You can also initalize by an pre-made quaternion:

```cpp
FQuat MyQuaternion = FQuat::Identify; // (0, 0, 0, 0)
```

> [!NOTE]
> Use `FQuat4f` for `float` and `FQuat4d` for `double`, as explicit data type for the backend conversion.

#### Transform

A struct representing a 3D transformation, consisting of a `FVector` for translation, a `FQuat` for rotation, and a `FVector` for scale. It is often used to represent the position, orientation, and size of an object in 3D space, and provides many useful functions for transforming other vectors and transforms.

Declare and initialize a `FTransform`:

```cpp
FVector Location = FVector::ZeroVector;
FRotator Rotation = FRotator::ZeroRotator;
FVector Scale = FVector::OneVector;

// Note! Unreal will convert FRotator into FQuat in the backend.
FTransform MyTransform = FTransform(Rotation, Location, Scale);
```

You can also initalize by an pre-made transform:

```cpp
FTransform MyTransform = FTransform::Identify; // NaN
```

> [!NOTE]
> Use `FTransform3f` for `float` and `FTransform3d` for `double`, as explicit data type for the backend conversion.

#### Plane

A struct representing a 3D plane.

Here's an example:

```cpp
float X = 0.0f;
float Y = 0.0f;
float X = 0.0f;

FPlane Plane = FVector(X, Y, Z);
```

Here's another way to initialize `FPlane`:

```cpp
FPlane Plane = FVector(FVector(0.0f, 0.0f, 0.0f));
```

> [!NOTE]
> Use `FPlane4f` for `float` and `FPlane4d` for `double`, as explicit data type for the backend conversion.

#### Matrix

A struct representing a 4x4 matrix of loating point values.

Here's an example:

```cpp
FPlane XPlane = FPlane(1.0f, 0.0f, 0.0f, 0.0f);
FPlane YPlane = FPlane(0.0f, 1.0f, 0.0f, 0.0f);
FPlane ZPlane = FPlane(0.0f, 0.0f, 1.0f, 0.0f);
FPlane WPlane = FPlane(0.0f, 0.0f, 0.0f, 1.0f);

FMatrix Matrix = FMatrix(XPlane, YPlane, ZPlane, WPlane);
```

```cpp
FVector XVector = FVector(1.0f, 0.0f, 0.0f);
FVector YVector = FVector(0.0f, 1.0f, 0.0f);
FVector ZVector = FVector(0.0f, 0.0f, 1.0f);
FVector WVector = FVector(0.0f, 0.0f, 0.0f);

FMatrix Matrix = FMatrix(XVector, YVector, ZVector, WVector);
```

```cpp
FMatrix Matrix;

int32 RowIndex = 0;
int32 ColumnIndex = 0;

double Element = Matrix[RowIndex][ColumnIndex];
```

> [!NOTE]
> Use `FMatrix44f` for `float` and `FMatrix44d` for `double`, as explicit data type for the backend conversion.

#### Sphere

A struct representing a 3D sphere.

Here's an example:

```cpp
FVector Center = FVector::ZeroVector;
float Radius = 500.0f;

FSphere Sphere = FSphere(Center, Radius);
```

> [!NOTE]
> Use `FSphere3f` for `float` and `FSphere3d` for `double`, as explicit data type for the backend conversion.

#### Box

A struct representing a 3D box.

Here's an example:

```cpp
FVector MinPoint = FVector(15.5f, 15.5f);
FVector MaxPoint = FVector(25.0f, 25.0f);

FBox Box2D = FBox(MinPoint, MaxPoint);
```

> [!NOTE]
> Use `FBox3f` for `float` and `FBox3d` for `double`, as explicit data type for the backend conversion.

#### Box2D

A struct representing a 2D box.

Here's an example:

```cpp
FVector2D MinPoint = FVector2D(10, 10);
FVector2D MaxPoint = FVector2D(20, 20);

FBox2D Box2D = FBox2D(MinPoint, MaxPoint);
```

> [!NOTE]
> Use `FBox2f` for `float` and `FBox2d` for `double`, as explicit data type for the backend conversion.

#### Ray

A struct representing a 3D ray, consisting of two vector values for the `Origin` and `Direction` components.

Here's an example:

```cpp
FVector Origin = FVector::ZeroVector;
FVector Direction = FVector::ForwardVector;
bool bDirectionIsNormalized = false;

FRay Ray = FRay(Origin, Direction, bDirectionIsNormalized);
```

Functions to use with `FRay`:

```cpp
FVector Point = FVector::ZeroVector;

FVector ClosestPoint = Ray.ClosestPoint(Point);
double MinDistance = Ray.Dist(Point);
double MinSqrtDistance = Ray.DistSquared(Point);

double ScalarDistance = 0.5; // Along the ray
FVector PointAt = Ray.PointAt(ScalarDistance);
double CalcScalarDistance = Ray.GetParameter(PointAt); // Will convert back to 'ScalarDistance'
```

> [!NOTE]
> Use `FRay3f` for `float` and `FRay3d` for `double`, as explicit data type for the backend conversion.

#### Colors

`FColor` stores a color with 8 bits (byte) of precision per channel.

`FLinearColor` stores a linear color with 32-bit/component floating point RGBA color.

Here's an example, how to initialize them:

```cpp
FLinearColor LinearColor = FLinearColor(0.5f, 1.0f, 0.3f);
```

```cpp
FColor Color = FColor(150, 200, 50);

// or

// Supported formats are: RGB, RRGGBB, RRGGBBAA, RGB, #RRGGBB, #RRGGBBAA
FColor HexColor = FColor::FromHex(TEXT("#9fd99e"));
FString HexString = HexColor.ToHex(); // Convert it back to a string. The format of the string is RRGGBBAA.
```

List of common colors of ´FLinearColor´:

* `FLinearColor::White`
* `FLinearColor::Gray`
* `FLinearColor::Black`
* `FLinearColor::Transparent`
* `FLinearColor::Red`
* `FLinearColor::Green`
* `FLinearColor::Blue`
* `FLinearColor::Yellow`

List of common colors of `FColor`:

* `FColor::White`
* `FColor::Black`
* `FColor::Transparent`
* `FColor::Red`
* `FColor::Green`
* `FColor::Blue`
* `FColor::Yellow`
* `FColor::Cyan`
* `FColor::Magenta`
* `FColor::Orange`
* `FColor::Purple`
* `FColor::Turquoise`
* `FColor::Silver`
* `FColor::Emerald`

You can read more about [linear color at Unreal's docs](https://docs.unrealengine.com/5.3/en-US/API/Runtime/Core/Math/FLinearColor/).

You can also read more about [color at Unreal's docs](https://docs.unrealengine.com/5.3/en-US/API/Runtime/Core/Math/FColor/).

### 💐 Collections

![Collections](static/img/Collections.png)

<table><tr><td>
This section was NOT written in conjunction with ChatGPT.
</td></tr></table>

| Data Container | Description                                                                                                                                                                                                                                                     | Use Case                                                                                                                                                                                   |
|----------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **TArray**         | A dynamic array that can grow or shrink in size at runtime, supporting random access and iteration.                                                                                                                                                            | Suitable for storing and managing a collection of elements where the size may change frequently and quick access to elements is required.                                                  |
| **TSet**           | A set data structure that stores unique elements in no particular order, efficiently supporting element insertion, deletion, and membership checks.                                                                                                              | Ideal for maintaining a collection of distinct elements and performing fast membership checks without duplicates.                                                                          |
| **TMap**           | An associative container that stores key-value pairs, allowing efficient lookup and retrieval based on keys.                                                                                                                                                  | Used for creating dictionaries or associative arrays, where data is organized based on unique keys for quick and efficient access.                                                          |

#### TArray

A dynamic array that can store a variable number of elements of the same type. It provides many useful functions, such as adding, removing, sorting, and searching for elements, as well as iterating over them.

**Here's an example:**

Include the header file:

```cpp
#include "Containers/Array.h"
```

Declare a `TArray` of `int32` (integers)

```cpp
TArray<int32> MyArray { 1, 2, 3 };
```

Add an element to the array:

```cpp
MyArray.Add(4);

// MyArray: { 1, 2, 3, 4 }
```

Add multiple elements to the array:

```cpp
MyArray.Append({10, 15, 20});

// MyArray: { 1, 2, 3, 4, 10, 15, 20 }
```

Remove elements from the array:

```cpp
MyArray.RemoveAt(0);
MyArray.RemoveAt(0);

// MyArray: { 3, 4, 10, 15, 20 }
```

Get the number of elements from the array:

```cpp
int32 NumOfElements = MyArray.Num(); // 5
```

Loop through the array and log each element:

```cpp
for (const int32& Element : MyArray)
{
    UE_LOG(LogTemp, Log, TEXT("Element: %i"), Element);
}
```

---

You can either allocate an array on the **stack** or on the **heap**. Without specifying, you are creating the array allocation on the heap, while the array returns a data container on the stack.

If you don't know about what the difference between **stack** and **heap** allocation, highly suggest reading upon the subject in [this section](#-stack-vs-heap).

Here is a way to allocate an array on the stack:

```cpp
TArray<int32, TInlineAllocator<4>> StackArray; // Allocate 4 elements on the stack

StackArray.Add(1);
StackArray.Add(2);
StackArray.Add(3);
StackArray.Add(4);

// Now we added the same amount of elements, to our buffer size (which has been allocated on the stack).
// If we try to add more elements than allocated, Unreal will default TArray to use heap allocation for the rest of elements.

StackArray.Add(5); // Will be allocated on the heap!
```

> [!WARNING]
> If you're trying to allocate a heap object on the stack with `TInlineAllocator`, Unreal will default to a heap allocation.

> [!WARNING]
> If you add more elements than have been allocated for, Unreal will default to a heap allocation instead.

> [!NOTE]
> Unreal will treat as stack allocated array as a different data type, compare to a regular array. To accommodate this, use `TArrayView` instead.

If you want to avoid filling up the rest of elements with heap allocation, then use `TFixedAllocator`:

```cpp
TArray<int32, TFixedAllocator<4>> StackArray; // Allocate 4 elements on the stack

StackArray.Add(1);
StackArray.Add(2);
StackArray.Add(3);
StackArray.Add(4);

StackArray.Add(5); // Unreal calls an assertion, which will CRASH Unreal in runtime mode!

// If you're continuing on with the assertion, using Visual Studio Debugger, Unreal will call Reset() function.
// Clearing out all elements, but keeping the current allocation size.

// Same thing happens with brace initialization.
TArray<int32, TFixedAllocator<4>> StackArray{ 1, 2, 3, 4, 5 }; // Allocate 4 elements on the stack, but we got 5 elements!
```

#### TSet

A set of unique elements of a single type, implemented as a hash table. It provides many of the same functions as `TArray`, but with faster lookup times for large collections of elements.

**Here's an example:**

Include the header file:

```cpp
#include "Containers/Set.h"
```

Declare a `TSet` of `FName` (names):

```cpp
TSet<FName> MySet;
```

Add elements to the set:

```cpp
// Add single element to the set
MySet.Add(TEXT("hello"));

// Add multiple elements to the set
MySet.Append({TEXT("cruel"), TEXT("world"), TEXT("hello")});

// MySet: { "hello", "curel", "world" }
```

Get number of elements from the set:

```cpp
int32 NumOfElements = MySet.Num(); // 4
```

Check if an element exists in the set:

```cpp
if (MySet.Contains(TEXT("cruel")))
{
    UE_LOG(LogTemp, Log, TEXT("'Cruel' element is in the set"));
}
```

Remove an element from the set:

```cpp
MySet.Remove(TEXT("cruel"));

// MySet: { "hello", "world" }
```

Iterate through the set and log each element:

```cpp
for (const FName& Name : MySet)
{
    UE_LOG(LogTemp, Log, TEXT("Name: %s"), *Name.ToString());
}
```

Convert the set to an array:

```cpp
TArray<FName> CopyOfSet = MySet.Array();
CopyOfSet[0] = TEXT("goodbye");

// CopyOfSet: { "goodbye", "world" }
```

#### TMap

A map of key-value pairs, implemented as a hash table. It allows fast lookup of a value given a key, and supports adding, removing, and iterating over key-value pairs.

**Here's an example:**

Include the header file:

```cpp
#include "Containers/Map.h"
```

Declare a `TMap` of `FName` (names) to `int32` (integers):

```cpp
TMap<FName, int32> MyMap = { { TEXT("player_id"), 457865 }, { TEXT("player_age"), 35 } };

// MyMap: { { "player_id", 457865 }, { "player_age", 35 } }
```

Add elements to the map:

```cpp
int32& PlayerRankRef = MyMap.Add(TEXT("player_rank"));
PlayerRankRef = 420;

MyMap.Add(TEXT("player_speed"), 15);

// MyMap: { { "player_id", 457865 }, { "player_age", 35 }, { "player_rank", 420 }, { "player_speed", 15 } }
```

Finds the value in the map from the key. Otherwise, create and add the key to the map (with default value):

```cpp
int32& PlayerIDRef = MyMap.FindOrAdd(TEXT("player_id"));
PlayerIDRef = 001100;

// MyMap: { { "player_id", 001100 }, { "player_age", 35 }, { "player_rank", 420 }, { "player_speed", 15 } }
```

Get number of elements from the map:

```cpp
int32 NumOfElements = MyMap.Num(); // 4
```

Iterate through the map and log key-value pairs:

```cpp
for (const TPair<FName, int32>& KeyValuePair : MyMap)
{
    UE_LOG(LogTemp, Log, TEXT("Key: %s, Value: %i"), *KeyValuePair.Key.ToString(), KeyValuePair.Value);
}
```

Check if "player_rank" exists in the map and log its value if found:

```cpp
if (int32* PlayerRankPtr = MyMap.Find(TEXT("player_rank")))
{
    UE_LOG(LogTemp, Log, TEXT("Player rank is: %i"), *PlayerRankPtr);
}
```

Access an element in the map:

```cpp
int32 OutSpeed;

if (MyMap.TryGetValue(TEXT("player_speed"), OutSpeed))
{
    UE_LOG(LogTemp, Log, TEXT("Player's speed: %i [m/s]"), OutSpeed);
}
```

Modify an element in the map:

```cpp
MyMap[TEXT("player_age")] = -1;

// MyMap: { { "player_id", 001100 }, { "player_age", -1 }, { "player_rank", 420 }, { "player_speed", 15 } }
```

Remove an element from the map:

```cpp
MyMap.Remove(TEXT("player_age")); // Reference variables (such as PlayerRankRef and PlayerIDRef) become unsafe since the map size and elements have changed.

// MyMap: { { "player_id", 001100 }, { "player_rank", 420 }, { "player_speed", 15 } }
```

Convert the map to an array of key-value pairs:

```cpp
TArray<TPair<FName, int32>> KeyValueArray = MyMap.Array();
int32 PlayerID = KeyValueArray[0].Value; // 001100
```

#### Common and helpful functions

With these containers, you can use a couple of helpful functions.

* `Empty()` - Clears out the store elements (as well as resizing the buffer to zero).
* `Reset()` - Clears out the store elements (without resizing the buffer).
* `GetSlack()` - Gets the number of store elements minus it's buffer size. `Slack = NumOfElements - BufferCapacity`.
* `GetAllocationSize()` - Gets the buffer capacity.
* `Shrink()` - It will reset the buffer size to the number of elements, currently being stored.
* `Reserve()` - It will expand buffer size to that amount. Note, buffer size can change later on.
* `RemoveAll` - Will remove all elements with prediction as an argument.
* `RemoveAllSwap` - Same as `RemoveAll()` function, but doesn't preserve the order.

Here's an example:

```cpp
#include "Containers/Array.h"

TArray<int32> Array = { 1, 2, 2, 3, 4, 4, 5 };

// Create a lamba function (which is a temporary function, which takes this class as reference parameter)
Array.RemoveAll([&](const int32& Item)
{
    // Removes all item, if the item is equal to: 2
    return Item == 2;
});

// Current elements: { 1, 3, 4, 4, 5 }

Array.RemoveAllSwap([&](const int32& Item)
{
    // Removes all item, if the item is equal to: 2
    return Item == 4;
});

// Current elements: { 5, 3, 1 }
```

```cpp
#include "Containers/Array.h"

TArray<int32> Array;
Array.Add(1);
Array.Add(2);

// Current element count: 2
// Current buffer size: 4

Array.Empty();

// Current element count: 0
// Current buffer size: 0

Array.Add(1);
Array.Add(2);

// Current element count: 2
// Current buffer size: 4

Array.Reset();

// Current element count: 0
// Current buffer size: 4
```

```cpp
TArray<int32> Array;
Array.Add(1);
Array.Add(2);
Array.Add(3);
Array.Add(4);
Array.Add(5);

// Current element count: 5
// Current buffer size: 22

int32 SlackAmount = Array.GetSlack(); // 22 - 5 = 17 (Slack = BufferCapacity - NumOfElements)

Array.RemoveAt(0);
Array.RemoveAt(1);

// Current element count: 3
// Current buffer size: 22

Array.Shrink();

// Current element count: 3
// Current buffer size: 4
```

---

In order to remove an element without allowing the container to shrink, you can use these arguments:

```cpp
#include "Containers/Array.h"

TArray<int32> Array { 1, 2, 3 };

// Removes the last element, without enable the container to shrink itself.
int32 LastElementIndex = Array.Num() - 1;
int32 NumToRemove = 1;
bool bAllowShrinking = false;
Array.RemoveAt(LastElementIndex, NumToRemove, bAllowShrinking)
```

---

When and how much does the container allocated memory for future use cases?

If you run a for-loop and running the debugger, we can analyze the allocation size and where the container has its breakpoints for requesting more memory.

```cpp
#include "Containers/Array.h"

void UpdatingAllocationSize()
{
    TArray<int32> Array;

    int32 PreviousAllocatedSize = Array.GetAllocatedSize();

    for (int32 i = 0; i < 100; ++i)
    {
        Array.Add(69);

        int32 NewAllocatedSize = Array.GetAllocatedSize();

        if (PreviousAllocatedSize != NewAllocatedSize)
        {
            UE_LOG(LogTemp, Log, TEXT("[%s - %s]: Allocation size has changed from: %i to: %i. Current number of elements: %i and current max size: %i"), ANSI_TO_TCHAR(__FUNCTION__), TEXT("Adding"), PreviousAllocatedSize, NewAllocatedSize, Array.Num(), NewAllocatedSize / sizeof(int32));

            PreviousAllocatedSize = NewAllocatedSize;
        }
    }

    // Allocation size is data size times buffer size.

    // Int32 is 4 bytes in size
    // And the buffer size is currently at 4.

    // Allocation size = 4 * 4 = 16 bytes

    /*
        LogTemp: Allocation size has changed from: 0 to: 16. Current number of elements: 1 and current max size: 4
        LogTemp: Allocation size has changed from: 16 to: 88. Current number of elements: 5 and current max size: 22
        LogTemp: Allocation size has changed from: 88 to: 188. Current number of elements: 23 and current max size: 47
        LogTemp: Allocation size has changed from: 188 to: 328. Current number of elements: 48 and current max size: 82
        LogTemp: Allocation size has changed from: 328 to: 520. Current number of elements: 83 and current max size: 130
    */

    for (int32 i = 0; Array.Num() != 0; ++i)
    {
        Array.RemoveAt(Array.Num() - 1);

        int32 NewAllocatedSize = Array.GetAllocatedSize();

        if (PreviousAllocatedSize != NewAllocatedSize)
        {
            UE_LOG(LogTemp, Log, TEXT("[%s - %s]: Allocation size has changed from: %i to: %i. Current number of elements: %i and current max size: %i"), ANSI_TO_TCHAR(__FUNCTION__), TEXT("Removing"), PreviousAllocatedSize, NewAllocatedSize, Array.Num(), NewAllocatedSize / sizeof(int32));

            PreviousAllocatedSize = NewAllocatedSize;
        }
    }

    /*
        LogTemp: Allocation size has changed from: 520 to: 260. Current number of elements: 65 and current max size: 65
        LogTemp: Allocation size has changed from: 260 to: 0. Current number of elements: 0 and current max size: 0
    */
}
```

#### Algo Namespace

Algo is a namespace containing a lot of helper functions for container.

Here is common functions:

* `Algo::Accumulate()` - Sums a range.
* `Algo::AllOf()` - Checks if every projection of the elements in the range is truthy.
* `Algo::AnyOf()` - Checks if any projection of the elements in the range is truthy.
* `Algo::BinarySearch()` - Returns index to the first found element matching a value in a range, the range must be sorted by `<`
* `Algo::BinarySearchBy()` - Same as `Algo::BinarySearch()`, but with custom logic.
* `Algo::Compare()` - Compares two contiguous containers using operator== to compare pairs of elements.
* `Algo::CompareByPredicate()` - Compares two contiguous containers using a predicate to compare pairs of elements.
* `Algo::Copy()` - Copies a range into a container.
* `Algo::CopyIf()` - Conditionally copies a range into a container.
* `Algo::Count()` - Counts elements of a range that equal the supplied value.
* `Algo::CountBy()` - Counts elements of a range whose projection equals the supplied value.
* `Algo::CountIf()` - Counts elements of a range that match a given predicate.
* `Algo::Find()` - Returns a pointer to the first element in the range which is equal to the given value.
* `Algo::FindBy()` - Returns a pointer to the first element in the range whose projection is equal to the given value.
* `Algo::FindLast()` - Returns a pointer to the last element in the range which is equal to the given value.
* `Algo::FindLastBy()` - Returns a pointer to the last element in the range whose projection is equal to the given value.
* `Algo::FindSequence()` - Searches for the first occurrence of a sequence of elements in another sequence.
* `Algo::ForEach()` - Invokes a callable to each element in a range.
* `Algo::Includes()` - Checks if one sorted contiguous container is a subsequence of another sorted contiguous container by comparing pairs of elements.
* `Algo::IndexOf()` - Returns the index of the first element in the range which is equal to the given value.
* `Algo::IndexOfByPredicate()` - Returns the index of the first element in the range which matches the predicate.
* `Algo::IsSorted()` - Tests if a range is sorted by its element type's operator `<`.
* `Algo::MaxElement()` - Returns a pointer to the maximum element in a range.
* `Algo::MinElement()` - Returns a pointer to the minimum element in a range.
* `Algo::NoneOf()` - Checks if no element in the range is truthy.
* `Algo::Sort()` - Sort the range. It will default to `<` operator (ascending order). However, custom logic can be added.
* `Algo::SortBy()` - Same as `Algo::Sort`, but uses a projection method. Projections are transformations but for values.
* `Algo::RandomShuffle()` - Randomly shuffle a range of elements.
* `Algo::RemoveIf()` - Moves all elements which do not match the predicate to the front of the range, while leaving all other elements is a constructed but unspecified state.
* `Algo::Replace()` - Replaces all elements that compare equal to one value with a new value.
* `Algo::ReplaceIf()` - Replaces all elements that satisfy the predicate with the given value.
* `Algo::Reverse()` - Reverses a range.
* `Algo::Transform()` - Applies a transform to a range and stores the results into a container.

You can read more about Algo on [Unreal's docs](https://docs.unrealengine.com/5.3/en-US/API/Runtime/Core/Algo/).

Here's an example of using them:

```cpp
#include "Algo/ForEach.h"
#include "Algo/Accumulate.h"
#include "Algo/IndexOf.h"

TArray<FString> Array;
Array.Add(TEXT("hello"));
Array.Add(TEXT("cRuEL"));
Array.Add(TEXT("WORLD"));

const int32 FoundIndex = Algo::IndexOf(Array, FString(TEXT("cRuEL")));

if (FoundIndex != INDEX_NONE)
{
    // Successfully found the index
}

const int32 FoundIndexPred = Algo::IndexOfByPredicate(Array,
    [&](const FString& Arg)
    {
        return TEXT("hello") == Arg.ToLower();
    });

if (FoundIndexPred != INDEX_NONE)
{
    // Successfully found the index with prediction
}

TArray<FString> TransformArray;

Algo::Transform(Array, TransformArray, [](const FString& Item) { return Item.ToUpper(); });

// { "HELLO", "CRUEL", "WORLD" }

Algo::Reverse(TransformArray);

// { "WORLD", "CRUEL", "HELLO" }

TArray<int32> SortArray { 1, 5, 3, -4, 2, -1 };
Algo::Sort(SortArray);

// { -4, -1, 1, 2, 3, 5 }

// Create a lambda function for this projection
auto AbsProjection = [](int32 Value) { return FMath::Abs(Value); };

// Will sort based on this projection. But will still reserve the original values.
Algo::SortBy(SortArray, AbsProjection);

// { -1, 1, 2, 3, -4, 5 }

Algo::ForEach(SortArray, [](int32& Value)
{
    Value *= 2;
});

// { -2, 2, 4, 6, -8, 10 }

// Will sort based on descending order
auto ReverseSortPredicate = [](int32 A, int32 B) { return A > B; };
Algo::SortBy(SortArray, AbsProjection, ReverseSortPredicate);

// { 10, -8, 6, 4, 2, -2 }
```

#### TMultiMap

Similar to `TMap`, but allows multiple values to be associated with the same key. It also provides functions for iterating over all the values associated with a particular key.

**Here's an example:**

Include the header file:

```cpp
#include "Containers/Map.h"
```

Declare a `TMultiMap` of `FName` (names) to floats:

```cpp
TMultiMap<FName, float> MyMultiMap = { { TEXT("X"), 10.0f }, { TEXT("Y"), 69.0f }, { TEXT("Z"), 0.0f } }
```

Add elements to the map:

```cpp
MyMultiMap.Add(TEXT("X"), -10.0f);
MyMultiMap.Add(TEXT("Y"), 69.0f);
MyMultiMap.AddUnique(TEXT("Y"), 69.0f); // Will not add if both key and value match an existing association in the map!

// MyMultiMap: { { TEXT("X"), 10.0f }, { TEXT("Y"), 69.0f }, { TEXT("Z"), 0.0f }, { TEXT("Y"), 69.0f }, { TEXT("X"), -10.0f } }
```

Get all values for a key in the map:

```cpp
TArray<float> OutValues;
MyMultiMap.MultiFind(TEXT("Y"), OutValues);

// OutValues: { 69.0f, 69.0f }
```

Get number of elements from the multi-map:

```cpp
int32 NumOfElements = MyMultiMap.Num(); // 5
```

Loop through the values and log each one:

```cpp
for (const float& Value : OutValues)
{
    UE_LOG(LogTemp, Log, TEXT("Value: %f"), Value);
}
```

Remove all values for a key in the map:

```cpp
MyMultiMap.Remove(TEXT("Y"));

// MyMultiMap: { { TEXT("X"), 10.0f }, { TEXT("Z"), 0.0f }, { TEXT("X"), -10.0f } }
```

Remove the first association between the specified key and value from the map:

```cpp
MyMultiMap.RemoveSingle(TEXT("X"), 10.0f);

// MyMultiMap: { { TEXT("Z"), 0.0f }, { TEXT("X"), -10.0f } }
```

You can read more about it on [Unreal's docs](https://docs.unrealengine.com/5.3/en-US/API/Runtime/Core/Containers/TMultiMap/).

> [!WARNING]
> Unreal doesn't support `TMultiMap` with UHT[^3]. Meaning, you can't expose to Blueprint.

#### TStaticArray

An array with a static number of elements.

You cannot add or remove any of the entries of the static array. But you can still alter each element's data.

**Here's an example:**

Include the header file:

```cpp
#include "Containers/StaticArray.h"
```

Declare a `TStaticArray` of `int32` (integers) with 4 elements pre-allocated:

```cpp
// Allocate 4 elements of type 'FVector'
TStaticArray<FVector, 4> StaticArray;

// StaticArray: { (0, 0, 0), (0, 0, 0), (0, 0, 0), (0, 0, 0) }
```

You **CANNOT** use brace initialization with `TStaticArray`:

```cpp
TStaticArray<int32, 4> StaticArray { 1, 2, 3, 4 }; // Won't compile!
```

Update each element's value:

```cpp
StaticArray[0] = FVector::OneVector;
StaticArray[1] = FVector::ZeroVector;
StaticArray[2] = FVector::OneVector;
StaticArray[3] = FVector::ZeroVector;

// StaticArray: { (1, 1, 1), (0, 0, 0), (1, 1, 1), (0, 0, 0) }
```

Get number of elements from the static array:

```cpp
int32 NumOfElements = StaticArray.Num(); // 4
```

Loop through the values and log each one:

```cpp
for (const FVector& Vec : StaticArray)
{
    UE_LOG(LogTemp, Log, TEXT("Value: %s"), *Vec.ToString());
}
```

You can read more about it on [Unreal's docs](https://docs.unrealengine.com/5.3/en-US/API/Runtime/Core/Containers/TStaticArray/).

> [!WARNING]
> Unreal Engine doesn't support `TStaticArray` with UHT[^3]. Meaning, you can't expose to Blueprint. To use a static array with Blueprint, use `FixedSized` specifier for UPROPERTY on `TArray` property.

#### FHashTable

Dynamically sized hash table, used to index another data structure.
Vastly simpler and faster than `TMap`.

**Here's an example:**

Include the header file:

```cpp
#include "Containers/HashTable.h"
```

Define a `FHashTable`:

```cpp
FHashTable HashTable;
```

Add a new hash element to the table:

```cpp
const uint16 Hash = 50u;
const uint16 Index = 10u;

HashTable.Add(Hash, Index);
```

You can read more about it on [Unreal's docs](https://docs.unrealengine.com/5.3/en-US/API/Runtime/Core/Containers/FHashTable/).

#### TStaticHashTable

Statically sized hash table, used to index another data structure.
Vastly simpler and faster than `TMap`.

**Here's an example:**

Include the header file:

```cpp
#include "Containers/HashTable.h"
```

Define a `TStaticHashTable`:

```cpp
static const uint32 Capacity = 16u;
TStaticHashTable<1024u, Capacity> StaticHashTable;
```

Add a new hash element to the table:

```cpp
const uint16 Hash = 50u;
const uint16 Index = 10u;

StaticHashTable.Add(Hash, Index);
```

You can read more about it on [Unreal's docs](https://docs.unrealengine.com/5.3/en-US/API/Runtime/Core/Containers/TStaticHashTable/).

#### TSortedMap

A Map of keys to value, implemented as a sorted `TArray` of TPairs.

It has a mostly identical interface to `TMap` and is designed as a drop in replacement. Keys must be unique, there is no equivalent sorted version of `TMultiMap`. It uses half as much memory as `TMap`, but adding and removing elements is O(n), and finding is O(Log n). In practice it is faster than `TMap` for low element counts, and slower as n increases, This map is always kept sorted by the key type so cannot be sorted manually.

**Here's an example:**

Include the header file:

```cpp
#include "Containers/SortedMap.h"
```

Create a `TSortedMap` of `FName` (names) to `int32` (integers):

```cpp
TSortedMap<FName, int32> MyMap;
```

Add some elements to the map:

```cpp
MyMap.Add(TEXT("One"), 1);
MyMap.Add(TEXT("Two"), 2);
MyMap.Add(TEXT("Three"), 3);
```

Get the value associated with a key:

```cpp
int32 Value = MyMap[TEXT("One")];
```

Check if a key exists in the map:

```cpp
bool Exists = MyMap.Contains(TEXT("One"));
```

Iterate over the map and log each one:

```cpp
for (const TPair<FName, int32>& Element : MyMap)
{
    UE_LOG(LogTemp, Log, TEXT("Key: %s, Value: %i"), *Element.Key.ToString(), Element.Value);
}
```

You can read more about it on [Unreal's docs](https://docs.unrealengine.com/5.3/en-US/API/Runtime/Core/Containers/TSortedMap/).

#### TList

Simple single-linked list template.

It only stores two things:

```cpp
ElementType			Element; // Value
TList<ElementType>* Next; // Pointer to the next node
```

Helpful for scenarios like: Pathfinding, binary tree searching or dialogue tree system.

A linked list have some benefits compare to `TArray`, mainly it has **O(1)** in time complexity, for adding and removing elements in the list. This is because, every node has a pointer to the next node in the list. Thus giving `TList` a time complexity to **O(1)**.

You can read more about [time complexity by Joel Olawanle](https://www.freecodecamp.org/news/big-o-cheat-sheet-time-complexity-chart/).

There is a couple of downsides of using `TList` compare to `TArray`:

<table><tr><td>

Cache misses

When the computer reads the memory, it reads from RAM (Random-access memory). Hence, the name it will access the memory at random location. With `TArray`, your memory allocation contiguous. Meaning, that `TArray` will ask for a big spot to have its memory block.

However, if `TArray` cannot find nor fit a specific spot (as the `TArray` can grow and shrink), it needs to recalculate and find a new spot. Thus making it annoying to add or to remove elements.

But what `TArray` have which a linked list lacks is **cache hits**. Cache hits is a terminology, where the CPU can preload an array into CPU cached memory. Because an array stores in contiguous, allows the CPU to preload the whole array without jumping back and forth in memory location.

With linked lists, there is no contiguous memory. Meaning, the CPU needs to find each node in different location. Which doesn't allow the CPU to cache previous result into its memory. And this called a cache miss.

<figure>
    <img src="static/img/LinkedListMemory.png" alt="Linked List's memory allocation" />
    <figcaption>Image from <a href="https://dhathriblog.medium.com/linked-list-data-structure-dc13fd807096">Dhathri Vupparapalli's blog</a>.</figcaption>
</figure>

Here is a video from [SimonDev about cache misses and hits](https://www.youtube.com/watch?v=247cXLkYt2M).

You can also read more about the [CPU's cache on Wikipedia](https://en.wikipedia.org/wiki/Cache_(computing)).

---

Memory space

`TList` takes up more memory space per each node.

Since every node needs to keep track of the next node in the list. And the next variable is a pointer, which takes up 4 bytes in 32-bit and 8 bytes in 64-bit computers.

And if you just want to use primary data types, such as (`int`, `float`, `double`, `bool` or `char`), then you can just use `TArray` instead. Whilst a `TArray` stores some overhead, it's very minimal overhead.

---

No helper functions

`TList` only offers the data element and the next node (as a pointer variable).

`TList` does **NOT** offer any helper functions for adding or removing a node in the list.

If you wish to have these functions, then you can just use `TLinkedList` instead.

---

Only goes forward

With `TList`, you can only forwards.

This is becuase there is no previous node per node. Meaning, you cannot go backwards in the list.

If you wish to go backwards, then you can just use `TDoubleLinkedList` instead.

</td></tr></table>

**Here's an example:**

Include the header file:

```cpp
#include "Containers/List.h"
```

```cpp
// Create the head of the list with data value of 69
TList<int32> Head(69);

// Create a new node with data 1337 and link it to the head
Head.Next = new TList<int32>(1337);

// Create another node with data 3 and link it to the previous node
Head.Next->Next = new TList<int32>(3);

// Re-assign the data value
Head.Next->Next->Next.Element = 420;

// Print the elements in the linked list
TList<int32>* CurrentNode = &Head;

while (CurrentNode != nullptr)
{
    UE_LOG(LogTemp, Log, TEXT("Element: %i"), CurrentNode->Element);
    CurrentNode = CurrentNode->Next;
}
```

> [!NOTE]
> `TList` doesn't offer an insert nor a remove function for each node. If you wish to use those function, then use `TLinkedList`.

> [!NOTE]
> As a rule of thumb, you should almost always use `TArray`, unless you have specific reasons to use a linked list.

You can read more about it on [Unreal's docs](https://docs.unrealengine.com/5.3/en-US/API/Runtime/Core/Containers/TList/).

#### TLinkedList

Encapsulates a link in a single linked list with constant access time.

This linked list is non-intrusive, i.e. it stores a copy of the element passed to it (typically a pointer)

**Here's an example:**

Include the header file:

```cpp
#include "Containers/List.h"
```

Define a `TLinkedList` of `int32` (integer):

```cpp
TLinkedList<int32> HeadNode;
```

Iterate over the linked list using `TIterator`:

```cpp
for (TLinkedList<int32>::TIterator It(&HeadNode); It; It.Next())
{
    // Get the value at the current position of the iterator
    int32 Value = *It;

    // Log the value.
    UE_LOG(LogTemp, Log, TEXT("Value: %i"), Value);
}
```

You can read more about it on [Unreal's docs](https://docs.unrealengine.com/5.3/en-US/API/Runtime/Core/Containers/TLinkedList/).

#### TDoubleLinkedList

It only stores three things:

```cpp
ElementType            Value;
TDoubleLinkedListNode* NextNode;
TDoubleLinkedListNode* PrevNode;
```

**Here's an example:**

Include the header file:

```cpp
#include "Containers/List.h"
```

Define a `TDoubleLinkedList` of `int32` (integers):

```cpp
TDoubleLinkedList<int32> A;
```

Add node to the head/tail of the list:

```cpp
A.AddHead(69);
A.AddTail(1337);
```

Get the number of elements in the list:

```cpp
int32 NumOfElements = A.Num();
```

Check if the list contains the value 5:

```cpp
bool bContains = A.Contains(5);
```

Find a node with value 1 in the list:

```cpp
TDoubleLinkedList<int32>::TDoubleLinkedListNode* Node = A.FindNode(1);

// Log the value of the found node
if (Node != nullptr)
{
    UE_LOG(LogTemp, Log, TEXT("Value of the node: %i"), Node->GetValue());
}
else
{
    UE_LOG(LogTemp, Log, TEXT("Node with value 1 not found."));
}
```

Get the next node and previous node in the list:

```cpp
TDoubleLinkedList<int32>::TDoubleLinkedListNode* NextNode = Node->GetNextNode();
TDoubleLinkedList<int32>::TDoubleLinkedListNode* PrevNode = Node->GetPrevNode();

// Log the values of the next and previous nodes
if (NextNode != nullptr)
{
    UE_LOG(LogTemp, Log, TEXT("Value of the next node: %i"), NextNode->GetValue());
}
else
{
    UE_LOG(LogTemp, Log, TEXT("Next node is null."));
}

if (PrevNode != nullptr)
{
    UE_LOG(LogTemp, Log, TEXT("Value of the previous node: %i"), PrevNode->GetValue());
}
else
{
    UE_LOG(LogTemp, Log, TEXT("Previous node is null."));
}
```

You can read more about it on [Unreal's docs](https://docs.unrealengine.com/5.3/en-US/API/Runtime/Core/Containers/TDoubleLinkedList/).

#### TQueue

This template implements an unbounded non-intrusive queue using a lock-free linked list that stores copies of the queued items. The template can operate in two modes: Multiple-producers single-consumer (MPSC) and Single-producer single-consumer (SPSC).

The queue is thread-safe in both modes. The `Dequeue()` method ensures thread-safety by writing it in a way that does not depend on possible instruction reordering on the CPU. The `Enqueue()` method uses an atomic compare-and-swap in multiple-producers scenarios.

**Here's an example:**

Include the header file:

```cpp
#include "Containers/Queue.h"
```

Define a `TQueue` of `FHitResult` (hit results):

```cpp
TQueue<FHitResult> MyQueue;
```

Add some elements to the queue:

```cpp
AActor* TargetActor = this;
UPrimitiveComponent* TargetComponent = this;
FVector HitLocation = FVector(900.0f, 0.0f, 500.0f);
FVector HitNormal = FVector(0.0f, 0.0f, 1.0f);

MyQueue.Enqueue(FHitResult(TargetActor, TargetComponent, HitLocation, HitNormal));
MyQueue.Enqueue(FHitResult(nullptr, nullptr, FVector::ZeroVector, FVector::OneVector.GetSafeNormal()));
```

Dequeue the first element in the queue:

```cpp
FHitResult DequeuedElement = MyQueue.Dequeue();
```

Check if the queue is empty:

```cpp
bool IsEmpty = MyQueue.IsEmpty();
```

Iterate over the queue:

```cpp
while (!MyQueue.IsEmpty())
{
    FHitResult HitResult = MyQueue.Dequeue();

    UE_LOG(LogTemp, Log, TEXT("Hit Target: %s"), *HitResult.GetActor()->GetName());
}
```

You can read more about it on [Unreal's docs](https://docs.unrealengine.com/5.3/en-US/API/Runtime/Core/Containers/TQueue/).

#### TArrayView

When you want to reuse an array without copying or referencing the base class, you can use `TArrayView`.

A statically sized view of an array of typed elements. Designed to allow functions to take either a fixed C-style array or a `TArray` with an arbitrary allocator as an argument when the function neither adds nor removes elements.

You can read more about from [Unreal's docs](https://docs.unrealengine.com/5.3/en-US/API/Runtime/Core/Containers/TArrayView/).

Here's an example:

```cpp
#include "Containers/Array.h"
#include "Containers/ArrayView.h"

#include "Algo/ForEach.h"
#include "Algo/Accumulate.h"

int32 SumArray(TArrayView<const int32> ArrayView)
{
    // Sum the array
    return Algo::Accumulate(ArrayView, 0);
}

// Allocates on heap, but returns an array on the stack
TArray<int32> RegularArray = { 1, 2, 3 };

 // Allocates on the stack
TArray<int32, TInlineAllocator<4>> StackAllocatedArray = { 1, 2, 3 };

 // Allocates on the stack
int32 CArray[4] = { 1, 2, 3 };

UE_LOG(LogTemp, Log, TEXT("Sum=%i"), SumArray(RegularArray));

UE_LOG(LogTemp, Log, TEXT("Sum=%i"), SumArray(StackAllocatedArray));

UE_LOG(LogTemp, Log, TEXT("Sum=%i"), SumArray(CArray));
```

> [!WARNING]
> `TArrayView` is a fixed size and independent array. Meaning, it will not affect from its original assignment, nor does it support Add() or Remove() functions.

> [!NOTE]
> It's still possible to use Algo library, which offers functions to use for TArrayView and TArray. Such as Algo::Reverse() and Algo::ForEach().

> [!CAUTION]
> Avoid using `TArrayView` with a temporary array variable. Since, the array can go out of scope and corrupt `TArrayView`. Since the view is relying on the array's memory block.

```cpp
#include "Containers/ArrayView.h"

// Note how to mark an ArrayView const!
void ConstArrayView()
{
    TArray<int32> MutableArray;
    TArrayView<int32> ArrayView = MutableArray;
    TArrayView<const int32> ConstArrayView = MutableArray;

    ArrayView[0] = 1337; // Allowed!
    ConstArrayView[0] = 69; // Compiling error!
}

// Do not create an array view to a temporary variable, as this can cause issues!
void UnsafeArrayView()
{
    // Create Array view with temporary TArray
    TArrayView<const int32> UnsafeArray = TArray<int32> { 1, 2, 3 };

    // This memory block has likely been freed, but the array view doesn't know about it!
    int32 Value = UnsafeArray[0]; // This will cause a crash!
}

// Do not modify the array while the array view is in scope! Array view is independent from the array.
void ModifyArrayView()
{
    TArray<int32> Array { 1, 2, 3 };
    TArrayView<int32> ArrayView = Array;

    int32 PreviousValue = ArrayView[0];

    Array.RemoveAt(0); // Will not update array view!

    int32 NewValue = ArrayView[0];

    bool bIsSame = PreviousValue == NewValue; // Will return true!
}
```

#### String View

`FStringView` is a lightweight, non-owning view of the string data, and copying the view itself is efficient and does not affect the underlying data. However, when you copy the `FStringView`, the new instance of the view still refers to the same original string data.

Same concept with `TArrayView` but with `FString` instead.

Here's an example:

```cpp
#include "Containers/UnrealString.h"

void ProcessString(FStringView StringView)
{
    // Use FStringView to read the string data without copying it.
    UE_LOG(LogTemp, Log, TEXT("String: %s"), *StringView);
}

FString MyString = TEXT("Hello, FStringView!");

// Pass FString as FStringView to the function without copying the data.
ProcessString(MyString);

// Copy FStringView to another variable.
FStringView CopiedStringView = MyString;

// Modifying the original FString does not affect the copied FStringView.
MyString = TEXT("Modified String");

// Print the contents of the copied FStringView.
UE_LOG(LogTemp, Log, TEXT("Copied StringView: %s"), *CopiedStringView);
```

You can read more about it on [Unreal's docs](https://docs.unrealengine.com/5.3/en-US/API/Runtime/Core/Containers/TStringView/).

#### String Builder

When working strings, you might have to concatenate a lot of string together. Sometimes, this can create complex and messy code to read. Whilst, `FString` is **mutable** and allows the developer to alter its data without copy a new instance. A string builder can still be a very helpful tool.

The string builder allocates a buffer space which is used to hold the constructed string. The intent is that the builder is allocated on the stack as a function local variable to avoid heap allocations.

The buffer is always contiguous, and the class is not intended to be used to construct extremely large strings.

This is not intended to be used as a mechanism for holding on to strings for a long time. The use case is explicitly to aid in constructing strings on the stack and subsequently passing the string into a function call or a more permanent string storage mechanism like `FString` et al.

The amount of buffer space to allocate is specified via a template parameter and if the constructed string should overflow this initial buffer, a new buffer will be allocated using regular dynamic memory allocations.

---

**There are two ways to construct a string builder**. Either with initialize buffer size or with unknown buffer size.

**Here's an example:**

Include the header file:

```cpp
#include "Containers/StringFwd.h"
```

To create a string builder with an unknown buffer size:

```cpp
FStringBuilderBase StringBuilder; // Note! This is using a regular dynamic memory allocation.
```

To create a string builder with initialize buffer size:

```cpp
int32 BufferSize = 12; // 12 characters of TCHAR
TStringBuilder<BufferSize> StringBuilder;
```

Append characters to the string builder:

```cpp
StringBuilder.Appendchar('H');
StringBuilder.Appendchar('e');
StringBuilder.Appendchar('l');
StringBuilder.Appendchar('l');
StringBuilder.Appendchar('o');
StringBuilder.Appendchar(',');
StringBuilder.Appendchar(' ');
StringBuilder.Appendchar('W');
StringBuilder.Appendchar('o');
StringBuilder.Appendchar('r');
StringBuilder.Appendchar('l');
StringBuilder.Appendchar('d');

// StringBuilder: { 'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd' }
```

In order to get the string either call `ToString()` or `ToView()` functions:

```cpp
FString Str = StringBuilder.ToString();
FStringView StrView = StringBuilder.ToView();
```

You can also append a string as well:

```cpp
// Note! The string builder will allocate more memory, if necessary.

// We only allocated 12 characters, and this call will make it go over bound.
// Causing to allocate more memory on heap.
StringBuilder.Append(TEXT(" and welcome!"));

// StringBuilder: { 'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', ' ', 'a', 'n', 'd', ' ', 'w', 'e', 'l', 'c', 'o', 'm', 'e', '!' }
```

> [!WARNING]
> The string builder will allocate more memory, if necessary.

Here's an another example:

```cpp
TStringBuilder<256> MessageBuilder;

float PlayerHealth = 110.5285f;
MessageBuilder << TEXTVIEW("Player's health: ") << FString::SanitizeFloat(PlayerHealth);

return FString { MessageBuilder };
```

You can read more about it on [Unreal's docs](https://docs.unrealengine.com/5.3/en-US/API/Runtime/Core/Containers/TStringBuilderBase/).

#### TEnumAsByte

Template to store enumeration values as bytes in a type-safe way.

**Here's an example:**

Include the header file:

```cpp
#include "Containers/EnumAsByte.h"
```

Declare a `TEnumAsByte` with the enumeration type `ECollisionChannel`:

```cpp
TEnumAsByte<ECollisionChannel> Channel;
```

Get the value of the `TEnumAsByte`:

```cpp
ECollisionChannel Val = Channel.GetValue();
```

Get the integer value of the `TEnumAsByte`:

```cpp
int32 IntVal = Channel.GetIntValue();
```

Assign a new value to the `TEnumAsByte`

```cpp
Channel = ECollisionChannel::ECC_Camera;
```

Log the values:

```cpp
UE_LOG(LogTemp, Log, TEXT("Value of the: %i"), UEnum::GetValueAsName(Val));
UE_LOG(LogTemp, Log, TEXT("Integer value of the: %i"), IntVal);
```

> [!NOTE]
> That regular enums are supported by `UPROPERTY` and replaces the need of using `TEnumAsByte` anymore.

You can read more about it on [Unreal's docs](https://docs.unrealengine.com/5.3/en-US/API/Runtime/Core/Containers/TEnumAsByte/).

### 🧨 Value type vs Reference type

<table><tr><td>
This section was written in conjunction with ChatGPT.
</td></tr></table>

Let's talk about what value type and reference types.

In various programming languages like Python[^11], Java[^13], and C#[^12], you may have encountered both value types and reference types.

A value type creates a copy when initialized from another variable. For instance, let's consider variable A, and when we initialize variable B with the value of A, a separate copy of the value is created in B. Essentially, B is an independent entity that holds its own value.

```cpp
int A = 69;
int B = A; // A copy
```

On the other hand, a reference type directly references the memory location of the variable. In this case, when variable B is initialized by variable A, B becomes a reference to the same memory location as A. Consequently, any changes made to B will also affect A since B essentially points to the same underlying value as A.

```cpp
int A = 69;
int& B = A; // A reference
```

Everything in C++ is value type by default. Even classes, which differ from C#[^12].

You can watch this video about [references in C++ from Low Level Learning](https://www.youtube.com/watch?v=wro8Bb6JnwU).

Here's an example:

```cpp
// Test struct and class
struct Coords
{
    // Constructor: Initialize X and Y with given values
    Coords(int x, int y) : X(x), Y(y) {}

public:
    int X; // X coordinate
    int Y; // Y coordinate

public:
    // Return a string representation of this Coords struct
    std::string toString() const
    {
        // Use stringstream to concatenate strings
        std::stringstream ss;
        ss << "(" << X << ", " << Y << ")";
        return ss.str();
    }
};

int main()
{
    Coords A(1, 2); // Create struct A
    Coords& B = A; // B is a reference to A
    Coords* C = &B; // C is a pointer to A
    Coords* D = new Coords(5, 10); // Create a new Coords struct with new
    Coords* E = &(*C); // E is a pointer to what C points to

    B.X = 69; // Modify X of A through B
    C->Y = 1337; // Modify Y of A through C
    D->Y = D->Y * 2; // Modify Y of dynamically allocated struct

    E = &*D; // Make E point to what D points to
    E->X = 10; // Modify X of dynamically allocated struct

    // Print statements
    std::cout << A.toString() << std::endl;
    std::cout << B.toString() << std::endl;
    std::cout << C->toString() << std::endl;
    std::cout << D->toString() << std::endl;
    std::cout << E->toString() << std::endl;

    delete D; // Deallocate memory of dynamically allocated struct

    return 0;
}
```

With references, you can only assign them once, and they cannot be changed throughout the code. For example, you can have a direct reference to an argument passed into a function. This argument can then be modified within the function, similar to how an [out](https://learn.microsoft.com/en-us/dotnet/csharp/language-reference/keywords/out-parameter-modifier) parameter works in C#[^12].

Here's an example:

```cpp
bool DamageHealth(int& Health)
{
   Health -= 100; // Modifying the value through the reference
   return Health <= 0;
}

int PlayerHealth = 100;

if (DamageHealth(PlayerHealth)) // Passing the `PlayerHealth` as a direct reference
{
   // Player just died!
}
```

### 👈 Pointers

<table><tr><td>
This section was written in conjunction with ChatGPT.
</td></tr></table>

![Pointers](static/img/Pointers.png)

And lastly, we have pointers. This section, will go over about raw pointers and smart pointers. If you have no clue about pointers, highly recommend watching [Cherno about pointers](https://www.youtube.com/watch?v=DTxHyVn0ODg).

Pointers and references are similar in that they both refer to variables, but there's one key difference. Pointers are **indirect references**, meaning they can change throughout the code, pointing to different variables. On the other hand, regular references are **direct** and can only **refer to the specific variable** they were initialized with.

_In a short summary, a pointer is like writing down the address of a building on a piece of paper. The address on the paper tells you where the building is located, just as the memory address stored in the pointer variable tells you where a variable is located in memory. Similarly, you can also pass the address on the paper to someone else, allowing them to find the building too, just as you can pass a pointer variable to a function or another part of your code, allowing it to access the variable in memory._

Pointers are valuable tools in programming as they allow us to store memory addresses, enabling dynamic memory allocation and manipulation of data structures. By using pointers, we can create more flexible and efficient code that can adapt to changing data requirements during program execution.

Additionally, pointers are essential in scenarios like data structures, linked lists, and passing data to functions by reference, providing a level of control and precision that enhances the capabilities of the program. However, **it's important to handle pointers with care**, as incorrect usage can lead to **memory leaks** or **segmentation faults**.

#### 🦴 Raw pointers

A raw pointer can be sometime dangerous, because there is no validation when accessing this pointer. And when the pointer is pointing to nothing (meaning, the pointer is a `nullptr`). The program will throw a null pointer exception, also known as a segmentation fault (segfault).

A segmentation fault occurs when a program tries to access a memory location that it does not have permission to access, which can happen when the program tries to dereference a null pointer. When this happens, the operating system will usually terminate the program and generate an error message.

You can read more about [raw pointers from Microsoft Learn](https://learn.microsoft.com/en-us/cpp/cpp/raw-pointers?view=msvc-170).

To avoid this, you must check before if the pointer is valid, before using it.
> Use the function called `IsValid()` for raw pointers.

Here's an example:

```cpp
UPROPERTY()
AActor* ActorPtr = nullptr;

// Use UPROPERTY() macro, in order to tell the UHT (Unreal Header Tool), this pointer must be release into GC (garbage collector).
// If not, then this will cause a memory leak. Meaning, the pointer is still alive, even tough we are not using this memory block.

void KillActor()
{
  // IsValid() function also check if the pointer is not already destroyed by the GC (garbage collector).

  if (!IsValid(ActorPtr)) // The pointer has value of 'nullptr', therfore is NOT valid!
      return;

  ActorPtr->Destroy();
}
```

> [!NOTE]
`ActorPtr` is marked with `UPROPERTY()`in order to tell UHT[^3], that this pointer exists. When the pointer is unused, the garbage collector then marks it and deletes its memory. Also note, that this process can take a couple frames and is not instantaneously. Therefore, always use `IsValid()` function, which also checks if the pointer is not marked for the garbage collector. Avoid using manual checking, like this: `PlayerCharacter != nullptr` (since it will not work with GC system).

> [!WARNING]
> If something else is referencing `ActorPtr`, the pointer will not be destroyed via garbage collection (unless if it's a weak pointer).

After Unreal Engine (**5.0**) version, is now recommending to use `TObjectPtr` instead of `*` to mark raw pointers. `TObjectPtr` class contains some optimization for the editor.

Here is the updated code:

```cpp
UPROPERTY()
TObjectPtr<AActor> ActorPtr = nullptr;
```

#### 🤖 Smart pointers library

In Unreal Engine, the Smart Pointer's library provides a set of template classes to manage memory and object ownership more efficiently and safely. These smart pointers automatically handle memory management, such as allocating and deallocating memory, and help prevent memory leaks and null pointer dereferences.

The key smart pointers in Unreal Engine's library include `TSharedPtr`, `TWeakPtr`, and `TUniquePtr`. They are designed to handle various ownership scenarios and provide a safer alternative to raw pointers.

You can read more about [Unreal Smart Pointer Library on their docs](https://docs.unrealengine.com/5.2/en-US/smart-pointers-in-unreal-engine/).

##### TSharedPtr

`TSharedPtr` is a smart pointer that manages shared ownership of a dynamically allocated object. It uses reference counting to keep track of the number of shared references to the object and automatically releases the memory when the last reference goes out of scope.

Example:

```cpp
TSharedPtr<int32> sharedPtr = MakeShared<int32>(42);
```

##### TWeakPtr

`TWeakPtr` is a smart pointer that represents a weak reference to a dynamically allocated object. It allows accessing the object as long as it exists but does not affect the object's reference count. It is commonly used to avoid circular reference issues.

Example:

```cpp
TSharedPtr<int32> sharedPtr = MakeShared<int32>(42);
TWeakPtr<int32> weakPtr = sharedPtr;
```

##### TUniquePtr

`TUniquePtr` is a smart pointer that represents sole ownership of a dynamically allocated object. It ensures that only one pointer can own the object, and when the owning `TUniquePtr` goes out of scope, the memory is automatically deallocated.

Example:

```cpp
TUniquePtr<int32> uniquePtr = MakeUnique<int32>(42);
```

#### 🤖 Smart `UObject` pointers

Unreal Engine's Smart Pointers, such as `TSharedPtr`, `TWeakPtr`, and `TUniquePtr`, are generic smart pointers that can be used with any C++ classes or types, not limited to Unreal Engine's UObject-derived classes.

On the other hand, UObject Smart Pointers are specific to Unreal Engine's UObject-derived classes. These smart pointers, such as `TWeakObjectPtr`, `TWeakInterfacePtr`, `TSoftObjectPtr` and `TSoftClassPtr`, are designed to handle `UObject` ownership and management within the Unreal Engine ecosystem.

##### TWeakObjectPtr

This smart pointer is used to hold a weak reference to an `UObject` subclass. It allows you to safely reference an object without affecting its lifespan. It is commonly used to prevent strong references that could potentially create circular dependencies.

Example usage:

```cpp
TWeakObjectPtr<UObject> WeakPtr;

if (SomeObject.IsValid())
{
    WeakPtr = SomeObject;  // Assign weak reference to an object
}

if (WeakPtr.IsValid())
{
    // Access the object if it still exists
    WeakPtr->DoSomething();
}
```

##### TWeakInterfacePtr

This smart pointer is used to hold a weak reference to an interface implemented by an `UObject`. It allows you to safely reference the interface without affecting its lifespan.

Example usage:

```cpp
TWeakInterfacePtr<IMyInterface> WeakPtr;

if (SomeObject->Implements<IMyInterface>())
{
    WeakPtr = SomeObject;  // Assign weak reference to the interface
}

if (WeakPtr.IsValid())
{
    // Access the interface if the object still implements it
    WeakPtr->InterfaceFunction();
}
```

##### TSoftObjectPtr

This smart pointer is used to hold a soft reference to an `UObject` subclass. It is used for referencing assets that can be loaded and unloaded during runtime. Soft references do not prevent the asset from being garbage collected.

![TSoftObjectPtr](static/img/TSoftObjectPtr+BP.png)

Example usage:

```cpp
TSoftObjectPtr<UTexture2D> SoftPtr; // Assign soft reference to a texture asset

if (SoftPtr.IsValid())
{
    UTexture2D* Texture = SoftPtr.LoadSynchronous(); // This will cause a lag spike (if the asset is heavily chained or large in size)

    if (Texture)
    {
        // Use the loaded texture
    }
}
```

Asynchronous Solution:

```cpp
TSoftObjectPtr<UTexture2D> SoftPtr; // Assign soft reference to a texture asset

if (SoftPtr.IsValid())
{
    OnTextureLoadedDelegate.BindLambda([]()
    {
        // Called when the texture is loaded and ready to use
        UTexture2D* Texture = SoftPtr.Get();

        if (Texture)
        {
            // Use the loaded texture as needed
        }
    });

    StreamableManager.RequestAsyncLoad(SoftPtr.ToSoftObjectPath(), OnTextureLoadedDelegate);
}
```

> [!WARNING]
> Don't use `FSoftObjectPath` or `FSoftObjectPtr`. Used for internal purpose.

##### TSoftClassPtr

This smart pointer is used to hold a soft reference to a `UClass` subclass. It is used for referencing blueprint classes or other classes that can be loaded and unloaded during runtime.

![TSoftClassPtr](static/img/TSoftClassPtr+BP.png)

Example usage:

```cpp
TSoftClassPtr<AMyBlueprintClass> SoftPtr; // Assign soft reference to a blueprint class

if (SoftPtr.IsValid())
{
    UClass* Class = SoftPtr.LoadSynchronous(); // This will cause a lag spike (if the asset is heavily chained or large in size)

    if (Class)
    {
        // Use the loaded class
    }
}
```

Asynchronous Solution:

```cpp
TSoftClassPtr<AMyBlueprintClass> SoftPtr; // Assign soft reference to a blueprint class

if (SoftPtr.IsValid())
{
    OnBlueprintLoadedDelegate.BindLambda([]()
    {
        // Called when the blueprint class is loaded and ready to use
        UClass* BlueprintClass = SoftPtr.Get();

        if (BlueprintClass)
        {
            // Use the loaded blueprint class as needed
            AMyBlueprintClass* NewActor = GetWorld()->SpawnActor<AMyBlueprintClass>(BlueprintClass);

            if (NewActor)
            {
                // Successfully spawned the actor based on the loaded blueprint class
            }
        }
    });

    StreamableManager.RequestAsyncLoad(SoftPtr.ToSoftObjectPath(), OnBlueprintLoadedDelegate);
}
```

> [!WARNING]
> Don't use `FSoftClassPath`. Legacy code.

---

| Smart Pointer      | Type Based On      | Description                                                |
|--------------------|--------------------|------------------------------------------------------------|
| TSharedPtr         | Regular C++ Classes | Shared pointer for managing ownership of dynamically allocated objects. Allows multiple pointers to share ownership. |
| TWeakPtr           | Regular C++ Classes | Weak pointer for non-owning references to dynamically allocated objects. |
| TUniquePtr         | Regular C++ Classes | Unique pointer for exclusive ownership of dynamically allocated objects. Ensures only one pointer owns the object. |
| TWeakObjectPtr     | UObject Classes    | Weak pointer for non-owning references to UObject-derived objects. |
| TWeakInterfacePtr  | UObject Classes    | Weak pointer for non-owning references to objects implementing a specific interface. |
| TSoftObjectPtr     | UObject Classes    | Soft pointer for non-owning references to UObject-derived objects. Allows loading the object when needed, but won't prevent it from being garbage collected. |
| TSoftClassPtr      | UObject Classes    | Soft pointer for non-owning references to UClass-derived objects. Allows loading the class when needed, but won't prevent it from being garbage collected. |

</details>

<!-- prettier-ignore-end -->

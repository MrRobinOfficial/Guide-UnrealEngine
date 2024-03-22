## ⚓ Naming Convention

<table><tr><td>
This section was written in conjunction with ChatGPT.
</td></tr></table>

![Naming Conventions](static/img/Naming_conventions.png)

There is a github repo, which talks about Unreal's naming convention. The repo is very detailed and explains how you should name your assets, as well as your code. Repo is called [Unreal Engine's style guide by Michael Allar](https://github.com/Allar/ue5-style-guide).

You can read more about [Epic C++ Coding Standard on their docs](https://docs.unrealengine.com/5.3/en-US/epic-cplusplus-coding-standard-for-unreal-engine/).

Unreal Engine follows a specific naming convention that helps maintain consistency and readability in the codebase. When using Naming Conventions, all code and comments should use U.S. English spelling and grammar.

Pascal case is a naming convention used in programming and other contexts where compound words or phrases are created by capitalizing the first letter of each word and joining them without spaces. In Unreal Engine, pascal case is commonly used for naming classes, member variables, functions, and other constructs.

In Unreal Engine, the use of pascal case for classes is part of the naming convention for user-defined classes. When you create a new class in Unreal Engine, it is recommended to use pascal case for the class name. For example:

```cpp
class AMyPlayerCharacter : public ACharacter
{
    // Class definition here
};
```

Similarly, pascal case is used for member variables and functions in Unreal Engine to maintain consistency and improve code readability. For example:

```cpp
class AMyPlayerCharacter : public ACharacter
{
public:
    UPROPERTY()
    float MovementSpeed;

    UFUNCTION()
    void Jump();
};
```

Boolean variables, which uses a prefix of `b` followed by a descriptive name in pascal case.
For example, a boolean variable that controls whether a character is running might be named: `bIsRunning`.

Variable, method, and class names should be:

-   Clear
-   Unambiguous
-   Descriptive

The greater the scope of the name, the greater the importance of a good, descriptive name. Avoid over-abbreviation.

```cpp
// what does true mean?
bool CheckTea(FTea Tea);

// name makes it clear true means tea is fresh
bool IsTeaFresh(FTea Tea);
```

Enumerated (Enum) classes are a replacement for old-style namespaced enums, both for regular enums and `UENUMs`. For example:

```cpp
// Old enum
UENUM()
namespace EThing
{
    enum Type
    {
        Thing1,
        Thing2
    };
}

// New enum
UENUM()
enum class EThing : uint8
{
    Thing1,
    Thing2
}
```

Enums are supported as `UPROPERTYs`, and replace the old `TEnumAsByte<>` workaround. Enum properties can also be any size, not just bytes:

```cpp
// Old property
UPROPERTY()
TEnumAsByte<EThing::Type> MyProperty;

// New property
UPROPERTY()
EThing MyProperty;
```

### Prefixes

<table><tr><td>
This section was NOT written in conjunction with ChatGPT.
</td></tr></table>

| Prefix | Class        | Subclasses                                                            |
| ------ | ------------ | --------------------------------------------------------------------- |
| U      | `UObject`    | `UActorComponent`, `UPrimaryDataAsset`, `UEngine`, `UGameplayStatics` |
| A      | `AActor`     | `APawn`, `ACharaacter`, `AController`, `AHUD`, `AGameMode`            |
| F      | Struct       | `FHitResult`, `FVector`, `FRotator`, `FTableRowBase`                  |
| E      | Enum         | `EEnvQueryStatus`, `EConstraintType`, `EEndPlayReason`                |
| I      | Inteface     | `IInputDevice`, `IHapticDevice`, `ITargetPlatform`                    |
| T      | Template     | `TSubclassOf<T>`, `TArray<T>`, `TSet<T>`, `TMap<T>`, `TMultiMap<T>`   |
| G      | Global Class | `GEngine`, `GConfig`, `GWorld`, `GEngineLoop`, `GIsEditor`            |

> [!TIP]
> Did you know that `F` prefix actually stands for `Float` (floating point). but it was inadvertently spread throughout and has lost its original meaning.

### 🎨 Abbreviations, Acronyms and Synonyms

<table><tr><td>
This section was written in conjunction with ChatGPT.
</td></tr></table>

<table><tr><td>

Common Language features

-   `arg` = Argument
-   `arr` = Array
-   `async` = Asynchronous
-   `attr` = Attribute
-   `auth` = Authentication

-   `btn` = Button
-   `buff` = Buffer

-   `ctx` = Context
-   `const` = Constant

-   `db` = Database
-   `dest` = Destination
-   `desc` = Description
-   `doc` or `docs` = Documentation
-   `dir` = Direction or Directory (depending on the context)

-   `elem` = Element
-   `err` = Error
-   `e` or `evt` = Event
-   `exe` = Execution
-   `expr` = Expression
-   `ext` = Extension

-   `func` = Function
-   `fmt` = Format

-   `gen` = Generation

-   `hex` = Hexadecimal

-   `impl` = Implementation
-   `imp` = Import
-   `i` or `idx` = Index
-   `info` = Information
-   `init` = initialization
-   `it` or `iter` = Iterator
-   `ident` = Identifier

-   `lang` = Language
-   `len` = Length
-   `lvl` = Level
-   `lib` = Library
-   `loc` = Location

-   `msg` = Message

-   `num` = Number

-   `obj` = Object
-   `opt` = Option
-   `out` = Output

-   `pkg` = Package
-   `param` = Parameter
-   `px` = Pixel
-   `pos` = Position
-   `prev` = Previous
-   `priv` = Private
-   `pub` = Public

-   `q` = Query

-   `rand` = Random
-   `rng` = Range
-   `ref` = Reference
-   `rm` or `rmv` = Remove
-   `req` = Request
-   `res` = Result or Response (depending on the context)
-   `ret` = Return

-   `sel` = Selection
-   `sep` = Separator
-   `sec` = Sequence
-   `sol` = Solver
-   `src` = Source
-   `spec` = Specifier or Specification (depending on the context)
-   `std` = Standard
-   `stdio` = Standard Input Output
-   `stmt` = Statement
-   `stat` = Statistic
-   `str` = String
-   `sync` = Synchronization

-   `tmp` = Temperature
-   `temp` = Temporary

-   `util` = Utility

-   `val` = Value
-   `var` = Variable

-   `ws` = White space
-   `win` = Windows
-   `wiz` = Wizard

---

Unreal Engine features

-   `PC` - Indicates that a variable is a **PlayerController**
-   `LP` - Indicates that a variable is a **LocalPlayer**
-   `Char` = Indicates that a variable is a **Character** (not to be confused about `char` data type)
-   `Comp` - Indicates that a variable is a **component**
-   `Ptr` - Indicates that a variable is a **pointer** to an object.
-   `Ref` - Indicates that a variable is a **reference** to an object.
-   `dt` = Delta Time

---

Networking

-   `OAuth` or Open Authentication – An open standard for authenticating applications or websites to access the content.
-   `TCP` or Transmission Control Protocol – A standard defining how to exchange messages between systems.
-   `UDP` or User Datagram Protocol – A standard defining how to exchange messages between systems.

---

Tools/Frameworks

-   `IDE` or Integrated Development Environment - A software application that provides facilities to programmers for software development.
-   `JSON` or Javascript Object Notation – A file format, written with JavaScript[^14] notation, used widely for transferring data over the network.
-   `XML` or Extensible Markup Language – A markup language used mainly for storing and transporting data.
-   `SQL` or Structured Query Language – A query language for storage, retrieval, and modification of data.
-   `CSV` or Comma-separated values - A CSV file is a delimited text file that uses a comma to separate values.

---

Math

-   `add` Addition
-   `sub` Subtraction
-   `mul` Multiplication
-   `div` Division
-   `abs` Absolute
-   `sin` Sinus
-   `cos` Cosinus
-   `tan` Tangens
-   `rad` Radian
-   `r` Radius

-   `frac` Fraction
-   `freq` Frequency
-   `long` Longitude or Longitudinal (depending on the context)
-   `lat` Latitude or Lateral (depending on the context)

-   `sqrt` Square Root
-   `mod` Modulo
-   `min` Minimum
-   `max` Maximum
-   `lerp` Linear Interpolation

---

Misc

-   `API` or Application Programming Interface – An interface for connecting multiple isolated components.
-   `SDK` or Software Development Kit – A collection of software often needed for development in a specific platform.
-   `TDD` or Test-driven development - TDD is a software development process that is based on the repetition of a short development cycle: requirements are turned into specific test cases, and then the code is fixed so that the tests pass.
-   `UUID` or Universally unique identifier - A UUID is a 128-bit number used to identify information in computer systems.
-   `GUI` or Graphic User Interface - A GUI or graphical user interface is a form of user interface that allows users to interact with electronic devices through a graphical interface.
-   `misc` = Miscellaneous
-   `os` = Operating System
-   `org` = Organization
-   `pwr` = Power
-   `pref` = Preference
-   `repo` = Repository

</td></tr></table>

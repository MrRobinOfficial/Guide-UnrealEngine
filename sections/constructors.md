## 👷 Constructors, destructors and initialization

<table><tr><td>
This section was written in conjunction with ChatGPT.
</td></tr></table>

#### Constructors

Constructors are special member functions in C++ that are automatically called when an object is created. They are used to initialize the object's data members and set up its initial state. Constructors have the same name as the class and can be overloaded to take different sets of parameters, allowing for object initialization in various ways.

Here's an example:

```cpp
/**
 * This is a simple C++ class that demonstrates how to define a constructor.
 * Constructors are special member functions in C++ that are automatically
 * called when an object is created. They are used to initialize the object's
 * data members and set up its initial state.
 *
 * In Unreal Engine, you can define constructors and destructors in C++ classes
 * just like in standard C++. Constructors are useful for initializing
 * properties and setting up components when an object is created, while
 * destructors can be used for cleanup tasks like releasing resources or
 * stopping background processes when an object is destroyed.
 *
 * NOTE; Don't clean up UObject memory! As Unreal's garbage collector does this for you. Interfering with Unreal's GC can cause issue and even crashes.
 */
class RegularClass
{
    RegularClass()
    {
        // This constructor is called automatically,
        // when an instance of RegularClass is created.

        // It is used to initialize the object's data members,
        // and set up its initial state.
    }
};
```

#### Destructors

Destructors are another type of special member function in C++ that is automatically called when an object is destroyed or goes out of scope. They are used to perform cleanup tasks, release resources, and deallocate memory allocated during the object's lifetime. Like constructors, destructors have the same name as the class, preceded by a tilde (<kbd>~</kbd>).

Here's an example:

```cpp
/**
 * The destructor is a special member function in C++ that is automatically called
 * when an object is destroyed or goes out of scope. It is used to perform cleanup
 * tasks, release resources, and deallocate memory allocated during the object's
 * lifetime.
 *
 * In Unreal Engine, it is generally advised not to use destructors explicitly
 * for memory cleanup. Instead, Unreal Engine provides other mechanisms, such as
 * `BeginDestroy` and `EndPlay`, to handle object cleanup and resource release when
 * an object is destroyed or removed from the game world.
 */
class RegularClass
{
public:

    ~RegularClass()
    {
        // Destructor called when an instance of RegularClass is destroyed.
        // Or goes out of scope (curly brackets).
    }
};
```

#### Constructors and destructors in UE

In Unreal Engine, you can define constructors and destructors in C++ classes just like in standard C++. Constructors are useful for initializing properties and setting up components when an object is created, while destructors can be used for cleanup tasks like releasing resources or stopping background processes when an object is destroyed.

However, Unreal Engine has its own garbage collection system that automatically manages memory and deallocation of objects. This means that using destructors for memory deallocation or resource cleanup may interfere with the garbage collection process and lead to unexpected behavior or crashes.

Due to the automatic garbage collection in Unreal Engine, it is generally advised not to use destructors explicitly for memory cleanup. Instead, Unreal Engine provides other mechanisms, such as `BeginDestroy` and `EndPlay`, to handle object cleanup and resource release when an object is destroyed or removed from the game world.

Here's an example:

```cpp
#include "MyActor.h"

#include "GameFramework/Actor.h"
#include "GameFramework/MovementComponent.h"

AMyActor::AMyActor()
{
    // Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    // This is the default constructor for an Actor class in Unreal Engine.
    // You can initialize properties and set up components here.

    RootComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(RootComponent);
    MeshComponent->bCastDynamicShadow = false;

    checkf(MeshComponent, TEXT("MeshComponent cannot be a nullptr!"));
    verifyf(MeshComponent, TEXT("MeshComponent cannot be a nullptr!"));
    ensureMsgf(MeshComponent, TEXT("MeshComponent cannot be a nullptr!"));

    // Cast<T> has to be used for *UObjects* due to type safety; it will return *nullptr* in case of a failure in comparison with *StaticCast()*. StaticCast is just a wrapper to *static_cast* function.
    if (UMovementComponent* MeshAsMovementComponent = Cast<UMovementComponent>(MeshComponent))
    {
        // Cast worked!

        MeshAsMovementComponent->bSnapToPlaneAtStart = true;
    }

    UStaticMeshComponent* RootAsActorComponent = CastChecked<UActorComponent>(RootComponent); // Cast must work, otherwise a crash will occur.
}

void AMyActor::BeginPlay()
{
    Super::BeginPlay();

    // This function is automatically called when the actor is spawned or added to the world.
    // You can perform any necessary setup or initialization here.
}

void AMyActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    // This function is automatically called when the actor is removed from the world or destroyed.
    // You can perform cleanup and resource release here.

    Super::EndPlay(EndPlayReason);
}
```

#### Initialization

In C++, initialization refers to the process of assigning an initial value to a variable when it is declared. Initialization is crucial because it ensures that variables have well-defined starting values, which can help avoid unexpected behavior and improve code clarity.

Here's a code snippet that demonstrates:

```cpp
// Initialization using assignment statement
int num1 = 10;

// Initialization using brace initializer
int num2{20};
```

There is an **important** difference when using brace initializer, especially in cases where narrowing conversions are involved. A narrowing conversion occurs when a value is assigned to a variable that has a smaller range than the provided value. For example:

```cpp
int num3 = 1000;       // OK, no narrowing conversion
int num4 = 1000.5;     // OK, narrowing conversion from double to int
int num5{1000.5};      // Error, narrowing conversion from double to int
```

In the last line, using brace initializer, the compiler will generate an error because it detects a narrowing conversion from `double` to `int`, which could potentially lead to data loss. This is a safety feature to help catch unintended data truncation.

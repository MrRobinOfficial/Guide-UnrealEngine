### 🔖 Keywords

In C++, a keyword is a [reserved word](https://en.wikipedia.org/wiki/Reserved_word) that has a special meaning to the compiler. Keywords cannot be used as the names of variables, functions, or any other identifiers in your code.

The keywords in C++ are used to define the structure and behavior of your program. They are used to declare variables, functions, classes, and other types of identifiers. They also control the flow of execution of your program, such as with the `if`, `for`, and `switch` statements.

#### Constants

-   `const` - Specifies that an object or member is read-only and cannot be modified. Meaning, they are immutable.

-   `constexpr` - Specifies that a function or member can be evaluated at compile-time. `constexpr` can be used for inlining variables, without using macros[^4]. **NOTE**, the compiler does not guarantee compile-time evaluation (only it **CAN** be evaluated at compile-time).

-   `consteval` - Specifies that a function must be evaluated at compile-time. **NOTE**, it works only on functions and the compiler has to evaluated at compile-time.

-   `constinit` - Specifies that a variable should be initialized only with constant expressions.

```cpp
int Add(const int& a, const int& b)
{
    a++; // Compiling error!
    return a + b;
}
```

```cpp
// Will be compiled at runtime
const float PI = 3.14f;

// Can be compiled at compile-time
constexpr double PI_DOUBLE = 3.14159265359;
```

You can also use `constexpr` keyword for a function, which then can be directly used inside other operations as well (as it can be compiled at compile-time):

What is the difference between a `constexpr` and macro then?

> A macro doesn't give you any protection against syntax incorrectness, nor any highlighting support for the code. Meaning, is more dangerous to track down bugs and issue, as well as maintaining the code. Therefore, it is more recommend to use `constexpr` keyword for members and functions, which will generated a "truly" constant value.

```cpp
constexpr int getSizeOfAnArray()
{
    return 5;
}

int array[getSizeOfAnArray()]; // array has 5 elements
```

> [!NOTE]
> If you want a "truly" constant value at compile-time with no expectations from the compiler, you can use `consteval` keyword instead. This forces the compiler to compile your code at compile-time.

```cpp
consteval int getSizeOfAnArray()
{
    return 10;
}

int array[getSizeOfAnArray()]; // array has 10 elements

// Will be compiled at compile-time
// NOTE! It is also context-sensitive.
constinit int sizeOfAnArray = getSizeOfAnArray();
```

> [!WARNING]
> The `consteval` and `constinit` keywords are only supported on C++ version 20. Meaning, if your compiler doesn't support, you can't use these keywords.

> [!NOTE]
> Unreal Engine is now supporting [C++ version 20](https://dev.epicgames.com/documentation/en-us/unreal-engine/epic-cplusplus-coding-standard-for-unreal-engine#modernc++languagesyntax:~:text=Unreal%20Engine%20compiles%20with%20a%20language%20version%20of%20C%2B%2B20%20by%20default%20and%20requires%20a%20minimum%20version%20of%20C%2B%2B17%20to%20build.).

```cpp
// Example of using constinit keyword
struct Data
{
    constinit const int i = 10;
    constinit static int j = 20;
};

static_assert(Data::j == 20);
```

Here is a video, explaining what [constants keywords does in C++ by Cazz](https://www.youtube.com/watch?v=KBny6MZJR64)

#### Access modifiers

-   `public` - The member is accessible from any code that can see the class.
-   `protected` - The member is accessible from the class in which it is declared, and from any derived classes.
-   `private` - The member is only accessible from within the class where it is declared.

Here's an example implementation of access modifiers:

```cpp
class VehicleBase
{
public:
    int public_member = 10;

protected:
    int protected_member = 20;

private:
    int private_member = 30;
};

class Car : public VehicleBase
{
    public:
        void Access()
        {
            std::cout << "public_member: " << public_member << std::endl;
            std::cout << "protected_member: " << protected_member << std::endl;
            std::cout << "private_member: " << private_member << std::endl; // Will not compile
        }
};

int main()
{
    VehicleBase vehicle;
    std::cout << "public_member: " << vehicle.public_member << std::endl;
    std::cout << "protected_member: " << vehicle.protected_member << std::endl; // Will not compile
    std::cout << "private_member: " << vehicle.private_member << std::endl; // Will not compile

    Car car;
    car.Access();

    return 0;
}

```

#### Class, struct and memory

-   `class` and `struct` - Used to define user-defined types that encapsulate data and functions. In regular C++, both `class` and `struct` are both the same thing. Exposes `struct` exposes members are public by default.
-   `new` - Allocates memory for an object (on the [heap memory](https://en.wikipedia.org/wiki/Memory_management#HEAP)) and calls its constructor.
-   `delete` - Deallocates memory that was allocated with `new` keyword.

```cpp
/**
 * Struct to represent a person.
 */
struct Person
{
    /** The person's name. */
    std::string name;

    /** The person's age. */
    int age;
};

// Allocate memory for a Person object and initialize its members.
Person* person = new Person;
person->name = "John Doe";
person->age = 30;

// Print out the person's name and age.
std::cout << "Name: " << person->name << std::endl;
std::cout << "Age: " << person->age << std::endl;

// Deallocate memory for the Person object.
delete person;
```

> [!CAUTION]
> In Unreal Engine, it's recommended to use the built-in memory management functions like `NewObject()` and `MakeShared()` to allocate memory for objects, rather than using `new` and `delete`. Using `new` and `delete` can interfere with the garbage collector and cause memory leaks or crashes in your game.

What is the difference between a class and struct then?

> In native C++, the main difference between a struct and a class is that struct members are public by default, whereas class members are private by default. However, this difference is largely syntactic, and struct and class can be used interchangeably to define custom types.

> However, Unreal Engine structs are used to represent data types that are typically used for data storage and manipulation, whereas classes are used to represent objects that have behavior and state.

```cpp
// Code here
```

#### Function related

-   `virtual` - Specifies that a function should be polymorphic, meaning that it can be overridden by a derived class.
-   `override` - Indicates that a function in a derived class is intended to override a function in the base class.
-   `static` - Specifies that a variable or function is associated with a class rather than with a specific instance of the class.
-   `inline` - Specifies that a function should be inlined (i.e., its code should be inserted directly into the calling code rather than calling the function).
-   `force_inline` - Instructs the compiler to inline a function, regardless of whether it would normally do so.

```cpp
/**
 * @brief Struct used to store vehicle details.
 */
struct Details
{
    /**
     * @brief Unique identifier for the vehicle.
     */
    int id;
};

/**
 * @brief Abstract base class for vehicles.
 */
class VehicleBase
{
public:
    /**
     * @brief Honk the vehicle.
     *
     * This function should be implemented by derived classes to provide a way for
     * the vehicle to make a noise.
     */
    virtual void Honk() = 0;

    /**
     * @brief Get the type of the vehicle.
     *
     * @return The type of the vehicle as a string.
     */
    virtual std::string GetVehicleType() = 0;

    /**
     * @brief Get the details of the vehicle.
     *
     * This function is a static member function and can be called without an
     * instance of the class.
     *
     * @return The vehicle details.
     */
    static Details GetDetails()
    {
        return Details
        {
            id = 0
        };
    }
};

/**
 * @brief Class representing a car.
 */
class Car : public VehicleBase
{
public:
    /**
     * @brief Overridden implementation of the Honk() function.
     *
     * This function calls the base implementation of Honk() and then does
     * some additional work.
     */
    void Honk() override
    {
        // Calls the base function from the class's derived type.
        VehicleBase::Honk();
    }

    /**
     * @brief Overridden implementation of the GetVehicleType() function.
     *
     * This function returns a string representing the type of the vehicle.
     *
     * @return The type of the vehicle as a string.
     */
    std::string GetVehicleType() override
    {
        return "Car";
    }
};

/**
 * @brief Class representing a bike.
 */
class Bike : public VehicleBase
{
public:
    /**
     * @brief Overridden implementation of the Honk() function.
     *
     * This function does not call the base implementation of Honk() and
     * therefore can overwrite the logic.
     */
    void Honk() override
    {
        // Does not call the base function, therefore can overwrite the logic.

        // Some other code
    }

    /**
     * @brief Overridden implementation of the GetVehicleType() function.
     *
     * This function returns a string representing the type of the vehicle.
     *
     * @return The type of the vehicle as a string.
     */
    std::string GetVehicleType() override
    {
        return "Bike";
    }
};

// Static member function call
Details details = VehicleBase::GetDetails();
```

---

<figure>
    <blockquote>
        <p>“In theory, using inline functions can make your program faster because they eliminate the overhead associated with function calls. Calling a function requires pushing the return address on the stack, pushing arguments onto the stack, jumping to the function body, and then executing a return instruction when the function finishes. This process is eliminated by inlining the function. The compiler also has different opportunities to optimize functions expanded inline versus those that aren't. A tradeoff of inline functions is that the overall size of your program can increase.”</p>
    </blockquote>
    <figcaption>
        <cite>
            <a href="https://learn.microsoft.com/en-us/cpp/cpp/inline-functions-cpp">Microsoft docs</a>
        </cite>
    </figcaption>
</figure>

When inlining functions, you have the option to force or give the decision up to the compiler. By using `inline`, you are telling the compiler, that they are allowed to inline this function. However, it doesn't grant for an inline function.

To force an inline function, you must use `force_inline` keyword.

> [!NOTE]
> In Unreal Engine, it is more common to use a macro called `FORCEINLINE`, which is essentially expands to `force_inline` keyword.

```cpp
inline int CalcNewHealth(int Health)
{
    return Health - 10;
}

const int Health = 10;
Health = CalcNewHealth(Health); // Compiles to: Health = 10 - 10;
```

#### Casts

-   `dynamic_cast` - Performs a runtime check to determine whether an object can be cast to a different type.
-   `static_cast` - Performs a static cast, which allows an expression to be converted to a different data type at compile time.
-   `const_cast` - Performs a cast but removes the const from the variable, which it has been declared on.
-   `reinterpret_cast` - Performs a cast that allows converting a pointer to any other type of pointer. Meaing, that this cast will allow you to reinterpretation of the bits representing the value without changing them.

```cpp
// Performs a runtime check to determine whether an object can be cast to a different type.
Parent* parentPtr = dynamic_cast<Parent*>(childPtr);

if (parentPtr)
{
    // Casting successful, handle parentPtr
}
else
{
    // Casting failed, handle accordingly
}
```

```cpp
// Performs a static cast, allowing an expression to be converted to a different data type at compile time.
int num = 10;
double result = static_cast<double>(num);
```

```cpp
// Removes the const from a variable, which it has been declared on.
const int x = 5;

int* y = const_cast<int*>(&x);

// Modifying the value of x through y
*y = 10; // Will be changed to 10 instead 5.
```

```cpp
// Converting a pointer to any other type of pointer, reinterpreting the bits representing the value without changing them.
int* ptr = new int(65);
char* charPtr = reinterpret_cast<char*>(ptr); // Will be casted to char pointer, with the value of 'A'.
```

> [!CAUTION]
> Don't use C++ version of casts in Unreal Engine project. Instead, use ´Cast()´ provide by the engine. This cast is optimized for UE specific.

> [!NOTE]
> If you wish to use `static_cast()` in Unreal, then use `StaticCast()` provided by the engine. It will result in the same code, but fixes some issue with Visual Studio.

```cpp
// Code here
```

#### Flow controls

-   `if`, `else if` and `else` - Used for conditional execution in a program. `if` checks a condition and executes a block of code if the condition is true. `else if` provides an alternative condition to check if the first condition is false. `else` executes a block of code if none of the previous conditions are true.

-   `switch` - A control flow statement used to select one of many code blocks to be executed based on the value of an expression.

-   `for` - A loop statement that repeatedly executes a block of code as long as a condition is true. It consists of initialization, condition, and increment/decrement expression.

-   `while` - Another loop statement that executes a block of code as long as a specified condition is true.

-   `do` and `while` - Similar to the `while` loop, but the `do while` loop will execute the block of code at least once before checking the condition.

-   `break` - Used to exit a loop or switch statement prematurely, transferring the program control to the statement immediately following the loop or switch.

-   `continue` - Causes the program to skip the rest of the current iteration of a loop and proceed to the next iteration.

-   `try`, `catch` and `finally` - Implements exception handling by trying a block of code that may throw an exception, catching the exception if it is thrown, and executing cleanup code in the `finally` block regardless of whether an exception is thrown or not.

```cpp
int num = 10;

if (num > 10)
{
    // do something
}
else if (num < 10)
{
    // do something else
}
else
{
    // do something different
}
```

```cpp
int option = 2;

switch (option)
{
    case 1:
        // case 1 actions
        break;

    case 2:
        // case 2 actions
        break;

    default:
        // default actions
        break;
}
```

```cpp
for (int i = 0; i < 5; ++i)
{
    // loop body
}
```

```cpp
int i = 0;

while (i < 5)
{
    // loop body
    ++i;
}
```

```cpp
int j = 0;

do
{
    // loop body
    ++j;
}
while (j < 5);
```

```cpp
for (int i = 0; i < 10; ++i)
{
    if (i == 5)  break; // exits the loop when i equals 5

    // loop body
}
```

```cpp
for (int i = 0; i < 5; ++i)
{
    if (i == 2)  continue; // skips the rest of the loop body for i equals 2

    // loop body
}
```

```cpp
try
{
    // block of code that may throw an exception
    throw 20; // example of throwing an exception
}
catch (int e)
{
    // handle exception
    // e contains the thrown value
}
finally
{
    // clean-up code that executes whether an exception is thrown or not
}
```

#### Generic programming

-   `template` - Allows generic programming by defining a type or function with parameters that are specified at compile time.

```cpp
template <typename T>
void PrintArray(T* arr, size_t size)
{
    for (size_t i = 0; i < size; ++i)
        std::cout << arr[i] << ", ";

    std::cout << std::endl;
}
```

```cpp
int arr1[5] = { 1, 2, 3, 4, 5 };
double arr2[5] = { 1.1, 2.2, 3.3, 4.4, 5.5 };
std::string arr3[5] = { "one", "two", "three", "four", "five" };

PrintArray(arr1, sizeof(arr1) / sizeof(arr1[0])); // 1, 2, 3, 4, 5,
PrintArray(arr2, sizeof(arr2) / sizeof(arr2[0])); // 1.1, 2.2, 3.3, 4.4, 5.5,
PrintArray(arr3, sizeof(arr3) / sizeof(arr3[0])); // one, two, three, four, five,
```

#### Misc

-   `auto` - Allows the compiler to deduce the type of a variable based on its initializer. Similar to C# version of `var` keyword.
-   `namespace` - Defines a scope for identifiers to avoid naming conflicts.
-   `operator` - Declares a function as an overloaded operator.
-   `explicit` - Specifies that a constructor or conversion operator cannot be used for implicit type conversions.

```cpp
namespace MyNamespace
{
    /**
     * @brief This is an example class that shows how to use the `auto` keyword
     * and overloaded operators.
     */
    class MyClass
    {
    public:
        /**
         * @brief Returns the current value of the class.
         * @return The current value.
         */
        int GetValue() const { return value; }

    private:
        int value;

    public:
        /**
         * @brief Adds the given number to the current value.
         * @param number The number to add.
         * @return The result of the addition.
         */
        int Add(const int& number)
        {
            // The compiler will figure out what type it should be
            auto result = value + number;
            return result;
        }

        /**
         * @brief Updates the value of the class.
         *
         * This function is an example of bad practices.
         * As the other developers who might read code,
         * doesn't understand the return value type is.
         */
        void ExampleOfBadPractice()
        {
            auto result = Add(5);
        }

        /**
         * @brief Overloaded `+` operator.
         * @param other The number to add to the current value.
         * @return A reference to the current object (to allow chaining).
         */
        void operator+(const int& other)
        {
            value = Add(other);
        }
    };
}
```

> [!TIP]
> It's recommended to `auto` keyword where a variable is declared twice during a single line. For an example, during a cast operation. If you use the `auto` keyword on a function return value, it can be extremely difficult for other developers to see what the return value type is.

> [!CAUTION]
> UHT doesn't support `operator` or `namespace` keyword. Meaning, you can't have a C++ class with a namespace, nor use the operations function for Blueprint.

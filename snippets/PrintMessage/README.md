```cpp
#include "YourClass.h"

// YourClass.cpp

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Green, text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT(text), fstring))

void YourClass::PrintMessage()
{
    int Number = 42;
    float Pi = 3.14159f;
    FString Name = TEXT("John Doe");

    // Using the print macro to print a simple text message
    print(TEXT("Hello, World!"));

    // Using the printFString macro to print a formatted message
    printFString("The number is: %d", Number);
    printFString("The value of Pi is: %f", Pi);
    printFString("My name is: %s", *Name);
}
```

In this example, we have a class called `YourClass`, and inside the `PrintMessage` function, we use the `print` and `printFString` macros to print messages on the screen.

The `print` macro takes a single parameter, which is the text message to be displayed.

The `printFString` macro takes two parameters: the format string and the variable to be formatted. The format string uses `%d` for integers, `%f` for floats, and `%s` for strings. The `FString::Printf` function is used to format the message with the given variable.

When you call the `PrintMessage` function, you should see the messages displayed on the screen in the game window.
## ⚠️ Common Issues

<table><tr><td>
This section was NOT written in conjunction with ChatGPT.
</td></tr></table>

![Common Errors](static/img/Cpp_Errors.png)

### ⛔ Compiler Error C2628

Description
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

[Link](https://learn.microsoft.com/en-us/cpp/error-messages/compiler-errors-2/compiler-error-c2628?view=msvc-170) to error message.

### ⛔ Compiler Error C2065

Description
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

[Link](https://learn.microsoft.com/en-us/cpp/error-messages/compiler-errors-1/compiler-error-c2065?view=msvc-170) to error message.

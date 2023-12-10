## 🌍 Global Functions

<table><tr><td>
This section was written in conjunction with ChatGPT.
</td></tr></table>

Global functions are functions that are defined outside of any class and are not tied to any specific object instance. They are accessible from any part of the codebase and can be used to perform tasks or calculations that do not require access to specific object properties or methods.

Global functions in Unreal Engine are commonly used for utility functions, helper functions, or functions that operate on data independently of any particular object instance.

* `IsValid()`: Check if a pointer or object reference is valid. This is important to avoid accessing or modifying null pointers, which can cause crashes or other unexpected behavior.
* `Swap()`: Swaps the contents of two `TObjectPtr` objects.
* `Exchange()`: Exchanges the contents of a `TObjectPtr` with a new object, returning the previous object.
* `MakeWeakObjectPtr()`: Creates a weak pointer (`TWeakObjectPtr`) from a `TObjectPtr`, allowing for non-owning references to the object.
* `Cast()`: Is used to attempt to cast an object from one type to another. If the object is not of the specified type, it will return a nullptr. If the object is of the specified type or a subclass of it, the function will return a pointer to the object cast to the specified type.
* `CastChecked()`: Is similar to `Cast()`, but it also performs a runtime check in debug builds to ensure that the object is of the specified type. If the check fails, it will trigger an assertion. This function is useful when you are certain that an object should be of a particular type and want to catch errors early in development.

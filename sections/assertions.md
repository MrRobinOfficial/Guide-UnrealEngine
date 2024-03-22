## ☑️ Assertions

<table><tr><td>
This section was written in conjunction with ChatGPT.
</td></tr></table>

![Assertions](static/img/Assertions.png)

Assertions are a programming technique used to detect and report errors or unexpected behavior in code. In Unreal Engine, assert macros are provided to make it easier to add assertions to code and to customize the behavior of the engine when an assertion fails.

### Check

Used to test a condition at runtime and to report an error if the condition fails. If the condition is false, the `check(Expression)` macro will print an error message to the console and either halt the game or break into the debugger, depending on the configuration of the engine.

The `check(Expression)` macro is typically used to detect programming errors or unexpected runtime conditions.

```cpp
void MyFunction()
{
    APlayerCharacter* PC = Cast<APlayerController>(GetController());

    // If the condition returns false, the game will crash.
    // By default, C++ and Unreal has some overloads for pointers and classes, which allows them to return as boolean.
    check(PC);

    // But, if you wish to be explicit, then you have these options:
    check(PC != nullptr);
}
```

### Verify

Similar to the `check(Expression)` macro, but is only enabled in debug builds of the engine. If the condition is false, the `verify(Expression)` macro will break into the debugger but will not halt the game.

The `verify(Expression)` macro is typically used to detect errors during development or testing, but does not impact the performance of the final release build.

```cpp
void MyFunction()
{
    APlayerCharacter* PC = Cast<APlayerController>(GetController());

    // Same as 'check' assertion.
    // However, this assertion will include in all builds (including shipping builds).
    verify(PC);
}
```

### Ensure

Similar to the `check(Expression)` macro, but is used to test conditions that are not necessarily fatal to the program. If the condition is false, the `ensure(Expression)` macro will print a warning message to the console and either halt the game or break into the debugger, depending on the configuration of the engine.

The `ensure(Expression)` macro is typically used to detect non-fatal errors or unexpected conditions that can be recovered from.

```cpp
void MyFunction()
{
    APlayerCharacter* PC = Cast<APlayerController>(GetController());

    // Non-critical check (assertion only during development and editor builds).
    // This will only call once and will not retrigger for each play.
    ensure(PC);

    // To have this assertion retriggerable, then use this macro instead:
    ensureAlways(PC);
}
```

### Alternatives Assertions

There is also alternatives macros[^4] that displays text.

<table><tr><td>

-   `checkf(Expression, FormattedText, ...)` or `checkfSlow(Expression, FormattedText, ...)` - Halts execution if `Expression` is false and outputs `FormattedText` to the log
-   `verifyf(Expression, FormattedText, ...)` or `verifySlow(Expression, FormattedText, ...)` - Halts execution if `Expression` is false and outputs `FormattedText` to the log.
-   `ensureMsgf(Expression, FormattedText, ...)` - Notifies the crash reporter and outputs `FormattedText` to the log on the first time `Expression` is false.
-   `ensureAlwaysMsgf(Expression, FormattedText, ...)` - Notifies the crash reporter and outputs `FormattedText` to the log if `Expression` is false.

```cpp
void MyFunction()
{
    APlayerCharacter* PC = Cast<APlayerController>(GetController());
    checkf(PC, TEXT("Player character cannot be null!"));

    ULocalPlayer LP = PC->GetLocalPlayer();
    verifyf(LP, TEXT("Local player cannot be null in shipping builds!"));

    bool bIsDead = false;
    ensureMsgf(bIsDead, TEXT("Player shouldn't be dead!"));
}
```

</td></tr></table>

### Misc Assertions

There is also an `unimplemented` assert macro. Useful for writing functions that require code, but is currently unimplemented.

```cpp
void DoSomething()
{
    unimplemented();
}
```

Another assert macro is `checkCode`. Which is an asserted marco to check your code is valid. Behind the scene, the code runs inside a do-while loop with while set to false. This prevents from looping. The main point of using this technique is to clean up memory afterwards and the ability to use `continue` or `break` keyword.

```cpp
checkCode(
    if (ObjectItem->IsPendingKill())
    {
        UE_LOG(LogGarbage, Fatal, TEXT("Object %s is part of root set though has been marked RF_PendingKill!"), *Object->GetFullName());
    }
);
```

And lastly, we have `checkNoEntry`, `checkNoReentry` and `checkNoRecursion` assert macros.

-   `checkNoEntry` indicates that code should never be reached.
-   `checkNoReentry` indicates that code should not be executed more than once.
-   `checkNoRecursion` indicates that code should never be called recursively.

```cpp
void KillPlayer()
{
    PlayerPtr->Destroy();
    PlayerPtr = nullptr;

    if (IsValid(Player))
    {
        checkNoEntry();
    }
}

void CleanupCharacters(int32 Count)
{
    if (Count > 3)
        return;

    checkNoRecursion();

    if (IsValid(Player))
    {
        checkNoReentry();
        KillPlayer();
    }

    CleanupCharacters(Count + 1);
}
```

---

You can read more about [Assertions from the docs](https://docs.unrealengine.com/5.1/en-US/asserts-in-unreal-engine/).

You can also watch a video about it from [Sneaky Kitty Game Dev](https://www.youtube.com/watch?v=zGeJgI2xiT4).

---

| Assertion | Description                                                                                                                                                                                             | Use Cases                                                                                                                                                          |
| --------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| `check`   | A macro used for runtime checks in Unreal Engine, which is enabled only in Debug builds.                                                                                                                | - Validating preconditions or assumptions in the code.<br>- Ensuring that critical conditions are met during development and debugging.                            |
|           | If the condition specified in the `check` macro evaluates to false, it triggers an assertion failure, halting the program's execution in Debug mode, allowing developers to identify and fix the issue. | - Detecting potential bugs or logic errors during development.<br>- Identifying unexpected conditions that should not occur during testing or debugging.           |
|           | The `check` macro is compiled out in non-Debug builds, so it has no impact on the performance of the release version of the game.                                                                       |                                                                                                                                                                    |
|           |                                                                                                                                                                                                         |                                                                                                                                                                    |
| `verify`  | A macro similar to `check`, used for runtime checks in Unreal Engine, but it is enabled in both Debug and Release builds.                                                                               | - Similar use cases as `check`, but with the intention of detecting issues in both Debug and Release builds.<br>- Useful for crucial runtime checks in production. |
|           | If the condition specified in the `verify` macro evaluates to false, it triggers an assertion failure in both Debug and Release builds, halting the program's execution.                                |                                                                                                                                                                    |
|           | This can help identify and fix critical issues even in the final release version of the game or application.                                                                                            |                                                                                                                                                                    |
|           |                                                                                                                                                                                                         |                                                                                                                                                                    |
| `ensure`  | A macro specifically designed for Unreal Engine, used for runtime checks with a focus on improving the robustness of code in shipping games.                                                            | - Verifying and enforcing assumptions, preconditions, and invariants in the code to avoid crashes and unexpected behavior in production environments.              |
|           | The `ensure` macro remains active in both Debug and Release builds, and its behavior can be configured in the Unreal Editor project settings.                                                           | - In a shipping build, `ensure` can be set to log a message or perform a fail-safe action instead of halting the program's execution.                              |
|           | If the condition specified in the `ensure` macro evaluates to false, it may trigger an assertion or perform an alternative action based on project settings.                                            |                                                                                                                                                                    |

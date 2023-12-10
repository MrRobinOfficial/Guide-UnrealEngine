## 📚 Create custom module

<table><tr><td>
This section was NOT written in conjunction with ChatGPT.
</td></tr></table>

You can read more about Unreal Engine's modules [here](https://docs.unrealengine.com/5.1/en-US/unreal-engine-modules/)!

In Unreal Engine, a module is a way to organize game code into smaller pieces, similar to Unity's Assembly Definitions. By separating code into modules, you can reduce compile times and keep your code more organized.

For example, you could create a module called `Vehicle` to contain all the code related to the vehicle system. This would allow you to isolate the vehicle code from other parts of the game, such as the inventory system, and make it easier to maintain and update.

> [!NOTE]
> Unreal Engine modules are not related to C++ 20 modules.

Here is a list of Unreal Engine's modules:

<table><tr><td>

* Core
* CoreUObject
* InputCore
* Engine
* UnrealEd
* SlateCore
* Slate
* UMG
* UMGEditor

</td></tr></table>

Working with modules can also help you stay focused on the specific functionality you're implementing, as you only need to work with the code relevant to that module.

### Module structure

All modules should be placed in the Source directory for either a plugin or project. The module's root folder should have the same name as the corresponding module.

There should also be a [ModuleName].Build.csfile for each module in its root folder, and its C++ code should be contained in Private and Public folders.

![image](https://user-images.githubusercontent.com/61658252/236797649-1acb5aac-ab05-4676-86a4-959e443de404.png)

### ♻️ Circular Dependency

It's possible to encounter circular dependencies when multiple modules access the same module. This occurs when module A depends on module B, and module B also depends on module A.

To resolve circular dependencies, you can take several approaches:

<table><tr><td>

* One option is to use the `CircularlyReferencedDependentModules` statement in the [ModuleName].Build.cs file. You can read more about [here](https://forums.unrealengine.com/t/workaround-for-circular-dependencies/264945)!

Here's an example:

```cpp
using UnrealBuildTool;

public class ModuleB : ModuleRules
{
    public ModuleB(ReadOnlyTargetRules Target) : base(Target)
    {
        PrivateDependencyModuleNames.AddRange(new string[]
        {
            "ModuleA"
        });

        CircularlyReferencedDependentModules.Add("ModuleA");  // Avoid circular dependencies errors!
    }
}
```

* Another option is to create another module to further separate the code into smaller pieces.

* Finally, you can also refactor your modules to avoid circular dependencies altogether.

</td></tr></table>

*The best solution will depend on your specific situation and the complexity of your code.*

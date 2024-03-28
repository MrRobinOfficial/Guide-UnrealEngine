## 📚 Create custom module

<table><tr><td>
This section was NOT written in conjunction with ChatGPT.
</td></tr></table>

In Unreal Engine, a module is a way to organize game code into smaller pieces, similar to Unity's Assembly Definitions. By separating code into modules, you can reduce compile times and keep your code more organized.

For example, you could create a module called `Vehicle` to contain all the code related to the vehicle system. This would allow you to isolate the vehicle code from other parts of the game, such as the inventory system, and make it easier to maintain and update.

> [!NOTE]
> Unreal Engine modules are **NOT** related to C++ 20 modules.

You can read more about Unreal Engine's modules [here](https://dev.epicgames.com/documentation/en-us/unreal-engine/unreal-engine-modules)!

Here is a list of common Unreal Engine's modules:

<table><tr><td>

-   Core
-   CoreUObject
-   InputCore
-   Engine
-   UnrealEd
-   SlateCore
-   Slate
-   UMG
-   UMGEditor

</td></tr></table>

Working with modules can also help you stay focused on the specific functionality you're implementing, as you only need to work with the code relevant to that module.

### Module structure

All modules should be placed in the Source directory for either a plugin or project. The module's root folder should have the same name as the corresponding module.

There should also be a _[ModuleName].Build.csfile_ for each module in its root folder, and its C++ code should be contained in **Private** and **Public** folders.

![image](https://user-images.githubusercontent.com/61658252/236797649-1acb5aac-ab05-4676-86a4-959e443de404.png)

### Module code

```csharp
// Gameplay.Build.cs

using UnrealBuildTool;

public class Gameplay : ModuleRules
{
    public Gameplay(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[]
        {
            // ... add public include paths required here ...
        });


        PrivateIncludePaths.AddRange(new string[]
        {
            // ... add other private include paths required here ...
        });


        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            // ... add other public dependencies that you statically link with here ...
        });

        PrivateDependencyModuleNames.AddRange(new string[]
        {
            // ... add private dependencies that you statically link with here ...

            // NOTE, private dependencies will not be required to import in other modules
            // This means, if you require a plugin but don't want to import in other modules, here is the list for that.
        });

        DynamicallyLoadedModuleNames.AddRange(new string[]
        {
            // ... add any modules that your module loads dynamically here ...
        });
    }
}
```

```cpp
// Private/GameplayModule.cpp

#include "Modules/ModuleManager.h"

// NOTE, this macro is handling the default implementation for a module setup.
IMPLEMENT_MODULE(FDefaultModuleImpl, Gameplay);
```

If you require more setup for a module (callbacks on the editor), you must create a specific class for that.

Here is a full setup of module class:

```cpp
// Private/GameplayModule.cpp

#include "GameplayModule.h"

#define LOCTEXT_NAMESPACE "FGameplayModule"

void FGameplayModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FGameplayModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FGameplayModule, Gameplay)
```

```cpp
// Public/GameplayModule.h

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FGameplayModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	void StartupModule() override;
	void ShutdownModule() override;
};
```

### ♻️ Circular Dependency

It's possible to encounter circular dependencies when multiple modules access the same module. This occurs when module A depends on module B, and module B also depends on module A.

To resolve circular dependencies, you can take several approaches:

-   One option is to use the `CircularlyReferencedDependentModules` statement in the [ModuleName].Build.cs file. You can read more about [here](https://forums.unrealengine.com/t/workaround-for-circular-dependencies/264945)!

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

-   Another option is to create another module to further separate the code into smaller pieces.

-   Finally, you can also refactor your modules to avoid circular dependencies altogether.

_The best solution will depend on your specific situation and the complexity of your code._

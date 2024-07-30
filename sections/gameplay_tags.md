## 🧵 Gameplay Tags

Unreal has Actor tags that can be used to tag certain actors in your game. However, actor tags has a common problem that around string tag system used in a game engine, mainly spelling mistake, case sensitivity and bad maintainability. To solve these problems, Unreal introduced **Gameplay Tags**.

Gameplay tags are a powerful string tag system in Unreal, that help you organize your tags in a hierarchical way. It uses a UI interface to create and manage tags, this prevents from spelling mistakes. It also increases the maintainability of your code.

With Gameplay tags, you can define a tag tree structure where each tag can have child tags. You can also query specific tags or child tags using the query syntax.

You can read more about [Gameplay Tags on Unreal's blog](https://www.unrealengine.com/es-ES/tech-blog/using-gameplay-tags-to-label-and-organize-your-content-in-ue4).

> [!IMPORTANT]
> In order to use Gameplay Tags in C++, you must include the module (`GameplayTags`) inside the build system.

You can also watch this video by [LeafBranchGames to learn all about Gameplay Tags](https://www.youtube.com/watch?v=edJGE0aidZY).

### Usage

<!-- TODO: Add images -->

To manage your pre-existing Gameplay Tags in your project, open the **Gameplay Tags** tab in your **Project Settings**.

For example, you can create a tag tree like this:

-   `Weapon`
    -   `Gun`
        -   `Rifle`
            -   `AK47`
        -   `Pistol`
            -   `Glock-18`
        -   `Sniper`
            -   `AWP`
    -   `Melee`
        -   `Knife`

And then you can use the query syntax to find specific tags or child tags like this:

-   `Weapon.Gun.Rifle` will return all the child tags of `Weapon.Gun.Rifle`
-   `Weapon.Gun.Pistol` will return all the child tags of `Weapon.Gun.Pistol`
-   `Weapon.Gun.Sniper` will return all the child tags of `Weapon.Gun.Sniper`
-   `Weapon.Gun` will return all the child tags of `Weapon.Gun`
-   `Weapon.Melee` will return all the child tags of `Weapon.Melee`
-   `Weapon` will return all the child tags of `Weapon`

### Data types

-   [FGameplayTag](https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/GameplayTags/FGameplayTag), is a single tag. which represents a hierarchical name of the form `x.y` that is registered in the **GameplayTagsManager**.

-   [FGameplayTagContainer](https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/GameplayTags/FGameplayTagContainer), holds a collection of tags.

### Code

To use a Gameplay tag in code, you can do the following:

```cpp
// .h

#include "GameplayTagContainer.h"

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayTags", meta = (Categories = "Weapon.Gun"))
FGameplayTag GunTag;
```

To define Gameplay tags in your code, you can do the following:

```cpp
// .h

#include "NativeGameplayTags.h"

/** Declares the "Weapon.Gun.Rifle.AK47" gameplay tag. */
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_AK47)
```

```cpp
// .cpp

/** Define and expose the gameplay tag "Weapon.Gun.Rifle.AK47" to other modules and code. */
UE_DEFINE_GAMEPLAY_TAG(TAG_AK47, "Weapon.Gun.Rifle.AK47");
```

> [!NOTE]
> To avoid having to to use both `UE_DECLARE_GAMEPLAY_TAG_EXTERN()` and `UE_DEFINE_GAMEPLAY_TAG`, you can instead use: `UE_DEFINE_GAMEPLAY_TAG_STATIC()`. However, this macro should only used in the declared implementation file.

```cpp
// .cpp

/** Defines and locks the gameplay tag "Weapon.Melee.Knife" to this implementation file. */
UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_Weapon_Knife, "Weapon.Melee.Knife");
```

To use these tags in your code, you can do the following:

```cpp
FGameplayTag Tag;
bool bMatchesTag = Tag.MatchesTag(TEXT("MyTag"));

FGameplayTagContainer Tags;
FGameplayTagContainer IgnoreTags;
bool bHasTag = Tags.HasTag(TEXT("MyTag"));
bool bHasAnyTag = Tags.HasAny(IgnoreTags, TEXT("MyTag"));
```

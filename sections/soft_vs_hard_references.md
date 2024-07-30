## 💾 Soft vs hard references

<table><tr><td>
This section was NOT written in conjunction with ChatGPT.
</td></tr></table>

![Soft vs hard references](static/img/Soft_Hard_Refs.png)

When referencing an asset in Unreal Engine, you can opt for either soft or hard references. With hard references, the asset is loaded into memory, either by the editor or when it is spawned into a level.

Moreover, all assets with hard references must also be loaded into memory to ensure their availability. If they aren't, the game may crash.

This situation, often referred to as a chain-reaction, results in all assets referenced by the initial asset also being loaded into memory. This can lead to long loading times and potential performance issues.

> [!NOTE]
> Assets can include textures, meshes, sounds, animations, effects, blueprints, etc. Basically anything that can be referenced by another asset.

> [!TIP]
> You can use tools like **Reference Viewer** or **Size Map** to analyze the reference chain of an asset. More information can be found in the [Tools](#tools) section.

To mitigate hard references, you can use soft references, which function similarly to a lazy loading system. This means that an asset are only loaded if they are actually needed.

In other words, you need to load them **manually** to use them.

A soft reference is a data type that stores the path to an asset. Epic have provided safety checks, to ensure correct object type. They have also provided functions to load or unload an asset during runtime. This can be really helpful, especially when you don't want the asset to be loaded all the time.

You can read more about [Referencing Assets](https://dev.epicgames.com/documentation/en-us/unreal-engine/referencing-assets-in-unreal-engine) at Unreal's docs.

You can also read more about [Asynchronous Asset Loading](https://dev.epicgames.com/documentation/en-us/unreal-engine/asynchronous-asset-loading-in-unreal-engine) at Unreal's docs.

There is also an article called [Hard References & Reasons to Avoid Them](https://raharuu.github.io/unreal/hard-references-reasons-avoid/) by Phil.

### Blueprint

To use soft references in Blueprint, you can change the variable type to `Soft Object Reference` or `Soft Class Reference`.

![TSoftObjectPtr](static/img/TSoftObjectPtr_BP.png)
![TSoftClassPtr](static/img/TSoftClassPtr_BP.png)

If you wish to load an asset synchronously, use the [Load Asset Blocking](https://dev.epicgames.com/documentation/en-us/unreal-engine/BlueprintAPI/Utilities/LoadAssetBlocking) node.

![LoadAssetBlocking Node](static/img/blueprint_nodes/LoadAssetBlocking.png)

> [!CAUTION]
> When loading an asset with synchronous, it will load on the main thread (which the game is running in). This can cause a lag spike (if the asset is heavily chained or large in size). Therefore, is recommended to use asynchronous loading when possible.

And with asynchronous loading, use the [Async Load Asset](https://dev.epicgames.com/documentation/en-us/unreal-engine/BlueprintAPI/Utilities/AsyncLoadAsset) node.

![AsyncLoadAsset Node](static/img/blueprint_nodes/AsyncLoadAsset.png)

If you want to unload an asset, use the [Unload Primary Asset](https://dev.epicgames.com/documentation/en-us/unreal-engine/BlueprintAPI/AssetManager/UnloadPrimaryAsset) node.

![UnloadPrimaryAsset Node](static/img/blueprint_nodes/UnloadPrimaryAsset.png)

> [!NOTE]
> Blueprint only support unloading primary assets (which are [Data Asset](https://dev.epicgames.com/documentation/en-us/unreal-engine/data-assets-in-unreal-engine)).

### C++

In C++, you can directly call the `LoadSynchronous()` method on a `TSoftObjectPtr` or `TSoftClassPtr` variable.

```cpp
TSoftObjectPtr<UTexture2D> TexturePtr; // Assign soft reference to a texture asset

// This will cause a lag spike (if the asset is heavily chained or large in size)
UTexture2D* Texture = TexturePtr.LoadSynchronous();

if (Texture.IsValid())
{
    // Use the loaded texture
}
```

> [!CAUTION]
> When loading an asset with synchronous, it will load on the main thread (which the game is running in). This can cause a lag spike (if the asset is heavily chained or large in size). Therefore, is recommended to use asynchronous loading when possible.

If you wish to unload or load an asset asynchronously, you must access the streamable manager through the asset manager. You can also inherit from the `UAssetManager` class, and extend custom functionality.

```cpp
// .h

TSoftObjectPtr<UTexture2D> TexturePtr; // Assign soft reference to a texture asset
```

```cpp
// .cpp
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"

FStreamableManager& Streamable = UAssetManager::GetStreamableManager();

// Request the asset to be loaded
Streamable.RequestAsyncLoad(
    TexturePtr.ToSoftObjectPath(),
    FStreamableDelegate::CreateUObject(
        this,
        &AMyActor::OnTextureLoaded
    )
);

void AMyActor::OnTextureLoaded()
{
    // Called when the texture is loaded and ready to use
    UTexture2D* Texture = TexturePtr.Get();

    if (Texture.IsValid())
    {
        // Use the loaded texture as needed
    }
}
```

You can also inline the callback into a lambda function:

```cpp
// Request the asset to be loaded
Streamable.RequestAsyncLoad(
    TexturePtr.ToSoftObjectPath(),
    FStreamableDelegate::CreateLambda(
        [this]()
        {
            // Called when the texture is loaded and ready to use
            UTexture2D* Texture = TexturePtr.Get();

            if (Texture)
            {
                // Use the loaded texture as needed
            }
        }
    )
);
```

To unload an asset, use the `Unload()` method.

```cpp
Streamable.Unload(TexturePtr.ToSoftObjectPath());
```

You can also load multiple assets asynchronously at once:

```cpp
TArray<FSoftObjectPath> StreamArray;
StreamArray.Add(TexturePtr.ToSoftObjectPath());

// Request the array of assets to be loaded (without a callback)
Streamable.RequestAsyncLoad(StreamArray);
```

You can also get the handle of the requested. Helpful for getting details about the request, such as progress bar, checking if the request is still loading or if it has completed.

You can also force the request to be cancelled.

Examples:

```cpp
TSharedPtr<FStreamableHandle> HandlePtr = Streamable.RequestAsyncLoad(StreamArray);

if (!HandlePtr.IsValid())
    return;

FStreamableHandle* Handle = HandlePtr.Get();
```

```cpp
Handle->GetProgress(); // Returns progress as a value between 0.0 and 1.0.
```

```cpp
int32 LoadedCount;
int32 RequestedCount;

// Returns number of assets that have completed loading out of initial list, failed loads will count as loaded
Handle->GetLoadedCount(LoadedCount, RequestedCount);
```

```cpp
// Release this handle. This can be called from normal gameplay code to indicate that the loaded assets are no longer needed
Handle->ReleaseHandle();

// Cancel a request, callable from within the manager or externally
Handle->CancelHandle();
```

```cpp
// True if load is still ongoing and we haven't been cancelled
bool bIsLoadingInProgress = Handle->IsLoadingInProgress();

// If this request has finished loading, meaning all available assets were loaded
bool bHasLoadCompleted = Handle->HasLoadCompleted();

// If this request was cancelled. Assets may still have been loaded, but completion delegate was not called
bool bWasCanceled = Handle->WasCanceled();

// If this handle is still active, meaning it wasn't canceled or released
bool bIsActive = Handle->IsActive();

// If this handle is stalled and waiting for another event to occur before it is actually requested
bool bIsStalled = Handle->IsStalled();
```

> [!WARNING]
> Don't use `FSoftObjectPath` or `FSoftObjectPtr`. Used for internal purpose.

### Tools

[Reference Viewer](https://docs.unrealengine.com/5.2/en-US/finding-asset-references-in-unreal-engine/) is a tool inside the editor, which allows you to look at the reference chain with a particular asset. Both hard and soft references. Helpful if you are trying to figure it out which is loading which and what causes a chain-reaction.

[Size Map](https://dev.epicgames.com/community/learning/tutorials/r4y7/unreal-engine-size-map) is another tool inside the editor, which allows you to look at the total and independent size of different assets, which has been loaded by the main source. For example, you can see how big the [memory footprint](https://en.wikipedia.org/wiki/Memory_footprint) of the player character.

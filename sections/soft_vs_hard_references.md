## 💾 Soft vs hard references

<table><tr><td>
This section was written in conjunction with ChatGPT.
</td></tr></table>

![Soft vs hard references](static/img/Soft_Hard_Refs.png)

### Soft References

A soft reference is a weak reference to an asset that does not create a strong dependency. It allows assets to be loaded or unloaded dynamically at runtime based on usage or other conditions. Soft references are used when you want to indicate a loose dependency on an asset without forcing its loading.

An analogy for a soft reference could be a bookmark in a book. It points to a specific page but doesn't physically hold the content. You can easily remove or change the bookmark without affecting the book's content.

### Hard References

A hard reference is a strong reference to an asset that creates a firm dependency. It ensures that the referenced asset is loaded and remains loaded as long as the referencing asset is in use. Hard references are used when you require a guaranteed presence of an asset during runtime.

An analogy for a hard reference could be a puzzle piece that needs to fit into a specific spot. The puzzle piece is integral to the puzzle, and removing or changing it would break the intended structure.

---

When an asset with hard references is loaded, it triggers a chain of dependencies, causing all assets that have hard references to be loaded as well. This ensures that all required assets are available for proper functionality. This loading behavior is known as "chain loading" or "load-on-demand."

For example, if a level blueprint references a specific sound cue with a hard reference, when the level is loaded, the sound cue and any other assets directly or indirectly referenced by it will also be loaded to maintain the integrity of the referenced sound cue's functionality.

In contrast, if a soft reference is used, the referenced asset may or may not be loaded initially, and it can be loaded or unloaded dynamically based on the specific requirements of the game or application.

Using the appropriate combination of soft and hard references allows for efficient management of asset dependencies, optimizing memory usage, and providing flexibility in loading and unloading assets during runtime.

[Reference Viewer](https://docs.unrealengine.com/5.2/en-US/finding-asset-references-in-unreal-engine/) is a tool inside the editor, which allows you to look at the reference chain with a particular asset. Both hard and soft references. This tool helps you to figure it out which is loading which and what chain dependencies it has.

[Size Map](https://dev.epicgames.com/community/learning/tutorials/r4y7/unreal-engine-size-map) is another tool inside the editor, which allows you to look at the total and independent size of different assets, which has been loaded by the main asset. For example, you can see how big the character [memory footprint](https://en.wikipedia.org/wiki/Memory_footprint) is (with all the textures and skeletal mesh).

You can read more about soft and hard references in article called [Hard References & Reasons to Avoid Them by raharuu](https://raharuu.github.io/unreal/hard-references-reasons-avoid/).

You can also read more about Unreal Engine docs about [Referencing Assets](https://docs.unrealengine.com/5.2/en-US/referencing-assets-in-unreal-engine/).

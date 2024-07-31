## 🚧 Blueprint vs C++

<table><tr><td>
This section was NOT written in conjunction with ChatGPT.
</td></tr></table>

[![Watch the video by Alex Forsythe](https://img.youtube.com/vi/VMZftEVDuCE/maxresdefault.jpg)](https://youtu.be/VMZftEVDuCE)

### Blueprint

Blueprint is a [visual scripting language](https://en.wikipedia.org/wiki/Visual_programming_language) that allows users to create programs using graphical elements in real-time. Some visual languages uses a node-based system, and some uses a block-based system (like [Scratch](<https://en.wikipedia.org/wiki/Scratch_(programming_language)>)). And Blueprint is a node-based system, making it ideal for rapid prototyping and modular development.

### C++

C++ is a statically typed, compiled programming language known for its blend of high-level and low-level features. Developed in the 1980s, it remains a powerful tool for a wide range of applications.

Learning C++ requires a solid understanding of both the language and general programming concepts. Many find it challenging due to its complexity and rich feature set, which can be overwhelming for beginners.

The language offers fine-grained control over system resources, including direct memory access, which is a **double-edged sword**: it provides great power but also the potential for errors, such as memory leaks or crashes, if not used carefully.

As [Bjarne Stroustrup](https://en.wikipedia.org/wiki/Bjarne_Stroustrup) (the creator of C++) once said:

> “_C makes it easy to shoot yourself in the foot; C++ makes it harder, but when you do it blows your whole leg off._”

### Which One Should You Use?

_Many newcomers to Unreal Engine ask this question quite a lot._

**Fortunately**, Unreal Engine supports a flexible workflow where you can use **both**.

You can start with Blueprint for quick iteration and visual scripting, and then add C++ for more detailed control and performance optimizations.

For example, you can create a base class in C++ and extend it with Blueprint to add specific details or visual effects. This approach allows you to write core functionality in C++, which can then interact with Blueprint scripts, providing a modular and flexible development process.

Examples:

-   **Weapons**: Define a base weapon class in C++ (e.g., `AWeapon`) and extend it with Blueprint for specific types of weapons (`BP_Pistol`, `BP_Rifle`, `BP_RocketLauncher`).

-   **Characters**: Create a base character class in C++ (e.g., `ABaseCharacter`) and then customize it in Blueprint (`BP_PlayerCharacter`).

-   **Components**: Develop a base component in C++ (e.g., `UInventoryComponent`) and enhance it using Blueprint (`BP_InventoryComponent`).

This combined approach work best, since it allows you to work both with C++ and Blueprint offering a flexible and efficient workflow for game development.

With C++, you can implement core functionalities such as damage handling, inventory systems, interaction mechanics, and save/load systems. This provides a solid, performance-optimized foundation for your game.

Once the core is in place, Blueprint can be used to enhance and expand upon these systems. In Blueprint, you can easily add visual elements like meshes and textures, incorporate sound and visual effects, and implement simple logic for rapid prototyping. This flexibility allows for quick iteration and modular development.

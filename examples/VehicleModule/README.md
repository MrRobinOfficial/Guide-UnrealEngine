# Module

_Creating a module in Unreal Engine with C++ is an essential step when you want to add new functionality or extend existing features of the engine. Modules help organize code into reusable units and facilitate the management of dependencies._

## Showcase

_In this demonstration, we will delve into the implementation of a vehicle module within Unreal Engine using C++. The module is specifically designed to incorporate the powerful Chaos Vehicle System provided by Unreal Engine, granting us access to a set of robust vehicle physics features._

This example showcases two fundamental classes:

* `ACarPawn`: Add functionality for the car (and also binding the car movement to the car).

* `UMyVehicleMovementComponent`: Handles the car movement (together with chaos physics).

## Getting started with modules

To create a module in Unreal Engine, you typically follow these steps:

1. **Create the Module Folder Structure:** Start by creating a new folder with the name of your module inside the "Source" folder of your Unreal Engine project. Inside this folder, you will need at least two sub-folders: `Public` and `Private`.

2. **Add Header and Source Files:** Inside the `Public` folder, create header files (`.h`) that define the public interfaces of your module. Inside the `Private` folder, add source files (`.cpp`) that implement the functionality of your module.

3. **Edit the Module Build File (.Build.cs):** In the root folder of your module, you will find a `.Build.cs` file. Open it with a text editor and configure it to include your module's files in the build process. Add any necessary dependencies on other modules or external libraries.

4. **Declare and Implement Module Classes:** In the header files of your module, declare the classes and functions you want to expose as part of the public interface. In the corresponding source files, implement the functionality of these classes and functions.

5. **Add Public Include Paths:** In the `.Build.cs` file, specify the public include paths so that other modules can access your module's public headers.

6. **Compile the Module:** Use Unreal Engine's built-in build system to compile your module. You can do this by opening the project in the Unreal Editor and selecting "**File**" -> "**Generate Visual Studio project files**" (if using Visual Studio) or "**File**" -> "**Generate Xcode project files**" (if using Xcode). Then build the project from the IDE.

7. **Use the Module:** Once the module is successfully built, you can start using its functionality in other parts of your Unreal Engine project. Include the module's public headers in the classes or Blueprints that need to access its functionality.

> **Remember**
> Modules allow you to encapsulate and structure your code effectively, making it easier to manage and extend the functionality of your game or application.
## ⚡ Compiling a plugin

When you find a plugin and trying to install it, you might find out that it doesn't support your current engine version.
And the Unreal's marketplace won't let you download unless you have a version associated.

One trick to avoid this, is to build the plugin manually and fixing compiling issues (header file missing or API changes). By installing the plugin with the access of the source code. Then by access the plugin with the UHT[^2] (Unreal Build Tool), you can then rebuild the plugin into a different engine version.

Here is `.bat` file (**Windows Only**) to locate the current engine directory, and compile your custom made plugin into another engine version:

```
@echo off

:: Setting up config variables
set EngineVersion=<EngineVersion>
set PluginName=<PluginName>
set InputDirectory=<InputDirectory>
set OutputDirectory=<OutputDirectory>
set TargetPlatforms=Win64

set PluginPath="%cd%\%InputDirectory%\%PluginName%\%PluginName%.uplugin"
set OutputPath="%cd%\%OutputDirectory%\%EngineVersion%\%PluginName%"

:: Locating a registry key, in order to find Unreal Engine source location

for /f "skip=2 tokens=2*" %%a in ('reg query "HKEY_LOCAL_MACHINE\SOFTWARE\EpicGames\Unreal Engine\%EngineVersion%" /v "InstalledDirectory"') do set "EngineDirectory=%%b"

set AutomationToolPath="%EngineDirectory%\Engine\Build\BatchFiles\RunUAT.bat"

title Build Plugin
echo Automation Tool Path: "%AutomationToolPath%"
echo:

call %AutomationToolPath% BuildPlugin -Plugin=%PluginPath% -Package=%OutputPath% -Rocket -TargetPlatforms=%TargetPlatforms%
echo:
pause
exit 0
```

And here is the bash file (**Linux Only**) version:

```
#!/bin/bash

# Setting up config variables
EngineVersion="<EngineVersion>"
PluginName="<PluginName>"
InputDirectory="<InputDirectory>"
OutputDirectory="<OutputDirectory>"
TargetPlatforms="Win64"

PluginPath="$PWD/$InputDirectory/$PluginName/$PluginName.uplugin"
OutputPath="$PWD/$OutputDirectory/$EngineVersion/$PluginName"

# Locating a registry key, in order to find Unreal Engine source location
EngineDirectory=$(reg query "HKEY_LOCAL_MACHINE\SOFTWARE\EpicGames\Unreal Engine\$EngineVersion" -v "InstalledDirectory" | awk 'NR==3{print $NF}')

AutomationToolPath="$EngineDirectory/Engine/Build/BatchFiles/RunUAT.bat"

echo "Automation Tool Path: \"$AutomationToolPath\""
echo

$AutomationToolPath BuildPlugin -Plugin="$PluginPath" -Package="$OutputPath" -Rocket -TargetPlatforms="$TargetPlatforms"

echo
read -p "Press Enter to continue..."
exit 0
```

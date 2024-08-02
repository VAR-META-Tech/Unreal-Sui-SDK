<p align="center">
	<img src="./Resource/SuiLogo.png" alt="Unreal-Sui-SDKLogo" width="256" height="128" />
</p>


# Unreal-Sui-SDK #

Unreal-Sui-SDK is a cpp package written in C++ to help developers integrate Sui blockchain technology into their cpp and Unreal projects.

- [Project Layout](#project-layout)
- [Features](#features)
- [Requirements](#requirements)
- [Dependencies](#dependencies)
- [Installation](#installation)
- [Example Unreal Project](#example-unreal-project)
- [Using Unreal-Sui-SDK](#using-unreal-sui-sdk)
  - [RestClient](#restclient)
  - [FaucetClient](#faucetclient)
  - [TokenClient](#tokenclient)
  - [EntryFunction](#entryfunction)
  - [Wallet](#wallet)
- [Using Unreal-Sui-SDK with Blueprint](#using-unreal-sui-sdk-with-blueprint)
- [Examples](#examples)
- [License](#license)

### Project Layout ###  

1. **`AptosSDKDemo/`**:: This directory contains examples showcasing how to use the Aptos Cpp SDK.
2. **`AptosUI/`**:: This directory contains Wallet example Unreal Project using Aptos Cpp SDK.
3. **`Doc/`**:: Documentation related to the project, which include setup API, Class references.
4. **`Resource/`**:: A place for various resources needed for the project, like images, data files, or other assets.
5. **`Src/`**: Contains the main source code for the SDK. This is where you'll find the core functionality, client classes, and utility modules.
6. **`ThirdParty/`**: Holds unit tests and integration tests for verifying the correctness of your code. Writing comprehensive tests ensures robustness.

### Features ###

- [x] ......
- [x] ......
- [x] ..........
- [x] ............s.


### Requirements ###

| Platforms                              | Unreal Version | Installation           | Status       |
| -------------------------------------- | ------------- | ---------------------- | ------------ |
| Mac / Linux                            | Unity engine 5.4| 3rd lib build config| Fully Tested |


### Dependencies
.................................................

### Installation ###
# Installation Guide

................................................

## Prerequisites

### All Platforms
- **.....**: ........

### macOS Specific
- **CMake** (version 3.14 or higher)
- **Visual Studio** with C++ development environment

## Installation Steps

### Windows
1. Install Visual Studio with the C++ development environment.
2. Install CMake if not included in the Visual Studio installation.
3. Install Conan using pip or download it from the official website.

### Linux
1. Install CMake and Conan using your distribution's package manager.

### macOS
1. Install Visual Studio with the C++ development environment.

2. Install ......:
    ```sh
    ..................
    ```
3. ........:
    ```sh
    ..................
    ```

## Project Setup

Follow these steps to set up the project environment:

1. Clone the repository and initialize submodules:
    ```sh
    git clone <repository-url>
    cd <repository-name>
    git submodule update --init --recursive
    ```
2. Build the project:
     ```sh
    git clone <repository-url>
    cd <repository-name>
    git submodule update --init --recursive
    ```

#For run code coverage on MacOS
First of all, make sure you have llvm and lcov installed. You can install them using brew:
brew install llvm lcov
To generate coverage data, you would then do:
cmake -DCODE_COVERAGE=ON ..
make
make coverage

### Example Unreal Project
A examples unreal project can be found in the following directory:  
`........`.

For Unreal project please reference example in ```........```, you need define Build.cs to integration Aptos library with Unreal engine.
Here is an example:
```cshape
// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.IO;
using System;
public class SuisdkUnreal : ModuleRules
{
	public SuisdkUnreal(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "Json", "JsonUtilities", "HTTP", "ImageWrapper" });
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		PrivateDependencyModuleNames.AddRange(new string[] { });
		if (Target.Platform == UnrealTargetPlatform.Mac)
		{
			string unreal_sui_sdk_LibPath = Path.Combine(ModuleDirectory, "../../Lib/", "libsui_rust_sdk.dylib");
			string destinationDirectory = Target.ProjectFile.Directory.FullName;
			PublicAdditionalLibraries.Add(unreal_sui_sdk_LibPath);
			PublicIncludePaths.AddRange(new string[] { Path.Combine(ModuleDirectory, "../../Lib/") });
			PublicIncludePaths.AddRange(new string[] { Path.Combine(ModuleDirectory, "../../../") });
		}
		CppStandard = CppStandardVersion.Cpp17;
	}
}

```
Video we using SDK on windows with sample unreal project:


link video

### Using Unreal-Sui-SDK
Unreal-Sui-SDK can integrate into your own any cpp or Unreal projects. The main functionality comes from several key classes: 

### using-Unreal-Sui-SDK-with-blueprint
**Create Wallet**
![](./Resource/create_wallet.png)

**Import Wallet**
![](./Resource/import_wallet.png)

**Send Transaction**
![](./Resource/send_transaction.png)

**Create Collection**
![](./Resource/create_collection.png)

**Create NFT**
![](./Resource/create_nft.png)

**Airdrop**
![](./Resource/airdrop.png)

### Examples ###

The SDK comes with several examples that show how to leverage the SDK to its full potential. The examples include 


link video


### License ###
This project is licensed under the Apache-2.0 License. Refer to the LICENSE.txt file for details.

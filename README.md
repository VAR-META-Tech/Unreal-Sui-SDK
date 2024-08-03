<p align="center">
	<img src="./Resource/SuiLogo.png" alt="Unreal-Sui-SDKLogo" width="256" height="128" />
</p>


# Unreal-Sui-SDK #

Unreal-Sui-SDK is a sample example to help developers integrate Sui blockchain technology into their C++ and Unreal projects.

- [Project Layout](#project-layout)
- [Features](#features)
- [Requirements](#requirements)
- [Dependencies](#dependencies)
- [Installation](#installation)
- [Using Unreal-Sui-SDK](#using-unreal-sui-sdk)
- [Using Unreal-Sui-SDK with Blueprint](#using-unreal-sui-sdk-with-blueprint)
- [Examples](#examples)
- [License](#license)

### Project Layout ###  

1. **`Config/`**:: This directory contains the project's configuration files, including INI files used to set various project parameters .
2. **`Content/`**:: This directory contains all the project's content assets.
3. **`Lib/`**:: This directory contains the libsui_rust_sdk.dylib library and header files to use the functions in the library.
4. **`Resource/`**:: A place for various resources needed for the project, like images, data files, or other assets.
5. **`Source/`**: This directory contains the project's C++ source code.

### Features ###

- [x]  Compatibility with main, dev, and test networks.
- [x]  Comprehensive Unit and Integration Test coverage.



### Requirements ###

| Platforms                              | Unreal Version | Installation           | Status       |
| -------------------------------------- | ------------- | ---------------------- | ------------ |
| Mac / Linux                            | Unity engine 5.4| 3rd lib build config| Fully Tested |


### Dependencies
- https://github.com/VAR-META-Tech/Rust2C-Sui-SDK

### Installation ###
# Installation Guide

This guide provides step-by-step instructions for installing and setting up on macOS platforms. Ensure you have the following prerequisites installed to build the project:

## Prerequisites
- **Visual Studio Code** with C++ development environment
- **Install Sui** Follow this guide to install Sui https://docs.sui.io/guides/developer/getting-started/sui-install
## Project Setup
Run follow command to setting Envỉroment befor testing:
1. Check Sui Client Environment:  
    ```sh 
    Sui client envs
    ```
 **NOTE:If you dont have DevNet Please Run CMD :**
```sh 
    sui client new-env --alias devnet --rpc https://fullnode.devnet.sui.io:443
```
2. Switch to devnet network: 
    ```sh 
    sui client switch --env devnet
    ```
3. Check current network:
    ```sh 
    sui client active-env
    ```
 **NOTE: The return should be devnet**
 
4. Get the active address: 
    ```sh
    sui client active-address
    ```
5. Request token:
    ```sh
    sui client faucet 
    ```
 **NOTE: Wait for 60s to get the tokens**

6. Check the gas coin objects for the active address: 
    ```sh
    sui client gas
    ```

### Using Unreal-Sui-SDK
Unreal-Sui-SDK can integrate into your own Unreal projects.
We have two options to run the project:

   1. Open the Unreal project directly through the SuisdkUnreal.uproject file and then click the Run icon to test.
    
   2. Open the project using Visual Studio Code, build the source code, and run the test.

For option 2 you need define Build.cs to integration libsui_rust_sdk.dylib library with Unreal engine.
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

### Using-Unreal-Sui-SDK-with-blueprint
**Create Wallet**
![](./Resource/create_wallet.png)

**Import Wallet**
![](./Resource/import_wallet.png)

**Send Transaction**
![](./Resource/send_transaction.png)

**Create Collection**
![](./Resource/create_collection.png)

**CreateNFT**
![](./Resource/create_nft.png)

**Multisign**
![](./Resource/airdrop.png)

### Examples ###

The SDK comes with several examples that show how to leverage the SDK to its full potential. The examples include Wallet Creation and Management, Token Transfers,  NFT Minting, Account Funding, and Multi-signature.

link video


### License ###
This project is licensed under the Apache-2.0 License. Refer to the LICENSE.txt file for details.

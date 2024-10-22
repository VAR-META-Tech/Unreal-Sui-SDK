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

#### General
- [x] Compatibility with main, dev, and test networks.
- [x] Integration with Sui blockchain using native libraries.
- [x] Cross-platform support (macOS, Windows, Linux).

#### NFT
- [x] Mint new NFTs.
- [x] Transfer NFTs to other addresses.
- [x] Retrieve wallet objects related to NFTs.
- [x] Conversion between raw and managed data structures for NFT objects.

#### BCS
- [x] Basic serialization and deserialization of Sui types.
- [x] Support for various Sui types including integers, floats, booleans, strings, and addresses.
- [x] Conversion of Sui types to BCS (Binary Canonical Serialization) format.

#### SuiMultisig
- [x] Create and manage multisig wallets.
- [x] Create transactions from multisig wallets.
- [x] Sign and execute transactions using multisig wallets.
- [x] Handling of multisig data structures and transaction results.

#### SuiTransactionBuilder
- [x] Create and manage transaction builders.
- [x] Add various types of commands to transactions (e.g., move call, transfer object, split coins, merge coins).
- [x] Execute transactions with or without a sponsor.

#### SuiWallet
- [x] Singleton pattern for easy access to wallet functionalities.
- [x] Generate new wallets with specified key schemes and word lengths.
- [x] Import wallets from private keys.
- [x] Import wallets from mnemonics.
- [x] List all wallets.
- [x] Display wallet details.
- [x] Generate and add new keys to the wallet.



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

##### Import Wallet from Private Key
To import a wallet using a private key:
```cpp
    ImportResult *result = import_from_private_key(PRIVATE_KEY_BASE64);
    printf("Status: %d\n", result->status);
    printf("Address: %s\n", result->address);
    printf("Error: %s\n", result->error);
```

##### Import Wallet from Mnemonic
To import a wallet using a mnemonic:
```cpp
     ImportResult *result = import_from_mnemonic(SENDER_MNEMONIC, "ED25519", SENDER_MNEMONIC_ALIAS);
    printf("Status: %d\n", result->status);
    printf("Address: %s\n", result->address);
    printf("Error: %s\n", result->error);
```

##### Get Saved Wallets
To get saved wallets:
```cpp
     WalletList wallet_list = get_wallets();
```

##### Get Saved Wallet From Address
To get saved wallet from address:
```cpp
    Wallet *wallet = get_wallet_from_address(ADDRESS);
```

##### Generate Wallet Using KeyScheme and Word Length
To generate wallet using key scheme and word length:
```cpp
    Wallet *wallet = generate_wallet("ed25519", "word12");
```

##### Generate random and save wallet
To generate random and save wallet:
```cpp
    Wallet *wallet = generate_and_add_key();
```

##### Request tokens from faucet
To request tokens from faucet:
```cpp
   const char *response = request_tokens_from_faucet(FAUCET_ADDRESS);
```

##### Execute programmable transaction
```cpp
    unsigned long long amount = 1000000000;
    const char *result = programmable_transaction(SENDER_ADDRESS, RECIPIENT_ADDRESS, amount);
    assert(result != NULL);
    printf("Result: %s\n", result);
    free((void *)result);
```

##### Execute programmable transaction with sponser
```cpp
    unsigned long long amount = 5400000000;
    const char *result = programmable_transaction_allow_sponser(SENDER_ADDRESS, RECIPIENT_ADDRESS, amount, SPONSER_ADDRESS);
    assert(result != NULL);
    printf("Result: %s\n", result);
    free((void *)result);
```

##### Execute programmable transaction with builder
```cpp
  // Create a new builder
    CProgrammableTransactionBuilder *builder = create_builder();
    assert(builder != NULL);

    //
    CArguments *coin = create_arguments();
    add_argument_gas_coin(coin);

    CArguments *amount = create_arguments();
    make_pure(builder, amount, bsc_basic("u64", "1000000000000"));

    add_split_coins_command(builder, coin, amount);

    // Add a transfer object command
    CArguments *agrument = create_arguments();
    add_argument_result(agrument, 0);
    CArguments *recipient = create_arguments();
    make_pure(builder, recipient, bsc_basic("address", RECIPIENT_ADDRESS));
    add_transfer_object_command(builder, agrument, recipient);

    // Execute the builder
    const char *result = execute_transaction(builder, SENDER_ADDRESS, 5000000);
    assert(result != NULL);
    printf("Result: %s\n", result);
```

##### To get and execute transaction using multisig
```cpp
    // Step 1: Create a multisig
    const char *addresses[] = {"0x013c740d731b06bb7447316e7b43ea6120d808d07cd0a8a0c6f391930bd449dd", "0x2107184d961804e3cbeef48106a7384d11d90f5a050fde0709da8e079450b824", "0x3d8c53148ba895d5aaa4a604af9864dd041fb409977fdfacc313f296f36faa77"};
    CStringArray addr_array = {addresses, 3};

    unsigned char weights_data[] = {1, 1, 1};
    CU8Array weights = {weights_data, 3, NULL};

    uint16_t threshold = 2;

    // Test get_or_create_multisig
    CMultiSig multisig = get_or_create_multisig(addr_array, weights, threshold);
    if (multisig.error)
    {
        printf("Error creating multisig: %s\n", multisig.error);
    }
    else
    {
        printf("Multisig Address: %s\n", multisig.address);
        printf("Multisig Bytes: ");
        print_hex(multisig.bytes.data, multisig.bytes.len);
    }

    // Step 2: Create a transaction
    const char *from_address = "0x5e4f2cce89e8c5f634b4692fdad3e1345b88aa90546ccaa417fd8a5b0591a21c";
    const char *to_address = "0x7bee59cf2c25539bb267b7d26ae8722f1dfe5112949727648f7b17de0ea72432";
    uint64_t amount = 1000; // Sample transfer amount

    CU8Array tx = create_transaction(from_address, to_address, amount);
    if (tx.error)
    {
        printf("Error creating transaction: %s\n", tx.error);
    }
    else
    {
        printf("Transaction bytes: ");
        print_hex(tx.data, tx.len);
    }

    // Step 3: Sign and execute the multisig transaction
    const char *result = sign_and_execute_transaction_miltisig(multisig.bytes, tx, addr_array);
    if (result)
    {
        printf("Error signing and executing transaction: %s\n", result);
    }
    else
    {
        printf("Transaction executed successfully.\n");
    }
```

### Using-Unreal-Sui-SDK-with-blueprint
**Create Wallet**
![](./Resource/CreateWallet.png)

**Import Wallet**
![](./Resource/ImportWallet.png)

**Send Transaction**
![](./Resource/Transaction.png)

**Request Faucet**
![](./Resource/RequestFaucet.png)

**MintNFT**
![](./Resource/MintNFT.png)

**Multisign**
![](./Resource/Multisign.png)

### Examples ###

The SDK comes with several examples that show how to leverage the Rust2C-Sui-SDK to its full potential. The examples include Wallet Creation and Management, Token Transfers,  NFT Minting, Account Funding, and Multi-signature.


### License ###
This project is licensed under the Apache-2.0 License. Refer to the LICENSE.txt file for details.

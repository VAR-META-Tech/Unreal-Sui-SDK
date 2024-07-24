// Fill out your copyright notice in the Description page of Project Settings.

#include "SuiSDKUnrealLogic.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "Components/ComboBoxString.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "sui_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <cstdint>
#include <sstream>
#include <iomanip>
#include <cstring> // For memcpy

#if PLATFORM_MAC
#import <Cocoa/Cocoa.h>
#endif

MultiSig multisig;
CU8Array resultTX;
CSuiObjectDataArray arrayNFT;
const char *package_id = "0xd1efbd86210322b550a8d6017ad5113fda2bd4f486593096f83e7b9ce3cbd002";

const char *FstringToChar(FString InputString)
{
    // // Convert FString to const char*
    // std::string MyStdString(TCHAR_TO_UTF8(*text));
    // returnvalue = MyStdString.c_str();
    // printf("  returnvalue: %s\n", returnvalue);
    // return returnvalue;

    // Convert FString to UTF-8 using FTCHARToUTF8, which is a helper class for conversion
    FTCHARToUTF8 Convert(*InputString); // Pass the TCHAR pointer (FString's underlying pointer)

    // Allocate memory for the output buffer (add 1 for null-terminator)
    char *Buffer = new char[Convert.Length() + 1];

    // Copy the UTF-8 data from the converter to the buffer
    FMemory::Memcpy(Buffer, Convert.Get(), Convert.Length());

    // Null-terminate the string
    Buffer[Convert.Length()] = '\0';

    // Return the buffer - remember to deallocate this in the caller to avoid memory leaks
    return Buffer;
}

void USuiSDKUnrealLogic::OnInitApp(class UWidget *TargetComboBox)
{
    UComboBoxString *walletsCombobox = Cast<UComboBoxString>(TargetComboBox);
    if (walletsCombobox)
    {
        // Clear existing options
        walletsCombobox->ClearOptions();
        WalletList wallet_list = get_wallets();
        for (size_t i = 0; i < wallet_list.length; ++i)
        {
            Wallet wallet = wallet_list.wallets[i];
            printf("Wallet %zu:\n", i + 1);
            printf("  Address: %s\n", wallet.address);
            printf("  Mnemonic: %s\n", wallet.mnemonic);
            printf("  Public Base64 Key: %s\n", wallet.public_base64_key);
            printf("  Private Key: %s\n", wallet.private_key);
            printf("  Key Scheme: %s\n", wallet.key_scheme);
            walletsCombobox->AddOption(FString(wallet.address));
        }
        free_wallet_list(wallet_list);
        walletsCombobox->SetSelectedIndex(0);
    }
}

void USuiSDKUnrealLogic::CopyTextToClipboard(const FString &text)
{
#if PLATFORM_MAC
    // Convert FString to NSString
    NSString *ClipboardText = [NSString stringWithFString:text];

    // Create a pasteboard and clear its content
    NSPasteboard *Pasteboard = [NSPasteboard generalPasteboard];
    [Pasteboard clearContents];

    // Set the NSString to the pasteboard
    [Pasteboard setString:ClipboardText forType:NSPasteboardTypeString];
#else
    // Use the default implementation for other platforms
    FPlatformApplicationMisc::ClipboardCopy(*text);
#endif
}

void USuiSDKUnrealLogic::OnBtnGenerateClicked(FString key_scheme, FString word_length, FString &mnemonic, FString &address, FString &privateKey, FString &publicKey)
{
    const char *_key_scheme = FstringToChar(key_scheme);
    const char *_word_length = FstringToChar(word_length);

    Wallet *wallet = generate_wallet(_key_scheme, _word_length);

    address = wallet->address;
    privateKey = wallet->private_key;
    publicKey = wallet->public_base64_key;
    mnemonic = wallet->mnemonic;

    printf("  Address: %s\n", wallet->address);
    printf("  Mnemonic: %s\n", wallet->mnemonic);
    printf("  Public Base64 Key: %s\n", wallet->public_base64_key);
    printf("  Private Key: %s\n", wallet->private_key);

    free_wallet(wallet);
}

void USuiSDKUnrealLogic::OnBtnGetWalletPrivateKeyClicked(FString importprivateKey, FString &mnemonic, FString &address, FString &privateKey, FString &publicKey)
{
    const char *privateConchar = FstringToChar(importprivateKey);
    printf("  privateConchar: %s\n", privateConchar);
    import_from_private_key(privateConchar);
}

void USuiSDKUnrealLogic::OnBtnGetWalletMnemonicClicked(FString importmnemonic, FString &mnemonic, FString &address, FString &privateKey, FString &publicKey)
{
    const char *mnemonicConchar = FstringToChar(importmnemonic);
    printf("  mnemonicConchar: %s\n", mnemonicConchar);
    char *returnAddress = import_from_mnemonic(mnemonicConchar);
    address = returnAddress;
}

void USuiSDKUnrealLogic::OnBtnGetWallByCurrentAddress(FString currentAddress, FString &mnemonic, FString &address, FString &privateKey, FString &publicKey)
{

    const char *currentAddressSelected = FstringToChar(currentAddress);
    printf("  currentAddressSelected: %s\n", currentAddressSelected);
    // Wallet* wallet =  get_wallet_from_address(currentAddressSelected);

    // address = wallet->address;
    // privateKey = wallet->private_key;
    // publicKey = wallet->public_base64_key;
    // mnemonic = wallet->mnemonic;

    // printf("  Address: %s\n",wallet->address);
    // printf("  Mnemonic: %s\n", wallet->mnemonic);
    // printf("  Public Base64 Key: %s\n", wallet->public_base64_key);
    // printf("  Private Key: %s\n", wallet->private_key);

    //  free_wallet(wallet);
    WalletList walletlist = get_wallets();
    for (size_t i = 0; i < walletlist.length; ++i)
    {
        Wallet wallet = walletlist.wallets[i];
        if (strcmp(currentAddressSelected, wallet.address) == 0)
        {
            address = wallet.address;
            privateKey = wallet.private_key;
            publicKey = wallet.public_base64_key;
            mnemonic = wallet.mnemonic;

            printf("  Address: %s\n", wallet.address);
            printf("  Mnemonic: %s\n", wallet.mnemonic);
            printf("  Public Base64 Key: %s\n", wallet.public_base64_key);
            printf("  Private Key: %s\n", wallet.private_key);
            break;
        }
    }
    free_wallet_list(walletlist);
}

void USuiSDKUnrealLogic::OnBtnGetBalanceByCurrentAddress(FString currentAddress, FString &returnCoinType, FString &returnTotalBalance)
{
    const char *currentAddressSelected = FstringToChar(currentAddress);

    Balance balance = get_balance_sync(currentAddressSelected);
    if (balance.coin_type == NULL)
    {
        printf("Failed to fetch balance.\n");
    }
    else
    {
        printf(" *** Balance ***\n");
        printf("Coin Type: %s\n", balance.coin_type);
        returnCoinType = balance.coin_type;
        printf("Coin Object Count: %zu\n", balance.coin_object_count);
        std::ostringstream oss;

        // Stream the uint64_t values into the string stream as a comma-separated list
        oss << balance.total_balance[0];

        std::string result = oss.str();
        returnTotalBalance = result.c_str();
        printf("Total Balance: %s\n", result.c_str());
        // Convert the stream to a string and output it

        // __uint128_t total_balance = ((__uint128_t)balance.total_balance[1] << 64) | balance.total_balance[0];
        // char total_balance_str[40]; // Enough to hold 2^128-1
        // snprintf(total_balance_str, sizeof(total_balance_str), "%llu", total_balance);
        // printf("Total Balance: %s\n", total_balance_str);
        // returnTotalBalance = total_balance_str;
        // printf(" *** Balance ***\n");
    }
    // Free allocated resources
    free_balance(balance);
}

void USuiSDKUnrealLogic::OnBtnTransaction(FString sendAddress, FString receiveAddress, int amount, FString &resultTrans, bool &IsTransSucceed)
{
    const char *currentsendAddress = FstringToChar(sendAddress);
    const char *currentreceiveAddress = FstringToChar(receiveAddress);
    const char *result = programmable_transaction(currentsendAddress, currentreceiveAddress, amount);
    resultTrans = result;
    printf("OnBtnTransaction : %s\n", result);
    if (strcmp(result, "Transaction completed successfully") == 0)
    {
        IsTransSucceed = true;
    }
    else
    {
        IsTransSucceed = false;
    }
}

void USuiSDKUnrealLogic::OnBtnRequestFaucet(FString faucetAddress, FString &resultFaucet, bool &IsFaucetSucceed)
{
    const char *faucetaddressstr = FstringToChar(faucetAddress);
    const char *result = request_tokens_from_faucet_(faucetaddressstr);
    resultFaucet = result;
    printf("request_tokens_from_faucet_: %s\n", result);
    if (strcmp(result, "Request Faucet successful") == 0)
    {
        IsFaucetSucceed = true;
    }
    else
    {
        IsFaucetSucceed = false;
    }
}
// std::string BytesToHex(const uint8_t *data, size_t len)
// {
//     if (data == nullptr || len == 0)
//     {
//         return "";
//     }

//     std::string hex;
//     hex.reserve(len * 2); // Reserve space to avoid multiple reallocations

//     for (size_t i = 0; i < len; ++i)
//     {
//         std::stringstream ss;
//         ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]);
//         hex += ss.str();
//     }

//     return hex;
// }

void USuiSDKUnrealLogic::OnBtnGetMultisignClicked(TArray<FString> arrayAddress, TArray<int> arrayWeight, int threshold, FString &multisignAddress, FString &multisignBytes, FString &BalanceReturn, FString &resultError, bool &IsFaucetSucceed)
{
    // const char *addresses[] = {"0x013c740d731b06bb7447316e7b43ea6120d808d07cd0a8a0c6f391930bd449dd",
    //                            "0x2691bf90af73ce452f71ef081c1d8f00a9d8a3506101c5def54f6bed8c1be733",
    //                            "0x66e350a92a4ddf98906f4ae1a208a23e40047105f470c780d2d6bec139031f75"};
    const char *addresses[arrayAddress.Num()];
    for (int32 i = 0; i < arrayAddress.Num(); ++i)
    {
        // Convert FString to const char* using TCHAR_TO_ANSI
        addresses[i] = FstringToChar(arrayAddress[i]);
    }
    // uint8_t weights_data[] = {1, 1, 1};
    uint8_t weights_data[arrayWeight.Num()];
    for (int32 i = 0; i < arrayWeight.Num(); ++i)
    {
        // Convert FString to const char* using TCHAR_TO_ANSI
        weights_data[i] = arrayWeight[i];
        printf("weights_data %d \n", weights_data[i]);
    }
    CStringArray cstring_array = {addresses, arrayAddress.Num()};
    CU8Array cu8_array = {weights_data, arrayWeight.Num()};

    uint16_t threshold_ = threshold;
    printf("threshold_ %d \n", threshold_);
    printf("threshold %d \n", threshold);
    multisig = get_or_create_multisig(cstring_array, cu8_array, threshold_);

    printf("get_or_create_multisig: %s\n", multisig.address);
    multisignAddress = multisig.address;
    // Convert to hex string
    multisignBytes = BytesToHex(multisig.bytes.data, multisig.bytes.len);
    // Print the hex string
    std::cout << "Hex String: " << FstringToChar(multisignBytes) << std::endl;

    Balance balance = get_balance_sync(multisig.address);
    std::ostringstream oss;
    // Stream the uint64_t values into the string stream as a comma-separated list
    oss << balance.total_balance[0];
    std::string result = oss.str();
    BalanceReturn = result.c_str();
    printf("Total Balance: %s\n", result.c_str());
    free_balance(balance);

    // // Free the error message if it was allocated
    // // if (result.error != NULL)
    // // {
    // //     free((void *)result.error);
    // // }

    // // CU8Array multisig_bytes = multisig.bytes;

    // // uint8_t tx_data[] = {0x05, 0x06, 0x07, 0x08}; // Sample data
    // // CU8Array tx = result;

    // const char *addresses_data[] = {"0x013c740d731b06bb7447316e7b43ea6120d808d07cd0a8a0c6f391930bd449dd",
    //                                 "0x2691bf90af73ce452f71ef081c1d8f00a9d8a3506101c5def54f6bed8c1be733"};
    // CStringArray addresses2 = {addresses_data, 2};

    // // Call the Rust function
    // const char *result2 = sign_and_execute_transaction(multisig.bytes, result, addresses2);

    // if (result2 != NULL)
    // {
    //     printf("Result: %s\n", result2);
    //     // Free the result when done
    //     free((void *)result2);
    // }
    // else
    // {
    //     printf("Error occurred\n");
    // }
}

void USuiSDKUnrealLogic::OnBtnCreateTransMultisignClicked(FString sendAddress, FString receiveAddress, int mount, FString &multisignTransBytes, FString &resultTrans, bool &IsTransSucceed)
{
    const char *from_address = FstringToChar(sendAddress);
    const char *to_address = FstringToChar(receiveAddress);
    uint64_t amount = mount;

    resultTX = create_transaction(from_address, to_address, amount);
    multisignTransBytes = BytesToHex(resultTX.data, resultTX.len);
    if (resultTX.error == NULL)
    {
        printf("Transaction created successfully.\n");
        printf("Data length: %u\n", resultTX.len);
        printf("Data: ");
        for (uint32_t i = 0; i < resultTX.len; i++)
        {
            printf("%02x", resultTX.data[i]);
        }
        printf("\n");
    }
    else
    {
        printf("Error: %s\n", resultTX.error);
        free((void *)resultTX.error); // Free the error message
    }
}

void USuiSDKUnrealLogic::OnBtnSignandExecuteTransactionClicked(TArray<FString> arrayAddress, FString &ReturnBalance, FString &result, bool &IsSucceed)
{
    const char *addresses_data[arrayAddress.Num()];
    for (int32 i = 0; i < arrayAddress.Num(); ++i)
    {
        // Convert FString to const char* using TCHAR_TO_ANSI
        addresses_data[i] = FstringToChar(arrayAddress[i]);
        printf("addresses_data Vote: %s\n", addresses_data[i]);
    }
    CStringArray addresses2 = {addresses_data, arrayAddress.Num()};
    // Call the Rust function
    const char *result2 = sign_and_execute_transaction(multisig.bytes, resultTX, addresses2);

    if (result2 != NULL)
    {
        printf("Result: %s\n", result2);
        // Free the result when done
        free((void *)result2);
    }
    else
    {
        printf("Error occurred\n");
    }

    Balance balance = get_balance_sync(multisig.address);
    std::ostringstream oss;
    // Stream the uint64_t values into the string stream as a comma-separated list
    oss << balance.total_balance[0];
    std::string resultBalance = oss.str();
    ReturnBalance = resultBalance.c_str();
    printf("Total Balance: %s\n", resultBalance.c_str());
    free_balance(balance);
}

void USuiSDKUnrealLogic::OnBtnMintNFTClicked(FString sendNFTAddress, FString nftName, FString nftDescription, FString nftURL, FString &resultFstring, bool &IsSucceed)
{
    const char *sender_address = FstringToChar(sendNFTAddress);
    const char *name = FstringToChar(nftName);
    const char *description = FstringToChar(nftDescription);
    const char *url = FstringToChar(nftURL);

    const char *result = mint_nft(package_id, sender_address, name, description, url);

    // const char *sender_address = "0x013c740d731b06bb7447316e7b43ea6120d808d07cd0a8a0c6f391930bd449dd";
    // const char *nft_id = "0x68ce773d046e42959757a800af4db34ce5a725630841824d2fd02b08c86d476e";
    // const char *recipient_address = "0x66e350a92a4ddf98906f4ae1a208a23e40047105f470c780d2d6bec139031f75";
    // const char *result = transfer_nft(package_id, sender_address, nft_id, recipient_address);

    if (result != NULL)
    {
        printf("Result: %s\n", result);
        resultFstring = result;
        // Free the result when done
        free((void *)result);
    }
    else
    {
        printf("Error occurred\n");
    }
}

void USuiSDKUnrealLogic::OnBtnNFTTransactionClicked(FString sendNFTAddress, FString nft_id_, FString receiveNFTaddress, FString &resultError, bool &IsSucceed)
{
    const char *sender_address = FstringToChar(sendNFTAddress);
    const char *nft_id = FstringToChar(nft_id_);
    const char *recipient_address = FstringToChar(receiveNFTaddress);
    const char *result = transfer_nft(package_id, sender_address, nft_id, recipient_address);

    if (result != NULL)
    {
        printf("Result: %s\n", result);
        resultError = result;
        // Free the result when done
        free((void *)result);
    }
    else
    {
        printf("Error occurred\n");
    }
}

void USuiSDKUnrealLogic::OnBtnNFTGetListData(FString curNFTAddress, int &lengthArray, FString &resultError, bool &IsSucceed)
{
    const char *package_id_type = "0xd1efbd86210322b550a8d6017ad5113fda2bd4f486593096f83e7b9ce3cbd002::nft::NFT";
    const char *cur_address = FstringToChar(curNFTAddress);
    arrayNFT = get_wallet_objects("0x013c740d731b06bb7447316e7b43ea6120d808d07cd0a8a0c6f391930bd449dd", package_id_type);

    if (arrayNFT.data == NULL)
    {
        printf("Failed to get Sui object data list\n");
    }
    lengthArray = 3;
    for (size_t i = 0; i < arrayNFT.len; i++)
    {
        printf("Object ID: %s\n", arrayNFT.data[i].object_id);
        printf("Version: %llu\n", arrayNFT.data[i].version);
        printf("Digest: %s\n", arrayNFT.data[i].digest);
        printf("Type: %s\n", arrayNFT.data[i].type_);
        printf("Owner: %s\n", arrayNFT.data[i].owner);
        printf("Previous Transaction: %s\n", arrayNFT.data[i].previous_transaction);
        printf("Storage Rebate: %llu\n", arrayNFT.data[i].storage_rebate);
        printf("Display: %s\n", arrayNFT.data[i].display);
        printf("Content: %s\n", arrayNFT.data[i].content);
        printf("BCS: %s\n", arrayNFT.data[i].bcs);
        printf("\n");
    }

    free_sui_object_data_list(arrayNFT);
}

void USuiSDKUnrealLogic::OnBtnNFTGetDataItem(FString curNFTAddress, int index, FString &object_id, FString &version, FString &digest, FString &Type, FString &description, FString &name, FString &nftUrl, FString &resultError, bool &IsSucceed)
{
    // object_id = arrayNFT.data[index].object_id;
    // version = FString::Printf(TEXT("%llu"), arrayNFT.data[index].version);
    // digest = arrayNFT.data[index].digest;
    // Type = arrayNFT.data[index].type_;
    object_id = package_id;
    version = package_id;
    digest = package_id;
    Type = package_id;

    // FString JsonString = TEXT(R"({
    //     "description": "NFT description",
    //     "id": {
    //         "id": "0x1028ae308ad211d4a40b4405b88b9764da55936d766c370cf909335e7459285a"
    //     },
    //     "name": "New NFT",
    //     "url": "https://img.freepik.com/free-photo/abstract-autumn-beauty-multi-colored-leaf-vein-pattern-generated-by-ai_188544-9871.jpg?size=626&ext=jpg&ga=GA1.1.2008272138.1721347200&semt=ais_user"
    // })");

    // TSharedPtr<FJsonObject> JsonObject;
    // TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

    // if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
    // {
    //     // Access values from the JSON object
    //     FString Description = JsonObject->GetStringField("description");

    //     TSharedPtr<FJsonObject> IdObject = JsonObject->GetObjectField("id");
    //     FString Id = IdObject->GetStringField("id");

    //     FString Name = JsonObject->GetStringField("name");
    //     FString Url = JsonObject->GetStringField("url");

    //     // Print the values to the output log
    //     UE_LOG(LogTemp, Warning, TEXT("Description: %s"), *Description);
    //     UE_LOG(LogTemp, Warning, TEXT("ID: %s"), *Id);
    //     UE_LOG(LogTemp, Warning, TEXT("Name: %s"), *Name);
    //     UE_LOG(LogTemp, Warning, TEXT("URL: %s"), *Url);
    // }
    // else
    // {
    //     UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON."));
    // }
}

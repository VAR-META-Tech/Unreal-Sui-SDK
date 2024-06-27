// Fill out your copyright notice in the Description page of Project Settings.

#include "SuiSDKUnrealLogic.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "Components/ComboBoxString.h"
#include "sui_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <cstdint>
#if PLATFORM_MAC
#import <Cocoa/Cocoa.h>
#endif

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

void USuiSDKUnrealLogic::OnBtnTransaction(FString sendAddress, FString receiveAddress, int amount)
{
    const char *currentsendAddress = FstringToChar(sendAddress);
    const char *currentreceiveAddress = FstringToChar(receiveAddress);
    const char *result = programmable_transaction(currentsendAddress, currentreceiveAddress, amount);
    printf("%s\n", result);
}

void USuiSDKUnrealLogic::OnBtnRequestFaucet(FString faucetAddress)
{
    const char *faucetaddressstr = FstringToChar(faucetAddress);
    const char *result = request_tokens_from_faucet_(faucetaddressstr);
    printf("request_tokens_from_faucet_: %s\n", result);
}

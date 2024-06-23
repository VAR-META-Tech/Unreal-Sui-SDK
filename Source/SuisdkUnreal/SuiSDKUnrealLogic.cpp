// Fill out your copyright notice in the Description page of Project Settings.


#include "SuiSDKUnrealLogic.h"
#include "GenericPlatform/GenericPlatformMisc.h"
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

void USuiSDKUnrealLogic::OnInitApp()
{
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
    }

    free_wallet_list(wallet_list);
}

void USuiSDKUnrealLogic::CopyTextToClipboard(const FString& text)
{
    #if PLATFORM_MAC
    // Convert FString to NSString
    NSString* ClipboardText = [NSString stringWithFString: text];

    // Create a pasteboard and clear its content
    NSPasteboard* Pasteboard = [NSPasteboard generalPasteboard];
    [Pasteboard clearContents];

    // Set the NSString to the pasteboard
    [Pasteboard setString:ClipboardText forType:NSPasteboardTypeString];
#else
    // Use the default implementation for other platforms
    FPlatformApplicationMisc::ClipboardCopy(*text);
#endif
}

void USuiSDKUnrealLogic::OnBtnGenerateClicked(FString &mnemonic,FString &address, FString &privateKey, FString &publicKey)
{
Wallet* wallet =    generate_wallet();
        
address = wallet->address;
privateKey = wallet->private_key;
publicKey = wallet->public_base64_key;
mnemonic = wallet->mnemonic;

printf("  Address: %s\n",wallet->address);
printf("  Mnemonic: %s\n", wallet->mnemonic);
printf("  Public Base64 Key: %s\n", wallet->public_base64_key);
printf("  Private Key: %s\n", wallet->private_key);
import_from_private_key(wallet->private_key);
free_wallet(wallet);
}

void USuiSDKUnrealLogic::OnBtnGetWalletPrivateKeyClicked(FString importprivateKey, FString &mnemonic, FString &address, FString &privateKey, FString &publicKey)
{

// Convert FString to const char*
std::string MyStdString(TCHAR_TO_UTF8(*importprivateKey));
const char *privateConchar = MyStdString.c_str();
printf("  privateConchar: %s\n", privateConchar);
import_from_private_key(privateConchar);
WalletList walletlist= get_wallets();
 for (size_t i = 0; i < walletlist.length; ++i)
    {
        Wallet wallet = walletlist.wallets[i];
        if (strcmp(privateConchar, wallet.private_key ) == 0)
        {
            address = wallet.address;
            privateKey = wallet.private_key;
            publicKey = wallet.public_base64_key;
            mnemonic = wallet.mnemonic;

            printf("  Address: %s\n",wallet.address);
            printf("  Mnemonic: %s\n", wallet.mnemonic);
            printf("  Public Base64 Key: %s\n", wallet.public_base64_key);
            printf("  Private Key: %s\n", wallet.private_key);
           
            break;
        }
       
       
    }
free_wallet_list(walletlist);
}

void USuiSDKUnrealLogic::OnBtnGetWalletMnemonicClicked(FString importmnemonic, FString &mnemonic, FString &address, FString &privateKey, FString &publicKey)
{
   // Convert FString to const char*
std::string MyStdString(TCHAR_TO_UTF8(*importmnemonic));
const char *mnemonicConchar = MyStdString.c_str();
printf("  mnemonicConchar: %s\n", mnemonicConchar);
char * returnAddress = import_from_mnemonic(mnemonicConchar);
address = returnAddress;
// WalletList walletlist= get_wallets();
//  for (size_t i = 0; i < walletlist.length; ++i)
//     {
//         Wallet wallet = walletlist.wallets[i];
//         printf("  Address: %s\n",wallet.address);
//         printf("  Mnemonic: %s\n", wallet.mnemonic);
//         printf("  Public Base64 Key: %s\n", wallet.public_base64_key);
//         printf("  Private Key: %s\n", wallet.private_key);

//         if (strcmp(mnemonicConchar, wallet.mnemonic ) == 0)
//         {
//             address = wallet.address;
//             privateKey = wallet.private_key;
//             publicKey = wallet.public_base64_key;
//             mnemonic = wallet.mnemonic;
//             break;
//         }
       
       
//     }
// free_wallet_list(walletlist);
}

void USuiSDKUnrealLogic::OnBtnGetWallByCurrentAddress(FString currentAddress, FString &mnemonic, FString &address, FString &privateKey, FString &publicKey)
{
//Convert FString to const char*
std::string MyStdString(TCHAR_TO_UTF8(*currentAddress));
const char *currentAddressSelected = MyStdString.c_str();
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
WalletList walletlist= get_wallets();
 for (size_t i = 0; i < walletlist.length; ++i)
    {
        Wallet wallet = walletlist.wallets[i];
        if (strcmp(currentAddressSelected, wallet.address ) == 0)
        {
            address = wallet.address;
            privateKey = wallet.private_key;
            publicKey = wallet.public_base64_key;
            mnemonic = wallet.mnemonic;

            printf("  Address: %s\n",wallet.address);
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
    //Convert FString to const char*
std::string MyStdString(TCHAR_TO_UTF8(*currentAddress));
const char *currentAddressSelected = MyStdString.c_str();
 Balance balance = get_balance_sync(currentAddressSelected);
    if (balance.coin_type == NULL) {
        printf("Failed to fetch balance.\n");
    } else {
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
//Convert FString to const char*
std::string MyStdString(TCHAR_TO_UTF8(*sendAddress));
const char *currentsendAddress = MyStdString.c_str();
std::string MyStdString2(TCHAR_TO_UTF8(*receiveAddress));
const char *currentreceiveAddress = MyStdString2.c_str();
const char* result = programmable_transaction(currentsendAddress, currentreceiveAddress,amount);
    printf("%s\n", result);
}

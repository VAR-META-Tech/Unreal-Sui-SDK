// Fill out your copyright notice in the Description page of Project Settings.


#include "SuiSDKUnrealLogic.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "sui_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <string>
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



// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HAL/PlatformApplicationMisc.h"
#include "Misc/AutomationTest.h"

#include "SuiSDKUnrealLogic.generated.h"

/**
 *
 */
UCLASS()
class SUISDKUNREAL_API USuiSDKUnrealLogic : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "OnInitApp"), Category = "SuiSDKUnrealLogic")
	static void OnInitApp(class UWidget *TargetComboBox);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CopyTextToClipboard"), Category = "SuiSDKUnrealLogic")
	static void CopyTextToClipboard(const FString &text);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "OnBtnGenerateClicked"), Category = "SuiSDKUnrealLogic")
	static void OnBtnGenerateClicked(FString key_scheme, FString word_length, FString &mnemonic, FString &address, FString &privateKey, FString &publicKey);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "OnBtnGetWalletPrivateKeyClicked"), Category = "SuiSDKUnrealLogic")
	static void OnBtnGetWalletPrivateKeyClicked(FString importprivateKey, FString &mnemonic, FString &address, FString &privateKey, FString &publicKey);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "OnBtnGetWalletMnemonicClicked"), Category = "SuiSDKUnrealLogic")
	static void OnBtnGetWalletMnemonicClicked(FString importmnemonic, FString &mnemonic, FString &address, FString &privateKey, FString &publicKey);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "OnBtnGetWallByCurrentAddress"), Category = "SuiSDKUnrealLogic")
	static void OnBtnGetWallByCurrentAddress(FString currentAddress, FString &mnemonic, FString &address, FString &privateKey, FString &publicKey);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "OnBtnGetBalanceByCurrentAddress"), Category = "SuiSDKUnrealLogic")
	static void OnBtnGetBalanceByCurrentAddress(FString currentAddress, FString &returnCoinType, FString &returnTotalBalance);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "OnBtnTransaction"), Category = "SuiSDKUnrealLogic")
	static void OnBtnTransaction(FString sendAddress, FString receiveAddress, int mount, FString &resultTrans, bool &IsTransSucceed);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "OnBtnRequestFaucet"), Category = "SuiSDKUnrealLogic")
	static void OnBtnRequestFaucet(FString faucetAddress, FString &resultFaucet, bool &IsFaucetSucceed);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "OnBtnGetMultisignClicked"), Category = "SuiSDKUnrealLogic")
	static void OnBtnGetMultisignClicked(TArray<FString> arrayAddress, TArray<int> arrayWeight, int threshold, FString &multisignAddress, FString &multisignBytes, FString &Balance, FString &result, bool &IsFaucetSucceed);
};

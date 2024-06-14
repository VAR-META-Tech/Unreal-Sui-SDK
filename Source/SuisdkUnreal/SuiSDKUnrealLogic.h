// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SuiSDKUnrealLogic.generated.h"

/**
 * 
 */
UCLASS()
class SUISDKUNREAL_API USuiSDKUnrealLogic : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "OnInitApp"), Category = "SuiSDKUnrealLogic")
	static void OnInitApp();
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "OnBtnGenerateClicked"), Category = "SuiSDKUnrealLogic")
	static void OnBtnGenerateClicked(FString &mnemonic,FString &address,FString &privateKey,FString &publicKey);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "OnBtnGetWalletPrivateKeyClicked"), Category = "SuiSDKUnrealLogic")
	static void OnBtnGetWalletPrivateKeyClicked(FString importprivateKey,FString &mnemonic,FString &address,FString &privateKey,FString &publicKey);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "OnBtnGetWalletMnemonicClicked"), Category = "SuiSDKUnrealLogic")
	static void OnBtnGetWalletMnemonicClicked(FString importmnemonic,FString &mnemonic,FString &address,FString &privateKey,FString &publicKey);
};

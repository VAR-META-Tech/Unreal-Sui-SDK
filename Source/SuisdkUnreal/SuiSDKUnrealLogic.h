// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HAL/PlatformApplicationMisc.h"
#include "Misc/AutomationTest.h"
#include "Engine/Texture2D.h"

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
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "OnBtnImportWalletPrivateKeyClicked"), Category = "SuiSDKUnrealLogic")
	static void OnBtnImportWalletPrivateKeyClicked(FString importprivateKey, FString &mnemonic, FString &address, FString &privateKey, FString &publicKey);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "OnBtnImportWalletMnemonicClicked"), Category = "SuiSDKUnrealLogic")
	static void OnBtnImportWalletMnemonicClicked(FString importmnemonic, FString &mnemonic, FString &address, FString &privateKey, FString &publicKey);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "OnBtnGetWallByCurrentAddress"), Category = "SuiSDKUnrealLogic")
	static void OnBtnGetWallByCurrentAddress(FString currentAddress, FString &mnemonic, FString &address, FString &privateKey, FString &publicKey);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "OnBtnGetBalanceByCurrentAddress"), Category = "SuiSDKUnrealLogic")
	static void OnBtnGetBalanceByCurrentAddress(FString currentAddress, FString &returnCoinType, FString &returnTotalBalance);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "OnBtnTransaction"), Category = "SuiSDKUnrealLogic")
	static void OnBtnTransaction(FString sendAddress, FString receiveAddress, int mount, FString &resultTrans, bool &IsTransSucceed);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "OnBtnSponserTransaction"), Category = "SuiSDKUnrealLogic")
	static void OnBtnSponserTransaction(FString sendAddress, FString receiveAddress, FString sponserAddress, int mount, FString &resultTrans, bool &IsTransSucceed);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "OnBtnRequestFaucet"), Category = "SuiSDKUnrealLogic")
	static void OnBtnRequestFaucet(FString faucetAddress, FString &resultFaucet, bool &IsFaucetSucceed);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "OnBtnGetMultisignClicked"), Category = "SuiSDKUnrealLogic")
	static void OnBtnGetMultisignClicked(TArray<FString> arrayAddress, TArray<int> arrayWeight, int threshold, FString &multisignAddress, FString &multisignBytes, FString &ReturnBalance, FString &returnresult, bool &IsSucceed);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "OnBtnCreateTransMultisignClicked"), Category = "SuiSDKUnrealLogic")
	static void OnBtnCreateTransMultisignClicked(FString sendAddress, FString receiveAddress, int mount, FString &multisignTransBytes, FString &resultTrans, bool &IsTransSucceed);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "OnBtnSignandExecuteTransactionClicked"), Category = "SuiSDKUnrealLogic")
	static void OnBtnSignandExecuteTransactionClicked(TArray<FString> arrayAddress, FString &ReturnBalance, FString &result, bool &IsSucceed);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "OnBtnMintNFTClicked"), Category = "SuiSDKUnrealLogic")
	static void OnBtnMintNFTClicked(FString sendNFTAddress, FString nftName, FString nftDescription, FString nftURL, FString &result, bool &IsSucceed);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "OnBtnNFTTransactionClicked"), Category = "SuiSDKUnrealLogic")
	static void OnBtnNFTTransactionClicked(FString sendNFTAddress, FString nft_id, FString receiveNFTaddress, FString &result, bool &IsSucceed);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "OnBtnNFTGetListData"), Category = "SuiSDKUnrealLogic")
	static void OnBtnNFTGetListData(FString curNFTAddress, int &lengthArray, FString &result, bool &IsSucceed);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "OnBtnNFTGetDataItem"), Category = "SuiSDKUnrealLogic")
	static void OnBtnNFTGetDataItem(FString curNFTAddress, int index, FString &object_id, FString &version, FString &digest, FString &Type, FString &description, FString &name, FString &nftUrl, FString &result, bool &IsSucceed);
};

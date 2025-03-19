// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyTestCppLib.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLECHAT_API UMyTestCppLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "MyTestCPPLib")
	static FString GetMyFirstCPP();
	UFUNCTION(BlueprintCallable, Category = "Custom")
	static TArray<int32> GetRandom();
	UFUNCTION(BlueprintCallable, Category = "JudgeWinner")
	static bool JudgeNumber(const TArray<int32>& SecretNumber, const TArray<int32>& PlayerNumber, int32& OutStrikeCount, int32& OutBallCount, const bool& InHostTurn);
};

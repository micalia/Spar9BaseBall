// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLECHAT_API AMyGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	AMyGameMode();

	virtual void BeginPlay() override;

	// 서버가 생성한 숫자와 게임 상태
	TArray<int32> SecretNumber;
	int32 HostTries;
	int32 GuestTries;
	
	int32 HostStrikeCnt;
	int32 GuestStrikeCnt;
	
	int32 HostBallCnt;
	int32 GuestBallCnt;

	// 현재 게임의 진행 상태(Host, Guest)
	UPROPERTY(BlueprintReadWrite)
	bool bIsHostTurn;
	
	// 게임 시작
	void StartNewGame();

	// 사용자가 입력한 숫자 처리
	UFUNCTION(BlueprintCallable)
	void ProcessPlayerInput(const FString& PlayerInput);

};

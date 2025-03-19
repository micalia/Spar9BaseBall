// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"
#include "MyTestCppLib.h"

AMyGameMode::AMyGameMode()
{
	// 기본값 설정
	HostTries = 0;
	GuestTries = 0;
	bIsHostTurn = true; // 호스트의 턴부터 시작
}

void AMyGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (bIsHostTurn)
	{
		GEngine->AddOnScreenDebugMessage(-1, 99, FColor::Purple, FString::Printf(TEXT("Host Turn!!!")), true,
		                                 FVector2D(1, 1));

		UE_LOG(LogTemp, Log, TEXT("Host Turn!!!"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Guest Turn!!!"));
		GEngine->AddOnScreenDebugMessage(-1, 99, FColor::Purple, FString::Printf(TEXT("Guest Turn!!!")), true,
		                                 FVector2D(1, 1));
	}
	// 게임 시작
	StartNewGame();
}

void AMyGameMode::StartNewGame()
{
	// 새로운 3자리 숫자 생성
	SecretNumber = UMyTestCppLib::GetRandom();

	HostTries = 0;
	GuestTries = 0;
	HostStrikeCnt = 0;
	GuestStrikeCnt = 0;
	HostBallCnt = 0;
	GuestBallCnt = 0;
	bIsHostTurn = true;

	// 게임 상태 출력
	UE_LOG(LogTemp, Log, TEXT("새 게임이 시작되었습니다!"));
	if (bIsHostTurn)
	{
		GEngine->AddOnScreenDebugMessage(-1, 99, FColor::Purple, FString::Printf(TEXT("Host Turn!!!")), true,
										 FVector2D(1, 1));

		UE_LOG(LogTemp, Log, TEXT("Host Turn!!!"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Guest Turn!!!"));
		GEngine->AddOnScreenDebugMessage(-1, 99, FColor::Purple, FString::Printf(TEXT("Guest Turn!!!")), true,
										 FVector2D(1, 1));
	}
}

void AMyGameMode::ProcessPlayerInput(const FString& PlayerInput)
{
	// 숫자 입력 처리 (예: "/123")
	if (PlayerInput.Len() != 4 || PlayerInput[0] != '/')
	{
		// 잘못된 입력 처리

		UE_LOG(LogTemp, Log, TEXT("잘못된 입력입니다."));
		return;
	}

	TArray<int32> PlayerNumber;
	for (int32 i = 1; i < 4; i++)
	{
		PlayerNumber.Add(PlayerInput[i] - '0'); // 문자열에서 숫자 추출
	}

	// 유효성 검사: 숫자 중복 검사
	if (PlayerNumber[0] == PlayerNumber[1] || PlayerNumber[0] == PlayerNumber[2] || PlayerNumber[1] == PlayerNumber[2])
	{
		GEngine->AddOnScreenDebugMessage(-1, 99, FColor::Purple, FString::Printf(TEXT("숫자 중복이 포함된 입력입니다.")), true,
		                                 FVector2D(1, 1));

		UE_LOG(LogTemp, Log, TEXT("숫자 중복이 포함된 입력입니다."));
		return;
	}

	if (HostTries == GuestTries)
	{
		SecretNumber = UMyTestCppLib::GetRandom();
	}

	// 스트라이크 및 볼 계산
	int32 StrikeCount = 0;
	int32 BallCount = 0;
	bool bIsWinner = UMyTestCppLib::JudgeNumber(SecretNumber, PlayerNumber, StrikeCount, BallCount, bIsHostTurn);

	// 결과 출력
	if (bIsHostTurn)
	{
		if (StrikeCount == 0 && BallCount == 0)
		{
			GEngine->AddOnScreenDebugMessage(-1, 99, FColor::Purple, FString::Printf(TEXT("StrikeCnt & BallCnt = 0 / Host Out!!! Guest 승리 다시 게임이 시작됐다")), true,
											 FVector2D(1, 1));
			StartNewGame();
			return;
		}
		HostStrikeCnt += StrikeCount;
		HostBallCnt += BallCount;
		GEngine->AddOnScreenDebugMessage(-1, 99, FColor::Purple,
		                                 FString::Printf(TEXT("Host 결과: %dS %dB"), HostStrikeCnt, HostBallCnt), true, FVector2D(1, 1));

		UE_LOG(LogTemp, Log, TEXT("Host 결과: %dS %dB"), HostStrikeCnt, HostBallCnt);
		if (HostStrikeCnt >= 3)
		{
			GEngine->AddOnScreenDebugMessage(-1, 99, FColor::Purple, FString::Printf(TEXT("Host 승리 다시 게임이 시작됐다")), true,
			                                 FVector2D(1, 1));

			UE_LOG(LogTemp, Log, TEXT("Host 승리 다시 게임이 시작됐다"));
			StartNewGame();
			return;
		}
	}
	else
	{
		if (StrikeCount == 0 && BallCount == 0)
		{
			GEngine->AddOnScreenDebugMessage(-1, 99, FColor::Purple, FString::Printf(TEXT("StrikeCnt & BallCnt = 0 / Guest Out!!! Host 승리 다시 게임이 시작됐다")), true,
											 FVector2D(1, 1));
			StartNewGame();
			return;
		}
		GuestStrikeCnt += StrikeCount;
		GuestBallCnt += BallCount;
		GEngine->AddOnScreenDebugMessage(-1, 99, FColor::Purple,
		                                 FString::Printf(TEXT("Guest 결과: %dS %dB"), GuestStrikeCnt, GuestBallCnt), true, FVector2D(1, 1));

		UE_LOG(LogTemp, Log, TEXT("Guest 결과: %dS %dB"), GuestStrikeCnt, GuestBallCnt);
		if (GuestStrikeCnt >= 3)
		{
			GEngine->AddOnScreenDebugMessage(-1, 99, FColor::Purple, FString::Printf(TEXT("Guest 승리 다시 게임이 시작됐다")), true,
			                                 FVector2D(1, 1));

			UE_LOG(LogTemp, Log, TEXT("Guest 승리 다시 게임이 시작됐다"));
			StartNewGame();
			return;
		}
	}

	// 턴 변경 및 시도 횟수 관리
	if (bIsHostTurn)
	{
		HostTries++;
	}
	else
	{
		GuestTries++;
	}

	if (GuestTries >= 3 && HostTries >= 3)
	{
		GEngine->AddOnScreenDebugMessage(-1, 99, FColor::Purple, FString::Printf(TEXT("무승부 군 다시 게임을 시작하지")), true,
		                                 FVector2D(1, 1));
		UE_LOG(LogTemp, Log, TEXT("무승부 군 다시 게임을 시작하지"));
		StartNewGame();
		return;
	}

	// 턴 전환
	bIsHostTurn = !bIsHostTurn;

	if (bIsHostTurn)
	{
		GEngine->AddOnScreenDebugMessage(-1, 99, FColor::Purple, FString::Printf(TEXT("Host Turn!!!")), true,
		                                 FVector2D(1, 1));

		UE_LOG(LogTemp, Log, TEXT("Host Turn!!!"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Guest Turn!!!"));
		GEngine->AddOnScreenDebugMessage(-1, 99, FColor::Purple, FString::Printf(TEXT("Guest Turn!!!")), true,
		                                 FVector2D(1, 1));
	}
}

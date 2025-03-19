// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestCppLib.h"

FString UMyTestCppLib::GetMyFirstCPP()
{
	return FString(TEXT("Hello CPP lib in BP"));
}

TArray<int32> UMyTestCppLib::GetRandom()
{
	TArray<int32> Numbers;
// 스트라이크 테스트를 위해 임의값 할당
	Numbers.Add(2);
	Numbers.Add(4);
	Numbers.Add(5);
	return Numbers;
	
	/*for (int32 i = 0; i < 9; i++)
	{
		Numbers.Add(i);
	}

	TArray<int32> Result;

	for (int32 i = 0; i < 3; i++)
	{
		int32 RandomIndex = FMath::RandRange(0, Numbers.Num() - 1);
		Result.Add(Numbers[RandomIndex]);
		Numbers.RemoveAt(RandomIndex);
	}

	return Result;*/
}

bool UMyTestCppLib::JudgeNumber(const TArray<int32>& SecretNumber, const TArray<int32>& PlayerNumber,
                                int32& OutStrikeCount, int32& OutBallCount, const bool& InHostTurn)
{
	OutStrikeCount = 0;
	OutBallCount = 0;

	if (InHostTurn)
	{
		GEngine->AddOnScreenDebugMessage(-1, 99, FColor::Purple, FString::Printf(TEXT("Server %d %d %d : Host %d %d %d"), SecretNumber[0],  SecretNumber[1],  SecretNumber[2], PlayerNumber[0], PlayerNumber[1], PlayerNumber[2]),
			true, FVector2D(1, 1));
	}else
	{
		GEngine->AddOnScreenDebugMessage(-1, 99, FColor::Purple, FString::Printf(TEXT("Server %d %d %d : Guest %d %d %d"), SecretNumber[0],  SecretNumber[1],  SecretNumber[2], PlayerNumber[0], PlayerNumber[1], PlayerNumber[2]),
			true, FVector2D(1, 1));
	}

	// 3자리씩 비교하여 스트라이크, 볼, 아웃 계산
	for (int32 i = 0; i < 3; i++)
	{
		if (SecretNumber[i] == PlayerNumber[i])  // 동일한 자리와 숫자 -> 스트라이크
		{
			OutStrikeCount++;
		}
		else if (SecretNumber.Contains(PlayerNumber[i]))  // 다른 자리에서 동일한 숫자 -> 볼
		{
			OutBallCount++;
		}
	}

	// 결과를 반환 (S/B 계산)
	return OutStrikeCount == 3;  // 3S가 맞았을 때 게임 종료 처리
}

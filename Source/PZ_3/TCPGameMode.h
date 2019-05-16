// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TCPGameMode.generated.h"

class TCPClient;

USTRUCT(Blueprintable)
struct FUserData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString Name;

	UPROPERTY(BlueprintReadWrite)
	int32 Scores;
};

UCLASS()
class PZ_3_API ATCPGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	TCPClient * client;

	virtual void BeginPlay() override;

	TArray<unsigned char> Buff;

	bool WriteInt(int32 Value);

	bool WriteString(FString Value);

	bool WriteBytes(unsigned char * Data, int32 Size);

	int32 ReadInt(TArray<uint8> Data);

	FString ReadString(TArray<uint8> Data);

	~ATCPGameMode();

public:
	/*Player name should be 5 letters long*/ 
	UFUNCTION(BlueprintCallable) 
	void SavePlayerResult(FString PlayerName, int32 Scores);

	UFUNCTION(BlueprintCallable)
	TArray<FUserData> GetUserData();


};



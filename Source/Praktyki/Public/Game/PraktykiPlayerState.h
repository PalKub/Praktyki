// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PraktykiPlayerState.generated.h"

class UCurveVector;
class UPraktykiGameInstance;

/**
 * 
 */
UENUM(BlueprintType)
enum class ESectorNumber : uint8
{
	ESN_One UMETA(DisplayName = "SectorOne"),
	ESN_Two UMETA(DisplayName = "SectorTwo"),
	ESN_Three UMETA(DisplayName = "SectorThree")
};

USTRUCT(BlueprintType)
struct FLapInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	float LapTime = 0.f;

	UPROPERTY(BlueprintReadOnly)
	float SectorOneTime = 0.f;

	UPROPERTY(BlueprintReadOnly)
	float SectorTwoTime = 0.f;

	UPROPERTY(BlueprintReadOnly)
	float SectorThreeTime = 0.f;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLapTimeChangeSignature, float, LapTimeElapsed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnSectorCompletedSignature, ESectorNumber, SectorNumber, float, SectorTime, bool, bIsPurple);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLapCompletedSignature, FLapInfo, LapInfo, bool, bIsBestLap);

UCLASS()
class PRAKTYKI_API APraktykiPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnLapTimeChangeSignature OnLapTimeChangeDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnSectorCompletedSignature OnSectorCompletedDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnLapCompletedSignature OnLapTimeCompletedDelegate;

	void StartFinishTriggered();
	void SectorTwoTriggered();
	void SectorThreeTriggered();
	
private:
	UPROPERTY(EditDefaultsOnly)
	float RaceTimerTickFrequency = 0.1f;

	UPROPERTY()
	TObjectPtr<UCurveFloat> CurrentLapTimeAtDistance = nullptr;

	UPROPERTY()
	TObjectPtr<UCurveVector> CurrentLapLocationAtLapTime = nullptr;

	UPROPERTY()
	TObjectPtr<UCurveVector> CurrentLapRotationAtLapTime = nullptr;
	
	UPROPERTY()
	TObjectPtr<UCurveFloat> BestLapTimeAtDistanceCurve = nullptr;

	UPROPERTY()
	TObjectPtr<UCurveVector> BestLapLocationAtLapTime = nullptr;

	UPROPERTY()
	TObjectPtr<UCurveVector> BestLapRotationAtLapTime = nullptr;

	UPROPERTY()
	TArray<FLapInfo> LapsInfoArray = TArray<FLapInfo>();

	TObjectPtr<UPraktykiGameInstance> GameInstance = nullptr;
	
	FTimerHandle RaceTimer;
	float GameTimeAtLapStart = 0.f;
	float LapTimeElapsed = 0.f;
	float CurrentSectorOneTime = 0.f;
	float CurrentSectorTwoTime = 0.f;
	float CurrentSectorThreeTime = 0.f;
	float BestLapTime = 0.f;
	float BestSectorOneTime = 0.f;
	float BestSectorTwoTime = 0.f;
	float BestSectorThreeTime = 0.f;
	bool bRaceTimeMeasuringActive = false;
	bool bStartFinishTriggered = false;
	bool bSectorTwoTriggered = false;
	bool bSectorThreeTriggered = false;
	
	void StartRaceTimer();
	void StopRaceTimer();
	void PopulateLapInfoData();
};
// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlayerController/PraktykiPlayerVehicleController.h"
#include "PraktykiPlayerState.generated.h"

enum class EDamageMode : uint8;
class AGhostActor;
class APlayerVehiclePawn;
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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnLapTimeChangeSignature, float, LapTimeElapsed, float, Delta, bool, bIsValidLap, bool, CorrectRotation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnSectorCompletedSignature, ESectorNumber, SectorNumber, float, SectorTime, bool, bIsPurple, bool, bIsValidLap);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnLapCompletedSignature, FLapInfo, LapInfo, bool, bIsBestLap, bool, bIsValidLap);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimeRemainingChangedSignature, int32, TimeRemaining);

UCLASS()
class PRAKTYKI_API APraktykiPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	//** UI assigned delegates */
	UPROPERTY(BlueprintAssignable)
	FOnTimeRemainingChangedSignature OnTimeRemainingChangedDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FOnLapTimeChangeSignature OnLapTimeChangeDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnSectorCompletedSignature OnSectorCompletedDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnLapCompletedSignature OnLapTimeCompletedDelegate;
	//** end UI assigned delegates */

	//** UI callable functions */
	UFUNCTION(BlueprintCallable)
	FLapInfo GetBestLapInfo();

	UFUNCTION(BlueprintCallable)
	FLapInfo GetOptimalLapInfo();

	UFUNCTION(BlueprintCallable)
	int32 GetNumberOfLapsCompleted() const { return LapsInfoArray.Num(); }

	UFUNCTION(BlueprintCallable)
	EDamageMode GetDamageMode() const { return DamageMode; }
	//** end UI callable functions */

	TObjectPtr<AGhostActor> GetGhostActor() { return GhostPawn; }
	void StartFinishTriggered();
	void SectorTwoTriggered();
	void SectorThreeTriggered();
	void SetTimeLimit(const int32 NewTimeLimit) { TimeLimit = NewTimeLimit; }
	void SetShouldShowGhost(const bool bShouldShowGhost) { bShowGhost = bShouldShowGhost; }
	void InitializeTimeLimit();
	void ResetData();
	void InvalidateLap() { bIsValidLap = false; }
	void SetDamageMode(const EDamageMode NewDamageMode) { DamageMode = NewDamageMode; }

private:
	UPROPERTY(EditDefaultsOnly)
	float RaceTimerTickFrequency = 0.1f;

	UPROPERTY()
	TObjectPtr<UCurveFloat> CurrentDistanceAtLapTime = nullptr;

	UPROPERTY()
	TObjectPtr<UCurveFloat> BestDistanceAtLapTime = nullptr;

	UPROPERTY()
	TObjectPtr<UCurveFloat> CurrentLapTimeAtDistance = nullptr;

	UPROPERTY()
	TObjectPtr<UCurveFloat> BestLapTimeAtDistance = nullptr;

	UPROPERTY()
	TArray<FLapInfo> LapsInfoArray = TArray<FLapInfo>();
	
	EDamageMode DamageMode = EDamageMode::EDM_NoDamage;
	TObjectPtr<AGhostActor> GhostPawn = nullptr;
	TObjectPtr<UPraktykiGameInstance> GameInstance = nullptr;

	/** Lap data */
	FTransformCurve CurrentLapTransformAtLapTime;
	FTransformCurve BestLapTransformAtLapTime;
	FTimerHandle RaceTimer;
	FTimerHandle TimeRemainingTimer;
	float GameTimeAtLapStart = 0.f;
	float LapTimeElapsed = 0.f;
	float CurrentSectorOneTime = 0.f;
	float CurrentSectorTwoTime = 0.f;
	float CurrentSectorThreeTime = 0.f;
	float BestLapTime = 0.f;
	float BestSectorOneTime = 0.f;
	float BestSectorTwoTime = 0.f;
	float BestSectorThreeTime = 0.f;
	float BestLapSectorOne = 0.f;
	float BestLapSectorTwo = 0.f;
	float BestLapSectorThree = 0.f;
	float PreviousDistance = 0.f;
	bool bRaceTimeMeasuringActive = false;
	bool bStartFinishTriggered = false;
	bool bSectorTwoTriggered = false;
	bool bSectorThreeTriggered = false;
	bool bIsValidLap = true;
	int32 TimeLimit = 0.f;
	int32 TimeRemaining = 0.f;
	bool bShowGhost = true;
	float LapStartDistanceAlongSpline = 0.f;
	/** end Lap data */
	
	void StartRaceTimer();
	void StopRaceTimer();
	void PopulateLapInfoData();
	void ShowGhost();
	void TickDownTimeRemaining();
	bool IsRotationAllignedWithTrack();
};
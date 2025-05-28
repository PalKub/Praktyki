// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PraktykiPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLapTimeChangeSignature, float, LapTimeElapsed);
/**
 * 
 */
UCLASS()
class PRAKTYKI_API APraktykiPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnLapTimeChangeSignature OnLapTimeChangeDelegate;

	void StartFinishTriggered();
	
private:
	UPROPERTY(EditDefaultsOnly)
	float RaceTimerTickFrequency = 0.1f;
	
	FTimerHandle RaceTimer;
	float GameTimeAtLapStart = 0.f;
	float LapTimeElapsed = 0.f;
	bool bRaceTimeMeasuringActive = false;
	
	void StartRaceTimer();
};
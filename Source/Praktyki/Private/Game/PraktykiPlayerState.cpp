// Copyright 2025 Teyon. All Rights Reserved.


#include "Game/PraktykiPlayerState.h"

void APraktykiPlayerState::StartFinishTriggered()
{
	if (bRaceTimeMeasuringActive)
	{
		GetWorldTimerManager().ClearTimer(RaceTimer);
		LapTimeElapsed = GetWorld()->GetTimeSeconds() - GameTimeAtLapStart;
		OnLapTimeChangeDelegate.Broadcast(LapTimeElapsed);
	}
	else
	{
		bRaceTimeMeasuringActive = true;
		GameTimeAtLapStart = GetWorld()->GetTimeSeconds();
		GetWorldTimerManager().SetTimer(RaceTimer, this, &APraktykiPlayerState::StartRaceTimer, RaceTimerTickFrequency, true);
	}
}

void APraktykiPlayerState::StartRaceTimer()
{
	LapTimeElapsed = GetWorld()->GetTimeSeconds() - GameTimeAtLapStart;
	OnLapTimeChangeDelegate.Broadcast(LapTimeElapsed);
}
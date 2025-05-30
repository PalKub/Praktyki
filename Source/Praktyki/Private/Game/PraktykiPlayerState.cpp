// Copyright 2025 Teyon. All Rights Reserved.


#include "Game/PraktykiPlayerState.h"

#include "Components/SplineComponent.h"
#include "Curves/CurveVector.h"
#include "Game/PraktykiGameInstance.h"

void APraktykiPlayerState::StartFinishTriggered()
{
	if (!GameInstance) GameInstance = Cast<UPraktykiGameInstance>(GetGameInstance());

	if (GameInstance)
	{
		if (bRaceTimeMeasuringActive && bSectorThreeTriggered && !bSectorTwoTriggered && !bStartFinishTriggered)
		{
			bRaceTimeMeasuringActive = false;
			bSectorThreeTriggered = false;
			bStartFinishTriggered = true;
			StopRaceTimer();
		}

		if (!bRaceTimeMeasuringActive)
		{
			bRaceTimeMeasuringActive = true;
			bStartFinishTriggered = true;
			bSectorTwoTriggered = false;
			bSectorThreeTriggered = false;
			GameTimeAtLapStart = GetWorld()->GetTimeSeconds();

			if (!CurrentLapTimeAtDistance || BestLapTimeAtDistanceCurve == CurrentLapTimeAtDistance) CurrentLapTimeAtDistance = NewObject<UCurveFloat>();
			else CurrentLapTimeAtDistance->ResetCurve();

			if (!CurrentLapLocationAtLapTime || BestLapLocationAtLapTime == CurrentLapLocationAtLapTime) CurrentLapLocationAtLapTime = NewObject<UCurveVector>();
			else CurrentLapLocationAtLapTime->ResetCurve();
			
			if (!CurrentLapRotationAtLapTime || BestLapRotationAtLapTime == CurrentLapRotationAtLapTime) CurrentLapRotationAtLapTime = NewObject<UCurveVector>();
			else (CurrentLapRotationAtLapTime->ResetCurve());
			
			GetWorldTimerManager().SetTimer(RaceTimer, this, &APraktykiPlayerState::StartRaceTimer, RaceTimerTickFrequency, true);
		}
	}
}

void APraktykiPlayerState::SectorTwoTriggered()
{
	if (bStartFinishTriggered && !bSectorTwoTriggered && !bSectorThreeTriggered && bRaceTimeMeasuringActive)
	{
		bStartFinishTriggered = false;
		bSectorTwoTriggered = true;
		CurrentSectorOneTime = LapTimeElapsed;
		if (BestSectorOneTime == 0.f || CurrentSectorOneTime < BestSectorOneTime)
		{
			BestSectorOneTime = CurrentSectorOneTime;
			OnSectorCompletedDelegate.Broadcast(ESectorNumber::ESN_One, CurrentSectorOneTime, true);
		}
		else OnSectorCompletedDelegate.Broadcast(ESectorNumber::ESN_One, CurrentSectorOneTime, false);
	}
}

void APraktykiPlayerState::SectorThreeTriggered()
{
	if (bSectorTwoTriggered && !bStartFinishTriggered && !bSectorThreeTriggered && bRaceTimeMeasuringActive)
	{
		bSectorTwoTriggered = false;
		bSectorThreeTriggered = true;
		CurrentSectorTwoTime = LapTimeElapsed - CurrentSectorOneTime;
		if (BestSectorTwoTime == 0.f || CurrentSectorTwoTime < BestSectorTwoTime)
		{
			BestSectorTwoTime = CurrentSectorTwoTime;
			OnSectorCompletedDelegate.Broadcast(ESectorNumber::ESN_Two, CurrentSectorTwoTime, true);
		}
		else OnSectorCompletedDelegate.Broadcast(ESectorNumber::ESN_Two, CurrentSectorTwoTime, false);
	}
}

void APraktykiPlayerState::StartRaceTimer()
{
	PopulateLapInfoData();
}

void APraktykiPlayerState::StopRaceTimer()
{
	GetWorldTimerManager().ClearTimer(RaceTimer);
	PopulateLapInfoData();
	CurrentSectorThreeTime = LapTimeElapsed - CurrentSectorOneTime - CurrentSectorTwoTime;

	FLapInfo CurrentLapInfo;
	CurrentLapInfo.LapTime = LapTimeElapsed;
	CurrentLapInfo.SectorOneTime = CurrentSectorOneTime;
	CurrentLapInfo.SectorTwoTime = CurrentSectorTwoTime;
	CurrentLapInfo.SectorThreeTime = CurrentSectorThreeTime;
	LapsInfoArray.Add(CurrentLapInfo);

	bool bIsBestLap = false;
	if (BestLapTime == 0.f || LapTimeElapsed < BestLapTime)
	{
		bIsBestLap = true;
		BestLapTime = LapTimeElapsed;
		BestLapTimeAtDistanceCurve = CurrentLapTimeAtDistance;
		BestLapLocationAtLapTime = CurrentLapLocationAtLapTime;
		BestLapRotationAtLapTime = CurrentLapRotationAtLapTime;
	}
	
	if (BestSectorThreeTime == 0.f || CurrentSectorThreeTime < BestSectorThreeTime)
	{
		BestSectorThreeTime = CurrentSectorThreeTime;
		OnSectorCompletedDelegate.Broadcast(ESectorNumber::ESN_Three, CurrentSectorThreeTime, true);
	}
	else OnSectorCompletedDelegate.Broadcast(ESectorNumber::ESN_Three, CurrentSectorThreeTime, false);

	OnLapTimeCompletedDelegate.Broadcast(CurrentLapInfo, bIsBestLap);
}

void APraktykiPlayerState::PopulateLapInfoData()
{
	LapTimeElapsed = GetWorld()->GetTimeSeconds() - GameTimeAtLapStart;
	OnLapTimeChangeDelegate.Broadcast(LapTimeElapsed);
	const FVector& ClosestLocationOnTheTrackSpline = GameInstance->GetSpectatorCameraSpline()->FindLocationClosestToWorldLocation(GetPawn()->GetActorLocation(), ESplineCoordinateSpace::World);
	const float DistanceAlongTrackSpline = GameInstance->GetSpectatorCameraSpline()->GetDistanceAlongSplineAtLocation(ClosestLocationOnTheTrackSpline, ESplineCoordinateSpace::World);

	CurrentLapTimeAtDistance->FloatCurve.AddKey(LapTimeElapsed, DistanceAlongTrackSpline);

	CurrentLapLocationAtLapTime->FloatCurves[0].AddKey(LapTimeElapsed, GetPawn()->GetActorLocation().X);
	CurrentLapLocationAtLapTime->FloatCurves[1].AddKey(LapTimeElapsed, GetPawn()->GetActorLocation().Y);
	CurrentLapLocationAtLapTime->FloatCurves[2].AddKey(LapTimeElapsed, GetPawn()->GetActorLocation().Z);

	CurrentLapRotationAtLapTime->FloatCurves[0].AddKey(LapTimeElapsed, GetPawn()->GetActorRotation().Roll);
	CurrentLapRotationAtLapTime->FloatCurves[1].AddKey(LapTimeElapsed, GetPawn()->GetActorRotation().Pitch);
	CurrentLapRotationAtLapTime->FloatCurves[0].AddKey(LapTimeElapsed, GetPawn()->GetActorRotation().Yaw);
}
// Copyright 2025 Teyon. All Rights Reserved.


#include "Game/PraktykiPlayerState.h"

#include "Actors/GhostActor.h"
#include "Components/SplineComponent.h"
#include "Game/PraktykiGameInstance.h"
#include "PlayerController/PraktykiPlayerVehicleController.h"

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
			if (GhostPawn) GhostPawn->Destroy();
			StopRaceTimer();
		}

		if (!bRaceTimeMeasuringActive)
		{
			bRaceTimeMeasuringActive = true;
			bStartFinishTriggered = true;
			bSectorTwoTriggered = false;
			bSectorThreeTriggered = false;
			GameTimeAtLapStart = GetWorld()->GetTimeSeconds();

			if (!CurrentDistanceAtLapTime || BestDistanceAtLapTime == CurrentDistanceAtLapTime) CurrentDistanceAtLapTime = NewObject<UCurveFloat>();
			else CurrentDistanceAtLapTime->ResetCurve();

			CurrentLapTransformAtLapTime.CopyCurve(EmptyCurve);

			PreviousDistance = 0.f;
			GetWorldTimerManager().SetTimer(RaceTimer, this, &APraktykiPlayerState::StartRaceTimer, RaceTimerTickFrequency, true);

			if (BestLapTime != 0 && bShowGhost)
			{
				ShowGhost();
			}
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
	CurrentDistanceAtLapTime->FloatCurve.AddKey(GameInstance->GetSpectatorCameraSpline()->GetSplineLength(), LapTimeElapsed);

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
		BestDistanceAtLapTime = CurrentDistanceAtLapTime;
		BestLapTransformAtLapTime.CopyCurve(CurrentLapTransformAtLapTime);
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
	const FVector& ClosestLocationOnTheTrackSpline = GameInstance->GetSpectatorCameraSpline()->FindLocationClosestToWorldLocation(GetPawn()->GetActorLocation(), ESplineCoordinateSpace::World);
	const float DistanceAlongTrackSpline = GameInstance->GetSpectatorCameraSpline()->GetDistanceAlongSplineAtLocation(ClosestLocationOnTheTrackSpline, ESplineCoordinateSpace::World);
	
	if (PreviousDistance < DistanceAlongTrackSpline)
	{
		CurrentDistanceAtLapTime->FloatCurve.AddKey(DistanceAlongTrackSpline, LapTimeElapsed);
		PreviousDistance = DistanceAlongTrackSpline;
	}
	
	CurrentLapTransformAtLapTime.UpdateOrAddKey(GetPawn()->GetActorTransform(), LapTimeElapsed);

	if (BestLapTime > 0.f)
	{
		const float Delta = LapTimeElapsed - BestDistanceAtLapTime->GetFloatValue(DistanceAlongTrackSpline);
		OnLapTimeChangeDelegate.Broadcast(LapTimeElapsed, Delta);
	}
	else OnLapTimeChangeDelegate.Broadcast(LapTimeElapsed, 0.f);

	if (GhostPawn) UpdateGhostLocation();
}

void APraktykiPlayerState::ShowGhost()
{

	FTransform StartTransform = BestLapTransformAtLapTime.Evaluate(LapTimeElapsed, 0.f);
	
	if (const APraktykiPlayerVehicleController* PlayerController = Cast<APraktykiPlayerVehicleController>(GetPlayerController()))
	{
		GhostPawn = PlayerController->SpawnGhost(StartTransform.GetLocation(), StartTransform.Rotator());
	}
}

void APraktykiPlayerState::UpdateGhostLocation()
{
	GhostPawn->SetActorTransform(BestLapTransformAtLapTime.Evaluate(LapTimeElapsed, 1.f));
	if (LapTimeElapsed >= BestLapTime)
	{
		GhostPawn->Destroy();
	}
}
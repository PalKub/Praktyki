// Copyright 2025 Teyon. All Rights Reserved.


#include "Game/PraktykiPlayerState.h"

#include "Actors/GhostActor.h"
#include "Components/SplineComponent.h"
#include "Game/PraktykiGameInstance.h"
#include "PlayerController/PraktykiPlayerVehicleController.h"

FLapInfo APraktykiPlayerState::GetBestLapInfo()
{
	if (BestLapTime == 0.f) return FLapInfo();
	FLapInfo Info;
	Info.LapTime = BestLapTime;
	Info.SectorOneTime = BestLapSectorOne;
	Info.SectorTwoTime = BestLapSectorTwo;
	Info.SectorThreeTime = BestLapSectorThree;
	return Info;
}

FLapInfo APraktykiPlayerState::GetOptimalLapInfo()
{
	if (BestLapTime == 0.f) return FLapInfo();
	FLapInfo Info;
	Info.LapTime = BestSectorOneTime + BestSectorTwoTime + BestSectorThreeTime;
	Info.SectorOneTime = BestSectorOneTime;
	Info.SectorTwoTime = BestSectorTwoTime;
	Info.SectorThreeTime = BestSectorThreeTime;
	return Info;
}

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
			if (GhostPawn && !GhostPawn->IsPendingKillPending()) GhostPawn->Destroy();
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
			if (!CurrentLapTimeAtDistance || BestLapTimeAtDistance == CurrentLapTimeAtDistance) CurrentLapTimeAtDistance = NewObject<UCurveFloat>();
			else CurrentDistanceAtLapTime->ResetCurve();
			if (!bIsValidLap) bIsValidLap = true;
			CurrentLapTransformAtLapTime = FTransformCurve();
			PreviousDistance = 0.f;

			const FVector& ClosestLocationOnTheTrackSpline = GameInstance->GetSpectatorCameraSpline()->FindLocationClosestToWorldLocation(GetPawn()->GetActorLocation(), ESplineCoordinateSpace::World);
			const float DistanceAlongTrackSpline = GameInstance->GetSpectatorCameraSpline()->GetDistanceAlongSplineAtLocation(ClosestLocationOnTheTrackSpline, ESplineCoordinateSpace::World);
			LapStartDistanceAlongSpline = DistanceAlongTrackSpline;
			
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
			OnSectorCompletedDelegate.Broadcast(ESectorNumber::ESN_One, CurrentSectorOneTime, true, bIsValidLap);
		}
		else OnSectorCompletedDelegate.Broadcast(ESectorNumber::ESN_One, CurrentSectorOneTime, false, bIsValidLap);
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
			OnSectorCompletedDelegate.Broadcast(ESectorNumber::ESN_Two, CurrentSectorTwoTime, true, bIsValidLap);
		}
		else OnSectorCompletedDelegate.Broadcast(ESectorNumber::ESN_Two, CurrentSectorTwoTime, false, bIsValidLap);
	}
}

void APraktykiPlayerState::InitializeTimeLimit()
{
	TimeRemaining = TimeLimit * 60;
	GetWorldTimerManager().SetTimer(TimeRemainingTimer, this, &APraktykiPlayerState::TickDownTimeRemaining, 1.f, true, 1.f);
}

void APraktykiPlayerState::ResetData()
{
	BestLapTime = 0.f;
	BestSectorOneTime = 0.f;
	BestSectorTwoTime = 0.f;
	BestSectorThreeTime = 0.f;
	BestLapSectorOne = 0.f;
	BestLapSectorTwo = 0.f;
	BestLapSectorThree = 0.f;
	PreviousDistance = 0.f;
	bRaceTimeMeasuringActive = false;
	bStartFinishTriggered = false;
	bSectorTwoTriggered = false;
	bSectorThreeTriggered = false;
	bIsValidLap = true;
	TimeLimit = 0.f;
	TimeRemaining = 0.f;
	LapStartDistanceAlongSpline = 0.f;
	bShowGhost = true;
	LapsInfoArray.Empty();
	if (CurrentDistanceAtLapTime) CurrentDistanceAtLapTime->ResetCurve();
	if (BestDistanceAtLapTime) BestDistanceAtLapTime->ResetCurve();
	if (CurrentLapTimeAtDistance) CurrentLapTimeAtDistance->ResetCurve();
	if (BestLapTimeAtDistance) BestLapTimeAtDistance->ResetCurve();
	CurrentLapTransformAtLapTime = FTransformCurve();
	BestLapTransformAtLapTime = FTransformCurve();
	CurrentLapTransformAtLapTime.RotationCurve.FloatCurves->Reset();
	CurrentLapTransformAtLapTime.TranslationCurve.FloatCurves->Reset();
	CurrentLapTransformAtLapTime.ScaleCurve.FloatCurves->Reset();
	BestLapTransformAtLapTime.RotationCurve.FloatCurves->Reset();
	BestLapTransformAtLapTime.TranslationCurve.FloatCurves->Reset();
	BestLapTransformAtLapTime.ScaleCurve.FloatCurves->Reset();
	DamageMode = EDamageMode::EDM_NoDamage;
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
	if ((BestLapTime == 0.f || LapTimeElapsed < BestLapTime) && bIsValidLap)
	{
		bIsBestLap = true;
		BestLapTime = LapTimeElapsed;
		BestLapSectorOne = CurrentSectorOneTime;
		BestLapSectorTwo = CurrentSectorTwoTime;
		BestLapSectorThree = CurrentSectorThreeTime;
		if (BestDistanceAtLapTime) BestDistanceAtLapTime->FloatCurve.Reset();
		BestDistanceAtLapTime = CurrentDistanceAtLapTime;
		BestLapTimeAtDistance = CurrentLapTimeAtDistance;
		BestLapTransformAtLapTime = FTransformCurve();
		BestLapTransformAtLapTime = CurrentLapTransformAtLapTime;
	}
	
	if (BestSectorThreeTime == 0.f || CurrentSectorThreeTime < BestSectorThreeTime)
	{
		BestSectorThreeTime = CurrentSectorThreeTime;
		OnSectorCompletedDelegate.Broadcast(ESectorNumber::ESN_Three, CurrentSectorThreeTime, true, bIsValidLap);
	}
	else OnSectorCompletedDelegate.Broadcast(ESectorNumber::ESN_Three, CurrentSectorThreeTime, false, bIsValidLap);

	OnLapTimeCompletedDelegate.Broadcast(CurrentLapInfo, bIsBestLap, bIsValidLap);
}

void APraktykiPlayerState::PopulateLapInfoData()
{
	LapTimeElapsed = GetWorld()->GetTimeSeconds() - GameTimeAtLapStart;
	const FVector& ClosestLocationOnTheTrackSpline = GameInstance->GetSpectatorCameraSpline()->FindLocationClosestToWorldLocation(GetPawn()->GetActorLocation(), ESplineCoordinateSpace::World);
	const float DistanceAlongTrackSpline = GameInstance->GetSpectatorCameraSpline()->GetDistanceAlongSplineAtLocation(ClosestLocationOnTheTrackSpline, ESplineCoordinateSpace::World);

	if (PreviousDistance < DistanceAlongTrackSpline || (PreviousDistance > GameInstance->GetSpectatorCameraSpline()->GetSplineLength() * 0.95f && DistanceAlongTrackSpline < GameInstance->GetSpectatorCameraSpline()->GetSplineLength() * 0.05f))
	{
		if (DistanceAlongTrackSpline <= GameInstance->GetSpectatorCameraSpline()->GetSplineLength() * 0.05f && DistanceAlongTrackSpline >= LapStartDistanceAlongSpline && bSectorTwoTriggered) return;
		CurrentDistanceAtLapTime->FloatCurve.AddKey(DistanceAlongTrackSpline, LapTimeElapsed);
		PreviousDistance = DistanceAlongTrackSpline;
		CurrentLapTimeAtDistance->FloatCurve.AddKey(LapTimeElapsed, DistanceAlongTrackSpline);
	}

	CurrentLapTransformAtLapTime.UpdateOrAddKey(GetPawn()->GetActorTransform(), LapTimeElapsed);

	if (BestLapTime > 0.f)
	{
		const float Delta = LapTimeElapsed - BestDistanceAtLapTime->GetFloatValue(DistanceAlongTrackSpline);
		OnLapTimeChangeDelegate.Broadcast(LapTimeElapsed, Delta, bIsValidLap);
	}
	else OnLapTimeChangeDelegate.Broadcast(LapTimeElapsed, 0.f, bIsValidLap);
}

void APraktykiPlayerState::ShowGhost()
{

	FTransform StartTransform = BestLapTransformAtLapTime.Evaluate(LapTimeElapsed, 0.f);
	
	if (const APraktykiPlayerVehicleController* PlayerController = Cast<APraktykiPlayerVehicleController>(GetPlayerController()))
	{
		GhostPawn = PlayerController->SpawnGhost(StartTransform.GetLocation(), StartTransform.Rotator());
		GhostPawn->SetLapData(BestLapTransformAtLapTime, BestDistanceAtLapTime, BestLapTimeAtDistance);
		GhostPawn->StartMoving();
	}
}

void APraktykiPlayerState::TickDownTimeRemaining()
{
	TimeRemaining--;
	OnTimeRemainingChangedDelegate.Broadcast(TimeRemaining);
	if (TimeRemaining <= 0)
	{
		GetWorldTimerManager().ClearTimer(TimeRemainingTimer);
		if (APraktykiPlayerVehicleController* PlayerController = Cast<APraktykiPlayerVehicleController>(GetPlayerController()))
		{
			PlayerController->RaceTimeEnded();
		}
	}
}
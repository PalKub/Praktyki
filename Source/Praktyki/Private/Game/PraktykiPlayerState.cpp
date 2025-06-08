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
			if (IsValid(GhostPawn)) GhostPawn->Destroy();
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
			else CurrentDistanceAtLapTime->FloatCurve = FRichCurve();
			if (!CurrentLapTimeAtDistance || BestLapTimeAtDistance == CurrentLapTimeAtDistance) CurrentLapTimeAtDistance = NewObject<UCurveFloat>();
			else CurrentLapTimeAtDistance->FloatCurve = FRichCurve();
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
		if ((BestSectorOneTime == 0.f || CurrentSectorOneTime < BestSectorOneTime) && bIsValidLap)
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
		if ((BestSectorTwoTime == 0.f || CurrentSectorTwoTime < BestSectorTwoTime) && bIsValidLap)
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
	if (CurrentDistanceAtLapTime) CurrentDistanceAtLapTime->FloatCurve = FRichCurve();
	if (BestDistanceAtLapTime) BestDistanceAtLapTime->FloatCurve = FRichCurve();
	if (CurrentLapTimeAtDistance) CurrentLapTimeAtDistance->FloatCurve = FRichCurve();
	if (BestLapTimeAtDistance) BestLapTimeAtDistance->FloatCurve = FRichCurve();
	CurrentLapTransformAtLapTime = FTransformCurve();
	BestLapTransformAtLapTime = FTransformCurve();
	DamageMode = EDamageMode::EDM_NoDamage;
}

void APraktykiPlayerState::ClearRaceTimer()
{
	if (GetWorldTimerManager().IsTimerActive(RaceTimer)) GetWorldTimerManager().ClearTimer(RaceTimer);
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
		if (BestDistanceAtLapTime) BestDistanceAtLapTime->FloatCurve = FRichCurve();
		BestDistanceAtLapTime = CurrentDistanceAtLapTime;
		BestLapTimeAtDistance = CurrentLapTimeAtDistance;
		BestLapTransformAtLapTime = FTransformCurve();
		BestLapTransformAtLapTime = CurrentLapTransformAtLapTime;
	}
	
	if ((BestSectorThreeTime == 0.f || CurrentSectorThreeTime < BestSectorThreeTime) && bIsValidLap)
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

	//Assuring curve points are not added when car goes backwards on the track
	if (PreviousDistance < DistanceAlongTrackSpline || (PreviousDistance > GameInstance->GetSpectatorCameraSpline()->GetSplineLength() * 0.95f && DistanceAlongTrackSpline < GameInstance->GetSpectatorCameraSpline()->GetSplineLength() * 0.05f))
	{
		//Assuring curve points are added correctly at the end/beginning spline overlap point
		if (DistanceAlongTrackSpline <= GameInstance->GetSpectatorCameraSpline()->GetSplineLength() * 0.05f && DistanceAlongTrackSpline >= LapStartDistanceAlongSpline && bSectorTwoTriggered) return;
		CurrentDistanceAtLapTime->FloatCurve.AddKey(DistanceAlongTrackSpline, LapTimeElapsed);
		PreviousDistance = DistanceAlongTrackSpline;
		CurrentLapTimeAtDistance->FloatCurve.AddKey(LapTimeElapsed, DistanceAlongTrackSpline);
	}

	CurrentLapTransformAtLapTime.UpdateOrAddKey(GetPawn()->GetActorTransform(), LapTimeElapsed);
	const bool bCarRotationCorrect = IsRotationAllignedWithTrack();

	if (BestLapTime > 0.f)
	{
		const float Delta = LapTimeElapsed - BestDistanceAtLapTime->GetFloatValue(DistanceAlongTrackSpline);
		OnLapTimeChangeDelegate.Broadcast(LapTimeElapsed, Delta, bIsValidLap, bCarRotationCorrect);
	}
	else OnLapTimeChangeDelegate.Broadcast(LapTimeElapsed, 0.f, bIsValidLap, bCarRotationCorrect);
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

bool APraktykiPlayerState::IsRotationAllignedWithTrack()
{
	const FRotator ClosestRotationOnTheTrackSpline = GameInstance->GetSpectatorCameraSpline()->FindRotationClosestToWorldLocation(GetPawn()->GetActorLocation(), ESplineCoordinateSpace::World);
	bool bIsValidDirection;
	const float RotationDifference = FMath::Abs(GetPawn()->GetActorRotation().Yaw - ClosestRotationOnTheTrackSpline.Yaw);
	if (RotationDifference < 90 || RotationDifference > 270) bIsValidDirection = true;
	else bIsValidDirection = false;
	return bIsValidDirection;
}

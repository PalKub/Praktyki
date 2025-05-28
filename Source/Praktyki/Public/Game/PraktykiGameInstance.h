// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PraktykiGameInstance.generated.h"

class ATrackTimerTriggersActor;
class USplineComponent;
/**
 * 
 */
UCLASS()
class PRAKTYKI_API UPraktykiGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	ATrackTimerTriggersActor* GetTrackTimerTriggersActor() { return TrackTimerTriggersActor; }
	
	void SetSpectatorCameraSpline(USplineComponent* Spline) { SpectatorCameraSpline = Spline; }
	TObjectPtr<USplineComponent> GetSpectatorCameraSpline() { return SpectatorCameraSpline; }
	void SetTrackTimerTriggersActor(ATrackTimerTriggersActor* TrackTimersActor) { TrackTimerTriggersActor = TrackTimersActor; }

private:
	TObjectPtr<USplineComponent> SpectatorCameraSpline;
	TObjectPtr<ATrackTimerTriggersActor> TrackTimerTriggersActor;
};
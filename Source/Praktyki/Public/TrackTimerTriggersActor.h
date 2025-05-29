// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrackTimerTriggersActor.generated.h"

class UBoxComponent;

UCLASS()
class PRAKTYKI_API ATrackTimerTriggersActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ATrackTimerTriggersActor();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBoxComponent> StartFinishTriggerBox;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBoxComponent> SectorTwoTriggerBox;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBoxComponent> SectorThreeTriggerBox;

	UPROPERTY(EditDefaultsOnly)
	float RaceTimerTickFrequency = 0.1f;
	
	FTimerHandle RaceTimer;
	float GameTimeAtLapStart = 0.f;
	float LapTimeElapsed = 0.f;
	bool bRaceTimeMeasuringActive = false;

	UFUNCTION()
	void OnStartFinishBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnSectorTwoBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnSectorThreeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
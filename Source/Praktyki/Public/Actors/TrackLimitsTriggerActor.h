// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrackLimitsTriggerActor.generated.h"

UCLASS()
class PRAKTYKI_API ATrackLimitsTriggerActor : public AActor
{
	GENERATED_BODY()

private:
	UFUNCTION(BlueprintCallable)
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
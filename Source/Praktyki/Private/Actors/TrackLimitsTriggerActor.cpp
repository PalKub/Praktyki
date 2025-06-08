// Copyright 2025 Teyon. All Rights Reserved.


#include "Actors/TrackLimitsTriggerActor.h"

#include "Player/PraktykiPlayerState.h"

void ATrackLimitsTriggerActor::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		if (APraktykiPlayerState* PlayerState = GetWorld()->GetFirstPlayerController()->GetPlayerState<APraktykiPlayerState>())
		{
			PlayerState->InvalidateLap();
		}
	}
}
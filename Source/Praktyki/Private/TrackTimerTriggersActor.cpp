// Copyright 2025 Teyon. All Rights Reserved.


#include "TrackTimerTriggersActor.h"

#include "Components/BoxComponent.h"
#include "Game/PraktykiGameInstance.h"
#include "Game/PraktykiPlayerState.h"

ATrackTimerTriggersActor::ATrackTimerTriggersActor()
{
	PrimaryActorTick.bCanEverTick = false;

	StartFinishTriggerBox = CreateDefaultSubobject<UBoxComponent>("StartFinishTriggerBox");
	StartFinishTriggerBox->SetupAttachment(GetRootComponent());
	StartFinishTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ATrackTimerTriggersActor::OnStartFinishBeginOverlap);
	StartFinishTriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	StartFinishTriggerBox->SetCollisionResponseToAllChannels(ECR_Overlap);

	SectorTwoTriggerBox = CreateDefaultSubobject<UBoxComponent>("SectorTwoTriggerBox");
	SectorTwoTriggerBox->SetupAttachment(GetRootComponent());

	SectorThreeTriggerBox = CreateDefaultSubobject<UBoxComponent>("SectorThreeTriggerBox");
	SectorThreeTriggerBox->SetupAttachment(GetRootComponent());
}

void ATrackTimerTriggersActor::BeginPlay()
{
	Super::BeginPlay();

	SetActorTickEnabled(false);

	if (UPraktykiGameInstance* GameInstance = Cast<UPraktykiGameInstance>(GetGameInstance()))
	{
		GameInstance->SetTrackTimerTriggersActor(this);
	}
}

void ATrackTimerTriggersActor::OnStartFinishBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		if (const APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
		{
			if (APraktykiPlayerState* PlayerState = PlayerController->GetPlayerState<APraktykiPlayerState>())
			{
				PlayerState->StartFinishTriggered();
			}
		}
	}
}
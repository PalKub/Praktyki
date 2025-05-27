// Copyright 2025 Teyon. All Rights Reserved.


#include "PraktykiSpectatorSpline.h"

#include "Components/SplineComponent.h"
#include "Game/PraktykiGameInstance.h"

APraktykiSpectatorSpline::APraktykiSpectatorSpline()
{
	PrimaryActorTick.bCanEverTick = false;

	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
	SetRootComponent(Spline);
}

void APraktykiSpectatorSpline::BeginPlay()
{
	Super::BeginPlay();

	if (UPraktykiGameInstance* GameInstance = Cast<UPraktykiGameInstance>(GetGameInstance()))
	{
		GameInstance->SetSpectatorCameraSpline(Spline);
	}
}
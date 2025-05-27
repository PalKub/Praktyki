// Copyright 2025 Teyon. All Rights Reserved.


#include "PraktykiSpectatorCamera.h"

#include "Camera/CameraComponent.h"
#include "Components/SplineComponent.h"
#include "Game/PraktykiGameInstance.h"
#include "GameFramework/SpringArmComponent.h"

APraktykiSpectatorCamera::APraktykiSpectatorCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SetRootComponent(SpringArm);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
}

void APraktykiSpectatorCamera::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (Spline)
	{
		FVector NewLocation = Spline->GetLocationAtDistanceAlongSpline(CurrentDistanceAlongSpline, ESplineCoordinateSpace::World);
		FRotator NewRotation = Spline->GetRotationAtDistanceAlongSpline(CurrentDistanceAlongSpline, ESplineCoordinateSpace::World);
		SpringArm->SetWorldLocation(NewLocation);
		SpringArm->SetWorldRotation(NewRotation);

		CurrentDistanceAlongSpline += CameraSpeed * DeltaSeconds;
		if (CurrentDistanceAlongSpline >= Spline->GetSplineLength()) CurrentDistanceAlongSpline = 0.f;
	}
}

void APraktykiSpectatorCamera::BeginPlay()
{
	Super::BeginPlay();

	if (TObjectPtr<UPraktykiGameInstance> GameInstance = Cast<UPraktykiGameInstance>(GetGameInstance()))
	{
		Spline = GameInstance->GetSpectatorCameraSpline();
	}
}
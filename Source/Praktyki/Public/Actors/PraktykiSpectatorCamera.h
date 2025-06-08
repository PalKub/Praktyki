// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PraktykiSpectatorCamera.generated.h"

class ASplineMeshActor;
class USplineComponent;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class PRAKTYKI_API APraktykiSpectatorCamera : public APawn
{
	GENERATED_BODY()

public:
	APraktykiSpectatorCamera();

protected:
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(EditDefaultsOnly)
	float CameraSpeed = 100.f;

	float CurrentDistanceAlongSpline = 0.f;
	TObjectPtr<USplineComponent> Spline;
};
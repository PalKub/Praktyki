// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PraktykiPlayerVehicleController.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class PRAKTYKI_API APraktykiPlayerVehicleController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> PlayerContext;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> RotateCameraAction;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> AccelerateAction;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> BrakeAction;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> TurnAction;

	void Accelerate(const FInputActionValue& InputActionValue);
	void Brake(const FInputActionValue& InputActionValue);
	void Turn(const FInputActionValue& InputActionValue);
	void RotateCamera(const FInputActionValue& InputActionValue);
};
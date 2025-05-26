// Copyright 2025 Teyon. All Rights Reserved.


#include "PlayerController/PraktykiPlayerVehicleController.h"

#include "ChaosVehicleMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerVehicle/PlayerVehiclePawn.h"

void APraktykiPlayerVehicleController::BeginPlay()
{
	Super::BeginPlay();
	check(PlayerContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(PlayerContext, 0);
}

void APraktykiPlayerVehicleController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(AccelerateAction, ETriggerEvent::Triggered, this, &APraktykiPlayerVehicleController::Accelerate);
	EnhancedInputComponent->BindAction(AccelerateAction, ETriggerEvent::Completed, this, &APraktykiPlayerVehicleController::Accelerate);
	EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Triggered, this, &APraktykiPlayerVehicleController::Brake);
	EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Completed, this, &APraktykiPlayerVehicleController::Brake);
	EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &APraktykiPlayerVehicleController::Turn);
	EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Completed, this, &APraktykiPlayerVehicleController::Turn);
	EnhancedInputComponent->BindAction(RotateCameraAction, ETriggerEvent::Triggered, this, &APraktykiPlayerVehicleController::RotateCamera);
}

void APraktykiPlayerVehicleController::Accelerate(const FInputActionValue& InputActionValue)
{
	if (const APlayerVehiclePawn* PlayerVehicle = Cast<APlayerVehiclePawn>(GetPawn()))
	{
		PlayerVehicle->GetVehicleMovement()->SetThrottleInput(InputActionValue.Get<float>());
	}
}

void APraktykiPlayerVehicleController::Brake(const FInputActionValue& InputActionValue)
{
	if (const APlayerVehiclePawn* PlayerVehicle = Cast<APlayerVehiclePawn>(GetPawn()))
	{
		PlayerVehicle->GetVehicleMovement()->SetBrakeInput(InputActionValue.Get<float>());
	}
}

void APraktykiPlayerVehicleController::Turn(const FInputActionValue& InputActionValue)
{
	if (const APlayerVehiclePawn* PlayerVehicle = Cast<APlayerVehiclePawn>(GetPawn()))
	{
		PlayerVehicle->GetVehicleMovement()->SetSteeringInput(InputActionValue.Get<float>());
	}
}

void APraktykiPlayerVehicleController::RotateCamera(const FInputActionValue& InputActionValue)
{
	if (APlayerVehiclePawn* PlayerVehicle = Cast<APlayerVehiclePawn>(GetPawn()))
	{
		PlayerVehicle->SetCameraRotation(InputActionValue.Get<FVector2D>());
	}
}
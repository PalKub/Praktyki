// Copyright 2025 Teyon. All Rights Reserved.


#include "PlayerController/PraktykiPlayerVehicleController.h"

#include "ChaosVehicleMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Actors/GhostActor.h"
#include "Game/PraktykiMainMenuHUD.h"
#include "Game/PraktykiPlayerState.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerVehicle/PlayerVehiclePawn.h"

TObjectPtr<AGhostActor> APraktykiPlayerVehicleController::SpawnGhost(const FVector& Location,
	const FRotator& Rotation) const
{
	return GetWorld()->SpawnActor<AGhostActor>(GhostActorClass, Location, Rotation);
}

void APraktykiPlayerVehicleController::StartPracticeMode()
{
	if (AActor* PlayerStart = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass()))
	{
		if (APawn* CurrentPawn = GetPawn())
		{
			UnPossess();
			CurrentPawn->Destroy();
		}
		APlayerVehiclePawn* NewPawn = GetWorld()->SpawnActor<APlayerVehiclePawn>(PlayerVehicleClass, PlayerStart->GetActorTransform());
		Possess(NewPawn);
		if (APraktykiMainMenuHUD* HUD = Cast<APraktykiMainMenuHUD>(GetHUD()))
		{
			HUD->OpenRacingHUDWidget();
		}
	}
}

void APraktykiPlayerVehicleController::StartRaceMode(int32 TimeLimit, bool bShowGhost, ELiveryColor LiveryColor)
{
	if (AActor* PlayerStart = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass()))
	{
		if (APawn* CurrentPawn = GetPawn())
		{
			UnPossess();
			CurrentPawn->Destroy();
		}
		APlayerVehiclePawn* NewPawn = GetWorld()->SpawnActorDeferred<APlayerVehiclePawn>(PlayerVehicleClass, PlayerStart->GetActorTransform());
		NewPawn->SetLivery(LiveryColor);
		NewPawn->FinishSpawning(PlayerStart->GetActorTransform());

		if (APraktykiPlayerState* PraktykiPlayerState = Cast<APraktykiPlayerState>(PlayerState))
		{
			PraktykiPlayerState->SetTimeLimit(TimeLimit);
			PraktykiPlayerState->SetShouldShowGhost(bShowGhost);
		}

		Possess(NewPawn);
		if (APraktykiMainMenuHUD* HUD = Cast<APraktykiMainMenuHUD>(GetHUD()))
		{
			HUD->OpenRacingHUDWidget();
		}
	}
}

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
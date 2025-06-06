// Copyright 2025 Teyon. All Rights Reserved.


#include "PlayerController/PraktykiPlayerVehicleController.h"

#include "ChaosVehicleMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PraktykiSpectatorCamera.h"
#include "Actors/GhostActor.h"
#include "Game/PraktykiMainMenuHUD.h"
#include "Game/PraktykiPlayerState.h"
#include "GameFramework/GameModeBase.h"
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
	StartRaceMode(0, false, ELiveryColor::ELC_Default);
}

void APraktykiPlayerVehicleController::QuitToMainMenu()
{
	if (AActor* PlayerStart = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass()))
	{
		if (APawn* CurrentPawn = GetPawn())
		{
			UnPossess();
			CurrentPawn->Destroy();
		}
		APraktykiSpectatorCamera* NewPawn = GetWorld()->SpawnActor<APraktykiSpectatorCamera>(GetWorld()->GetAuthGameMode()->GetDefaultPawnClassForController(this), PlayerStart->GetActorTransform());
		Possess(NewPawn);
		
		if (APraktykiMainMenuHUD* HUD = Cast<APraktykiMainMenuHUD>(GetHUD()))
		{
			HUD->OpenMainMenuWidget();
		}
	}
}

void APraktykiPlayerVehicleController::StartRaceMode(int32 TimeLimit, bool bShowGhost, ELiveryColor LiveryColor, EDamageMode DamageMode)
{
	if (const AActor* PlayerStart = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass()))
	{
		if (APawn* CurrentPawn = GetPawn())
		{
			UnPossess();
			CurrentPawn->Destroy();
		}
		FTransform SpawnPointTransform;
		SpawnPointTransform.SetLocation(FVector(PlayerStart->GetActorLocation().X, PlayerStart->GetActorLocation().Y, 3.f));
		SpawnPointTransform.SetRotation(PlayerStart->GetActorTransform().GetRotation());
		APlayerVehiclePawn* NewPawn = GetWorld()->SpawnActorDeferred<APlayerVehiclePawn>(PlayerVehicleClass, SpawnPointTransform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
		NewPawn->SetLivery(LiveryColor);
		NewPawn->FinishSpawning(SpawnPointTransform);
		
		Possess(NewPawn);

		if (APraktykiPlayerState* PraktykiPlayerState = Cast<APraktykiPlayerState>(PlayerState))
		{
			PraktykiPlayerState->ResetData();
			PraktykiPlayerState->SetTimeLimit(TimeLimit);
			PraktykiPlayerState->SetDamageMode(DamageMode);
			if (TimeLimit != 0) PraktykiPlayerState->InitializeTimeLimit();
			PraktykiPlayerState->SetShouldShowGhost(bShowGhost);
			NewPawn->SetPlayerState(PraktykiPlayerState);
		}
		
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
	EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Completed, this, &APraktykiPlayerVehicleController::StopTurning);
	EnhancedInputComponent->BindAction(ChangeCameraAction, ETriggerEvent::Triggered, this, &APraktykiPlayerVehicleController::ChangeCamera);
	EnhancedInputComponent->BindAction(ResetPositionAction, ETriggerEvent::Triggered, this, &APraktykiPlayerVehicleController::ResetCarPositionToTrack);
	EnhancedInputComponent->BindAction(PauseGameAction, ETriggerEvent::Triggered, this, &APraktykiPlayerVehicleController::PauseGame);
	EnhancedInputComponent->BindAction(RotateCameraAction, ETriggerEvent::Triggered, this, &APraktykiPlayerVehicleController::RotateCamera);
}

void APraktykiPlayerVehicleController::RaceTimeEnded()
{
	if (AActor* PlayerStart = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass()))
	{
		if (APawn* CurrentPawn = GetPawn())
		{
			UnPossess();
			CurrentPawn->Destroy();
		}
		APraktykiSpectatorCamera* NewPawn = GetWorld()->SpawnActor<APraktykiSpectatorCamera>(GetWorld()->GetAuthGameMode()->GetDefaultPawnClassForController(this), PlayerStart->GetActorTransform());
		Possess(NewPawn);
		
		if (APraktykiMainMenuHUD* HUD = Cast<APraktykiMainMenuHUD>(GetHUD()))
		{
			HUD->OpenRaceSummaryWidget();
		}
	}
}

void APraktykiPlayerVehicleController::Accelerate(const FInputActionValue& InputActionValue)
{
	if (const APlayerVehiclePawn* PlayerVehicle = Cast<APlayerVehiclePawn>(GetPawn()))
	{
		PlayerVehicle->GetVehicleMovement()->SetThrottleInput(InputActionValue.Get<float>() * ThrottleMultiplier);
	}
}

void APraktykiPlayerVehicleController::Brake(const FInputActionValue& InputActionValue)
{
	if (const APlayerVehiclePawn* PlayerVehicle = Cast<APlayerVehiclePawn>(GetPawn()))
	{
		if (ThrottleMultiplier == 0) PlayerVehicle->GetVehicleMovement()->SetBrakeInput(0);
		else PlayerVehicle->GetVehicleMovement()->SetBrakeInput(InputActionValue.Get<float>());
	}
}

void APraktykiPlayerVehicleController::Turn(const FInputActionValue& InputActionValue)
{
	if (APlayerVehiclePawn* PlayerVehicle = Cast<APlayerVehiclePawn>(GetPawn()))
	{
		if (GetWorldTimerManager().IsTimerActive(ResetWheelRotationTimer)) GetWorldTimerManager().ClearTimer(ResetWheelRotationTimer);
		PlayerVehicle->GetVehicleMovement()->SetSteeringInput(InputActionValue.Get<float>());
		PlayerVehicle->UpdateSteeringWheelPosition();
	}
}

void APraktykiPlayerVehicleController::StopTurning(const FInputActionValue& InputActionValue)
{
	if (APlayerVehiclePawn* PlayerVehicle = Cast<APlayerVehiclePawn>(GetPawn()))
	{
		PlayerVehicle->GetVehicleMovement()->SetSteeringInput(InputActionValue.Get<float>());
		GetWorldTimerManager().SetTimer(ResetWheelRotationTimer, PlayerVehicle, &APlayerVehiclePawn::RecenterWheel, 0.016f, true);
	}
}

void APraktykiPlayerVehicleController::ChangeCamera()
{
	if (APlayerVehiclePawn* PlayerVehicle = Cast<APlayerVehiclePawn>(GetPawn()))
	{
		if (bCameraSetToInside)
		{
			bCameraSetToInside = false;
			PlayerVehicle->SetCamera(ECameraPosition::ECP_Outside);
		}
		else
		{
			bCameraSetToInside = true;
			PlayerVehicle->SetCamera(ECameraPosition::ECP_Inside);
		}
	}
}

void APraktykiPlayerVehicleController::ResetCarPositionToTrack()
{
	if (APlayerVehiclePawn* PlayerVehicle = Cast<APlayerVehiclePawn>(GetPawn()))
	{
		PlayerVehicle->TeleportToTrack();
	}
}

void APraktykiPlayerVehicleController::PauseGame()
{
	if (APraktykiMainMenuHUD* HUD = Cast<APraktykiMainMenuHUD>(GetHUD()))
	{
		HUD->OpenPauseGameWidget();
	}
}

void APraktykiPlayerVehicleController::RotateCamera(const FInputActionValue& InputActionValue)
{
	if (APlayerVehiclePawn* PlayerVehicle = Cast<APlayerVehiclePawn>(GetPawn()))
	{
		PlayerVehicle->SetCameraRotation(InputActionValue.Get<float>());
	}
}

// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "PlayerVehicle/PlayerVehiclePawn.h"
#include "PraktykiPlayerVehicleController.generated.h"

enum class EDamageMode : uint8;
class AGhostActor;
enum class ELiveryColor : uint8;
class APlayerVehiclePawn;
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
	
public:
	TObjectPtr<AGhostActor> SpawnGhost(const FVector& Location, const FRotator& Rotation) const;
	void RaceTimeEnded();
	FTimerHandle ResetWheelRotationTimer;
	void SetThrottleMultiplier(const float NewMultiplier) { ThrottleMultiplier = NewMultiplier; }
	
protected:
	UFUNCTION(BlueprintCallable)
	void StartPracticeMode();

	UFUNCTION(BlueprintCallable)
	void QuitToMainMenu();

	UFUNCTION(BlueprintCallable)
	void StartRaceMode(int32 TimeLimit, bool bShowGhost, ELiveryColor LiveryColor, EDamageMode DamageMode = EDamageMode::EDM_NoDamage);
	
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> PlayerContext;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> AccelerateAction;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> BrakeAction;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> TurnAction;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> ChangeCameraAction;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> ResetPositionAction;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> PauseGameAction;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> RotateCameraAction;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APlayerVehiclePawn> PlayerVehicleClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGhostActor> GhostActorClass;

	bool bCameraSetToInside = false;
	float ThrottleMultiplier = 1.f;

	void Accelerate(const FInputActionValue& InputActionValue);
	void Brake(const FInputActionValue& InputActionValue);
	void Turn(const FInputActionValue& InputActionValue);
	void StopTurning(const FInputActionValue& InputActionValue);
	void ChangeCamera();
	void ResetCarPositionToTrack();
	void PauseGame();
	void RotateCamera(const FInputActionValue& InputActionValue);
};
// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PraktykiPlayerVehicleController.generated.h"

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
	
protected:
	UFUNCTION(BlueprintCallable)
	void StartPracticeMode();

	UFUNCTION(BlueprintCallable)
	void StartRaceMode(int32 TimeLimit, bool bShowGhost, ELiveryColor LiveryColor);
	
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

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APlayerVehiclePawn> PlayerVehicleClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGhostActor> GhostActorClass;

	void Accelerate(const FInputActionValue& InputActionValue);
	void Brake(const FInputActionValue& InputActionValue);
	void Turn(const FInputActionValue& InputActionValue);
	void RotateCamera(const FInputActionValue& InputActionValue);
};
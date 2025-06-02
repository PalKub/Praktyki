// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "PlayerVehiclePawn.generated.h"

class USpringArmComponent;
class UCameraComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpeedChangedSignature, int32, Speed);
/**
 * 
 */
UENUM(BlueprintType)
enum class ELiveryColor : uint8
{
	ELC_Default UMETA(DisplayName = "Default"),
	ELC_Blue UMETA(DisplayName = "Blue"),
	ELC_Orange UMETA(DisplayName = "Orange"),
	ELC_Red UMETA(DisplayName = "Red")
};

UENUM()
enum class ECameraPosition : uint8
{
	ECP_Outside UMETA(DisplayName = "Outside"),
	ECP_Inside UMETA(DisplayName = "Inside")
};

UCLASS()
class PRAKTYKI_API APlayerVehiclePawn : public AWheeledVehiclePawn
{
	GENERATED_BODY()

public:
	APlayerVehiclePawn();

	UPROPERTY(BlueprintAssignable)
	FOnSpeedChangedSignature OnSpeedChangedDelegate;

	FTimerHandle UpdateSpeedTimer;

	void SetCameraRotation(const FVector2D NewRotation);
	void SetLivery(const ELiveryColor LiveryColor);
	void SetCamera(const ECameraPosition CameraPosition) const;
	void UpdateSteeringWheelPosition() const;
	void RecenterWheel() const;

protected:
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;
	
private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> InteriorMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> ConsoleMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> DoorLeftMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> DoorRightMeshComponent;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> FenderLeftMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> FenderRightMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent>  EngineMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> WindshieldMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> FrontBumperMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> RearBumperMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> HoodMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> BodyMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> DiffuserMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> SpoilerMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> NetMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> BootMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> SeatMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> FrontLeftCaliperMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> FrontRightCaliperMeshComponent;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> BackLeftCaliperMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> BackRightCaliperMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> FrontLeftWheelMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> FrontRightWheelMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> BackLeftWheelMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> BackRightWheelMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> FrontLeftRotorMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> FrontRightRotorMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> BackLeftRotorMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> BackRightRotorMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> LeftMirrorMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> RightMirrorMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> SteeringWheelMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(EditDefaultsOnly)
	float UpdateSpeedFrequency = 0.1f;

	UPROPERTY(EditDefaultsOnly)
	FLinearColor LiveryBlueColor;

	UPROPERTY(EditDefaultsOnly)
	FLinearColor LiveryOrangeColor;

	UPROPERTY(EditDefaultsOnly)
	FLinearColor LiveryRedColor;

	int32 VehicleSpeed = 0;
	TArray<TObjectPtr<UStaticMeshComponent>> LiveryMeshes;

	void UpdateSpeed();
	void SetLiveryColor(const FLinearColor Color);
};
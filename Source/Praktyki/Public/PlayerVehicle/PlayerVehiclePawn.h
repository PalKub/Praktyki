// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "Components/TimelineComponent.h"
#include "PlayerVehiclePawn.generated.h"

class UTimelineComponent;
class APraktykiPlayerState;
class APraktykiPlayerVehicleController;
class UChaosWheeledVehicleMovementComponent;
class UImpactPoint;
class USpringArmComponent;
class UCameraComponent;

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

UENUM(BlueprintType)
enum class EDamageMode : uint8
{
	EDM_NoDamage UMETA(DisplayName = "NoDamage"),
	EDM_Cosmetic UMETA(DisplayName = "Cosmetic"),
	EDM_Mechanical UMETA(DisplayName = "Mechanical")
};

UENUM(BlueprintType)
enum class EDamageLevel : uint8
{
	EDL_None UMETA(DisplayName = "None"),
	EDL_Minor UMETA(DisplayName = "Minor"),
	EDL_Serious UMETA(DisplayName = "Serious"),
	EDL_Critical UMETA(DisplayName = "Critical"),
	EDL_Broken UMETA(DisplayName = "Broken")
};

UENUM()
enum class ECameraPosition : uint8
{
	ECP_Outside UMETA(DisplayName = "Outside"),
	ECP_Inside UMETA(DisplayName = "Inside")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpeedChangedSignature, int32, Speed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDamageLevelChangedSignature, EDamageLevel, DamageLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCooldownTimeChangedSignature, int32, TimeRemaining);

UCLASS()
class PRAKTYKI_API APlayerVehiclePawn : public AWheeledVehiclePawn
{
	GENERATED_BODY()

public:
	APlayerVehiclePawn();

	UPROPERTY(BlueprintAssignable)
	FOnSpeedChangedSignature OnSpeedChangedDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnDamageLevelChangedSignature OnDamageLevelChangedDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnCooldownTimeChangedSignature OnCooldownTimeChangedDelegate;

	FTimerHandle UpdateSpeedTimer;
	FTimerHandle EndSessionTimer;
	
	void SetCameraRotation(const float NewRotation);
	void SetLivery(const ELiveryColor LiveryColor);
	void SetCamera(const ECameraPosition CameraPosition) const;
	void UpdateSteeringWheelPosition() const;
	void RecenterWheel() const;
	void SetPlayerState(APraktykiPlayerState* NewPlayerState) { PlayerState = NewPlayerState; }
	void TeleportToTrack();

protected:
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	
private:
	/** Body Meshes */
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
	/** end Body Meshes */

	/** Camera */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USpringArmComponent> SpringArm;
	/** end Camera */

	/** Impact Points */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UImpactPoint> ImpactPointLeftFront;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UImpactPoint> ImpactPointLeftRear;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UImpactPoint> ImpactPointRightFront;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UImpactPoint> ImpactPointRightRear;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UImpactPoint> ImpactPointFront;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UImpactPoint> ImpactPointRear;
	/** end Impact Points */

	
	/** Vehicle Settings */
	UPROPERTY(EditDefaultsOnly, Category = "General Settings")
	float UpdateSpeedFrequency = 0.1f;

	UPROPERTY(EditDefaultsOnly, Category = "General Settings")
	float CollisionEventFrequency = 0.3f;

	UPROPERTY(EditDefaultsOnly, Category = "General Settings")
	float DamageScaling = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "General Settings")
	int32 ResetToTrackCooldownTime = 3;

	UPROPERTY(EditDefaultsOnly, Category = "General Settings")
	float TimeTillSessionEndAfterCarTotalled = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = "Livery")
	FLinearColor LiveryBlueColor;

	UPROPERTY(EditDefaultsOnly, Category = "Livery")
	FLinearColor LiveryOrangeColor;

	UPROPERTY(EditDefaultsOnly, Category = "Livery")
	FLinearColor LiveryRedColor;

	UPROPERTY(EditDefaultsOnly, Category = "Camera Settings")
	float CameraRecenterDelay = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "Camera Settings")
	float CameraRecenterVelocityThreshold = 200.f;

	UPROPERTY(EditDefaultsOnly, Category = "Camera Settings")
	float CameraAutoRecenterTime = 0.5f;
	
	/** end Vehicle Settings */
	
	UPROPERTY()
	TObjectPtr<UTimelineComponent> CameraRecenterTimeline;

	UPROPERTY()
	TObjectPtr<UCurveFloat> CameraRotationCurve;

	/** Lap Specific Data */
	FOnTimelineFloat CameraRotationProgressFunction;
	FTransformCurve LapCurve;
	float VehicleDamagePercentage = 0.f;
	int32 VehicleSpeed = 0;
	float LastHitTime = 0.f;
	int32 CooldownTimeRemaining = 0.f;
	FTimerHandle CooldownTimer;
	FTimerHandle RecenterCameraTimer;
	EDamageLevel CurrentDamageLevel = EDamageLevel::EDL_None;
	TArray<TObjectPtr<UStaticMeshComponent>> LiveryMeshes;
	TArray<TObjectPtr<UImpactPoint>> ImpactPoints;
	TObjectPtr<UChaosWheeledVehicleMovementComponent> WheeledMovementComponent;
	TObjectPtr<APraktykiPlayerVehicleController> PlayerVehicleController;
	TObjectPtr<APraktykiPlayerState> PlayerState;
	FRotator CameraDefaultRotation = FRotator();
	/** end Lap Specific Data */

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void UpdateCameraRotation(const float Rotation);

	void UpdateSpeed();
	void SetLiveryColor(const FLinearColor Color);
	TObjectPtr<UImpactPoint> FindClosestImpactPointToLocation (const FVector& Location);
	void ApplyCosmeticDamage(UImpactPoint* ImpactPoint, const float Percent);
	void ApplyMechanicalDamage(const float Percent);
	void CountDownCooldownTime();
	void RecenterCamera();
	void EndSession() const;
};
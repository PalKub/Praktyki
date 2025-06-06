// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "GhostActor.generated.h"

class UTimelineComponent;

UCLASS()
class PRAKTYKI_API AGhostActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AGhostActor();
	void SetLapData(const FTransformCurve& TransformCurve, UCurveFloat* DistanceAtLapTime, UCurveFloat* LapTimeAtDistance);
	void StartMoving() const;

protected:
	virtual void Destroyed() override;
	
private:
	/** Body Meshes */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> MainMesh;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> DoorLeftMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> DoorRightMeshComponent;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> FenderLeftMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> FenderRightMeshComponent;

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
	TObjectPtr<UStaticMeshComponent> BootMeshComponent;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> FrontLeftWheelMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> FrontRightWheelMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> BackLeftWheelMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> BackRightWheelMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> LeftMirrorMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> RightMirrorMeshComponent;
	/** end Body Meshes */

	//Material
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMaterialInstance> GhostCarMaterial;

	/** Transform update Timeline Data */
	UPROPERTY()
	TObjectPtr<UTimelineComponent> TransformTimeline;

	UPROPERTY()
	TObjectPtr<UCurveFloat> DistanceToLapTime;

	UPROPERTY()
	TObjectPtr<UCurveFloat> LapTimeToDistance;
	
	FOnTimelineFloat ProgressFunction;
	FOnTimelineEvent FinishedFunction;
	FTransformCurve LapCurve;
	/** end Transform update Timeline Data */

	UFUNCTION()
	void UpdateTimeline(const float Distance);

	UFUNCTION()
	void TimeLineFinished();
};
// Copyright 2025 Teyon. All Rights Reserved.


#include "PlayerVehicle/PlayerVehiclePawn.h"

#include "ChaosVehicleMovementComponent.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ImpactPoint.h"
#include "Components/SplineComponent.h"
#include "Game/PraktykiGameInstance.h"
#include "Game/PraktykiPlayerState.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerController/PraktykiPlayerVehicleController.h"

APlayerVehiclePawn::APlayerVehiclePawn()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.1f;
	
	InteriorMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Interior");
	InteriorMeshComponent->SetupAttachment(GetMesh());

	ConsoleMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Console");
	ConsoleMeshComponent->SetupAttachment(GetMesh());

	DoorLeftMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Door_Left");
	DoorLeftMeshComponent->SetupAttachment(GetMesh(), "DoorLeftSocket");
	LiveryMeshes.Add(DoorLeftMeshComponent);

	DoorRightMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Door_Right");
	DoorRightMeshComponent->SetupAttachment(GetMesh(), "DoorRightSocket");
	LiveryMeshes.Add(DoorRightMeshComponent);

	FenderLeftMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Fender_Left");
	FenderLeftMeshComponent->SetupAttachment(GetMesh(), "FenderLeftSocket");
	LiveryMeshes.Add(FenderLeftMeshComponent);

	FenderRightMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Fender_Right");
	FenderRightMeshComponent->SetupAttachment(GetMesh(), "FenderRightSocket");
	LiveryMeshes.Add(FenderRightMeshComponent);

	EngineMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Engine");
	EngineMeshComponent->SetupAttachment(GetMesh());

	WindshieldMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Windshield");
	WindshieldMeshComponent->SetupAttachment(GetMesh());

	FrontBumperMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Bumper_Front");
	FrontBumperMeshComponent->SetupAttachment(GetMesh(), "BumperFrontSocket");
	LiveryMeshes.Add(FrontBumperMeshComponent);

	RearBumperMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Bumper_Rear");
	RearBumperMeshComponent->SetupAttachment(GetMesh(), "BumperRearSocket");
	LiveryMeshes.Add(RearBumperMeshComponent);

	HoodMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Hood");
	HoodMeshComponent->SetupAttachment(GetMesh(), "HoodSocket");
	LiveryMeshes.Add(HoodMeshComponent);

	BodyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Body");
	BodyMeshComponent->SetupAttachment(GetMesh());
	LiveryMeshes.Add(BodyMeshComponent);

	DiffuserMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Diffuser");
	DiffuserMeshComponent->SetupAttachment(GetMesh(), "DiffuserSocket");

	SpoilerMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Spoiler");
	SpoilerMeshComponent->SetupAttachment(GetMesh(), "SpoilerSocket");
	LiveryMeshes.Add(SpoilerMeshComponent);
	
	NetMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Net");
	NetMeshComponent->SetupAttachment(GetMesh());

	BootMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Boot");
	BootMeshComponent->SetupAttachment(GetMesh(), "BootSocket");
	LiveryMeshes.Add(BootMeshComponent);

	SeatMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Seat");
	SeatMeshComponent->SetupAttachment(GetMesh());

	FrontLeftCaliperMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Front_Left_Caliper");
	FrontLeftCaliperMeshComponent->SetupAttachment(GetMesh(), "FrontLeftSuspensionSocket");

	FrontRightCaliperMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Front_Right_Caliper");
	FrontRightCaliperMeshComponent->SetupAttachment(GetMesh(), "FrontRightSuspensionSocket");

	BackLeftCaliperMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Back_Left_Caliper");
	BackLeftCaliperMeshComponent->SetupAttachment(GetMesh(), "BackLeftSuspensionSocket");

	BackRightCaliperMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Back_Right_Caliper");
	BackRightCaliperMeshComponent->SetupAttachment(GetMesh(), "BackRightSuspensionSocket");

	FrontLeftWheelMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Front_Left_Wheel");
	FrontLeftWheelMeshComponent->SetupAttachment(GetMesh(), "FrontLeftWheelSocket");

	FrontRightWheelMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Front_Right_Wheel");
	FrontRightWheelMeshComponent->SetupAttachment(GetMesh(), "FrontRightWheelSocket");

	BackLeftWheelMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Back_Left_Wheel");
	BackLeftWheelMeshComponent->SetupAttachment(GetMesh(), "BackLeftWheelSocket");

	BackRightWheelMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Back_Right_Wheel");
	BackRightWheelMeshComponent->SetupAttachment(GetMesh(), "BackRightWheelSocket");

	FrontLeftRotorMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Front_Left_Rotor");
	FrontLeftRotorMeshComponent->SetupAttachment(GetMesh(), "FrontLeftWheelSocket");

	FrontRightRotorMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Front_Right_Rotor");
	FrontRightRotorMeshComponent->SetupAttachment(GetMesh(), "FrontRightWheelSocket");

	BackLeftRotorMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Back_Left_Rotor");
	BackLeftRotorMeshComponent->SetupAttachment(GetMesh(), "BackLeftWheelSocket");

	BackRightRotorMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Back_Right_Rotor");
	BackRightRotorMeshComponent->SetupAttachment(GetMesh(), "BackRightWheelSocket");

	LeftMirrorMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mirror_Left");
	LeftMirrorMeshComponent->SetupAttachment(GetMesh(), "MirrorLeftSocket");
	LiveryMeshes.Add(LeftMirrorMeshComponent);

	RightMirrorMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mirror_Right");
	RightMirrorMeshComponent->SetupAttachment(GetMesh(), "MirrorRightSocket");
	LiveryMeshes.Add(RightMirrorMeshComponent);

	SteeringWheelMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("SteeringWheel");
	SteeringWheelMeshComponent->SetupAttachment(GetMesh(), "SteeringWheelSocket");

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	ImpactPointLeftFront = CreateDefaultSubobject<UImpactPoint>("ImpactPointLeftFront");
	ImpactPointLeftFront->SetupAttachment(GetMesh());
	ImpactPointLeftFront->BodyMeshesImpacted.Add(DoorLeftMeshComponent);
	ImpactPointLeftFront->BodyMeshesImpacted.Add(FenderLeftMeshComponent);
	ImpactPointLeftFront->BodyMeshesImpacted.Add(FrontBumperMeshComponent);
	ImpactPointLeftFront->BodyMeshesImpacted.Add(LeftMirrorMeshComponent);
	ImpactPointLeftFront->BodyMeshesImpacted.Add(WindshieldMeshComponent);
	ImpactPoints.Add(ImpactPointLeftFront);

	ImpactPointLeftRear = CreateDefaultSubobject<UImpactPoint>("ImpactPointLeftRear");
	ImpactPointLeftRear->SetupAttachment(GetMesh());
	ImpactPointLeftRear->BodyMeshesImpacted.Add(BodyMeshComponent);
	ImpactPointLeftRear->BodyMeshesImpacted.Add(RearBumperMeshComponent);
	ImpactPoints.Add(ImpactPointLeftRear);

	ImpactPointRightFront = CreateDefaultSubobject<UImpactPoint>("ImpactPointRightFront");
	ImpactPointRightFront->SetupAttachment(GetMesh());
	ImpactPointRightFront->BodyMeshesImpacted.Add(DoorRightMeshComponent);
	ImpactPointRightFront->BodyMeshesImpacted.Add(FenderRightMeshComponent);
	ImpactPointRightFront->BodyMeshesImpacted.Add(FrontBumperMeshComponent);
	ImpactPointRightFront->BodyMeshesImpacted.Add(RightMirrorMeshComponent);
	ImpactPointRightFront->BodyMeshesImpacted.Add(WindshieldMeshComponent);
	ImpactPoints.Add(ImpactPointRightFront);

	ImpactPointRightRear = CreateDefaultSubobject<UImpactPoint>("ImpactPointRightRear");
	ImpactPointRightRear->SetupAttachment(GetMesh());
	ImpactPointRightRear->BodyMeshesImpacted.Add(BodyMeshComponent);
	ImpactPointRightRear->BodyMeshesImpacted.Add(RearBumperMeshComponent);
	ImpactPoints.Add(ImpactPointRightRear);

	ImpactPointFront = CreateDefaultSubobject<UImpactPoint>("ImpactPointFront");
	ImpactPointFront->SetupAttachment(GetMesh());
	ImpactPointFront->BodyMeshesImpacted.Add(FrontBumperMeshComponent);
	ImpactPointFront->BodyMeshesImpacted.Add(HoodMeshComponent);
	ImpactPointFront->BodyMeshesImpacted.Add(WindshieldMeshComponent);
	ImpactPoints.Add(ImpactPointFront);

	ImpactPointRear = CreateDefaultSubobject<UImpactPoint>("ImpactPointRear");
	ImpactPointRear->SetupAttachment(GetMesh());
	ImpactPointRear->BodyMeshesImpacted.Add(RearBumperMeshComponent);
	ImpactPointRear->BodyMeshesImpacted.Add(BootMeshComponent);
	ImpactPointRear->BodyMeshesImpacted.Add(SpoilerMeshComponent);
	ImpactPoints.Add(ImpactPointRear);

	Tags.Add("Player");
}

void APlayerVehiclePawn::SetCameraRotation(const FVector2D NewRotation)
{
	SpringArm->AddRelativeRotation(FRotator(NewRotation.Y, NewRotation.X, 0.f));
}

void APlayerVehiclePawn::SetLivery(const ELiveryColor LiveryColor)
{
	switch (LiveryColor)
	{
	case ELiveryColor::ELC_Default:
		for (int32 i = 0; i < LiveryMeshes.Num(); i++)
		{
			if (!LiveryMeshes[i]->GetMaterial(0)->IsA(UMaterialInstanceDynamic::StaticClass()))
			{
				UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(LiveryMeshes[i]->GetMaterial(0), this);
				LiveryMeshes[i]->SetMaterial(0, DynamicMaterial);
				DynamicMaterial->SetScalarParameterValue(TEXT("EnablePaintColor"), 0.0f);
			}
			else Cast<UMaterialInstanceDynamic>(LiveryMeshes[i]->GetMaterial(0))->SetStaticSwitchParameterValueEditorOnly(TEXT("EnablePaintColor"), 0.0f);
			return;
		}

	case ELiveryColor::ELC_Blue:
		SetLiveryColor(LiveryBlueColor);
		break;

	case ELiveryColor::ELC_Orange:
		SetLiveryColor(LiveryOrangeColor);
		break;

	case ELiveryColor::ELC_Red:
		SetLiveryColor(LiveryRedColor);
		break;
	}
}

void APlayerVehiclePawn::SetCamera(const ECameraPosition CameraPosition) const
{
	switch (CameraPosition)
	{
	case ECameraPosition::ECP_Inside:
		Camera->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "CarInteriorGameplayCamera");
		break;

	case ECameraPosition::ECP_Outside:
		Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		break;
	}
}

void APlayerVehiclePawn::UpdateSteeringWheelPosition() const
{
	if (WheeledMovementComponent)
	{
		if (WheeledMovementComponent->Wheels.Num() > 3 && GetWorld()->HasBegunPlay())
		{
			float SteeringAngle; 
			if (WheeledMovementComponent->Wheels[0]->GetSteerAngle() < 0) SteeringAngle = WheeledMovementComponent->Wheels[0]->GetSteerAngle();
			else SteeringAngle = WheeledMovementComponent->Wheels[1]->GetSteerAngle();
			FRotator NewRotation;
			NewRotation.Roll = SteeringAngle * 2;
			NewRotation.Pitch = SteeringWheelMeshComponent->GetRelativeRotation().Pitch;
			NewRotation.Yaw = SteeringWheelMeshComponent->GetRelativeRotation().Yaw;
			SteeringWheelMeshComponent->SetRelativeRotation(NewRotation);
		}
	}
}

void APlayerVehiclePawn::RecenterWheel() const
{
	if (WheeledMovementComponent)
	{
		if (WheeledMovementComponent->Wheels.Num() > 3 && GetWorld()->HasBegunPlay())
		{
			float SteeringAngle; 
			if (WheeledMovementComponent->Wheels[0]->GetSteerAngle() < 0) SteeringAngle = WheeledMovementComponent->Wheels[0]->GetSteerAngle();
			else SteeringAngle = WheeledMovementComponent->Wheels[1]->GetSteerAngle();
			FRotator NewRotation;
			NewRotation.Roll = SteeringAngle * 2;
			NewRotation.Pitch = SteeringWheelMeshComponent->GetRelativeRotation().Pitch;
			NewRotation.Yaw = SteeringWheelMeshComponent->GetRelativeRotation().Yaw;
			SteeringWheelMeshComponent->SetRelativeRotation(NewRotation);
			if (SteeringAngle == 0)
			{
				if (APraktykiPlayerVehicleController* VehicleController = Cast<APraktykiPlayerVehicleController>(Controller))
				{
					VehicleController->GetWorldTimerManager().ClearTimer(VehicleController->ResetWheelRotationTimer);
				}
			}
		}
	}
}

void APlayerVehiclePawn::TeleportToTrack()
{
	if (CooldownTimeRemaining == 0)
	{
		if(UPraktykiGameInstance* GameInstance = Cast<UPraktykiGameInstance>(GetGameInstance()))
		{
			const USplineComponent* TrackSpline = GameInstance->GetSpectatorCameraSpline();
			const FTransform Transform = TrackSpline->FindTransformClosestToWorldLocation(GetActorLocation(), ESplineCoordinateSpace::World);
			const FVector NewPawnLocation = FVector(Transform.GetLocation().X, Transform.GetLocation().Y, Transform.GetLocation().Z - 67.f);
			GetMesh()->SetSimulatePhysics(false);
			TeleportTo(NewPawnLocation, Transform.Rotator(), true, true);
			CooldownTimeRemaining = ResetToTrackCooldownTime;
			GetWorldTimerManager().SetTimer(CooldownTimer, this, &APlayerVehiclePawn::CountDownCooldownTime, 1.f, true, 0.f);
		}
	}
}

void APlayerVehiclePawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	GetWorldTimerManager().SetTimer(UpdateSpeedTimer, this, &APlayerVehiclePawn::UpdateSpeed, UpdateSpeedFrequency, true);
}

void APlayerVehiclePawn::UnPossessed()
{
	Super::UnPossessed();

	if (GetWorldTimerManager().IsTimerActive(UpdateSpeedTimer)) GetWorldTimerManager().ClearTimer(UpdateSpeedTimer);
}

void APlayerVehiclePawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (WheeledMovementComponent)
	{
		for (int32 i = 0; i < WheeledMovementComponent->GetNumWheels(); i++)
		{
			const FWheelStatus& WheelStatus = WheeledMovementComponent->GetWheelState(i);
			if (WheelStatus.bInContact)
			{
				switch (UPhysicalMaterial::DetermineSurfaceType(WheelStatus.PhysMaterial.Get()))
				{
				case SurfaceType1:
					WheeledMovementComponent->SetWheelFrictionMultiplier(i, 1.f);
					break;

				case SurfaceType2:
					WheeledMovementComponent->SetWheelFrictionMultiplier(i, 0.5f);
					break;

				case SurfaceType3:
					WheeledMovementComponent->SetWheelFrictionMultiplier(i, 0.3f);
					break;

				default:
					break;
				}
			}
		}
	}
}

void APlayerVehiclePawn::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->SetNotifyRigidBodyCollision(true);
	GetMesh()->OnComponentHit.AddDynamic(this, &APlayerVehiclePawn::OnHit);
	WheeledMovementComponent = Cast<UChaosWheeledVehicleMovementComponent>(GetVehicleMovementComponent());
}

void APlayerVehiclePawn::UpdateSpeed()
{
	if (const int32 CurrentSpeed = FMath::TruncToInt32(GetVehicleMovementComponent()->GetForwardSpeed() * 0.036f); CurrentSpeed != VehicleSpeed)
	{
		VehicleSpeed = CurrentSpeed;
		OnSpeedChangedDelegate.Broadcast(VehicleSpeed);
	}
}

void APlayerVehiclePawn::SetLiveryColor(const FLinearColor Color)
{
	for (int32 i = 0; i < LiveryMeshes.Num(); i++)
	{
		if (!LiveryMeshes[i]->GetMaterial(0)->IsA(UMaterialInstanceDynamic::StaticClass()))
		{
			UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(LiveryMeshes[i]->GetMaterial(0), this);
			LiveryMeshes[i]->SetMaterial(0, DynamicMaterial);
			DynamicMaterial->SetScalarParameterValue(TEXT("EnablePaintColor"), 1.f);
			DynamicMaterial->SetVectorParameterValue(TEXT("PaintColor"), Color);
		}
		else
		{
			Cast<UMaterialInstanceDynamic>(LiveryMeshes[i]->GetMaterial(0))->SetScalarParameterValue(TEXT("EnablePaintColor"), 1.f);
			Cast<UMaterialInstanceDynamic>(LiveryMeshes[i]->GetMaterial(0))->SetVectorParameterValue(TEXT("PaintColor"), Color);
		}
	}
}

TObjectPtr<UImpactPoint> APlayerVehiclePawn::FindClosestImpactPointToLocation(const FVector& Location)
{
	float ClosestDistance = 0.f;
	UImpactPoint* ClosestImpactPoint = nullptr;

	for (UImpactPoint* ImpactPoint : ImpactPoints)
	{
		const float Distance = FVector::Distance(Location, ImpactPoint->GetComponentLocation());
		if (Distance < ClosestDistance || ClosestDistance == 0.f)
		{
			ClosestImpactPoint = ImpactPoint;
			ClosestDistance = Distance;
		}
	}
	return ClosestImpactPoint;
}

void APlayerVehiclePawn::ApplyCosmeticDamage(UImpactPoint* ImpactPoint, const float Percent)
{
	for (UStaticMeshComponent* MeshToDamage : ImpactPoint->BodyMeshesImpacted)
	{
		for (int32 i = 0; i < MeshToDamage->GetNumMaterials(); i++)
		{
			if (!MeshToDamage->GetMaterial(i)->IsA(UMaterialInstanceDynamic::StaticClass()))
			{
				UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(MeshToDamage->GetMaterial(i), this);
				MeshToDamage->SetMaterial(i, DynamicMaterial);
				float CurrentDamagePercent;
				DynamicMaterial->GetScalarParameterValue(TEXT("DamageValue"), CurrentDamagePercent);
				DynamicMaterial->SetScalarParameterValue(TEXT("DamageValue"), FMath::Min(1.f, Percent + CurrentDamagePercent));
			}
			else
			{
				float CurrentDamagePercent;
				MeshToDamage->GetMaterial(i)->GetScalarParameterValue(TEXT("DamageValue"), CurrentDamagePercent);
				Cast<UMaterialInstanceDynamic>(MeshToDamage->GetMaterial(i))->SetScalarParameterValue(TEXT("DamageValue"), FMath::Min(1.f, Percent + CurrentDamagePercent));
			}
		}
	}
}

void APlayerVehiclePawn::ApplyMechanicalDamage(const float Percent)
{
	VehicleDamagePercentage += Percent;
	EDamageLevel DamageLevel = EDamageLevel::EDL_None;
	
	if (!PlayerVehicleController) PlayerVehicleController = Cast<APraktykiPlayerVehicleController>(GetController());
	if (PlayerVehicleController)
	{
		if (VehicleDamagePercentage < 0.25f) return;

		if (VehicleDamagePercentage >= 1.f)
		{
			PlayerVehicleController->SetThrottleMultiplier(0.f);
			DamageLevel = EDamageLevel::EDL_Broken;
		}
		else if (VehicleDamagePercentage >= 0.75f)
		{
			PlayerVehicleController->SetThrottleMultiplier(0.4f);
			DamageLevel = EDamageLevel::EDL_Critical;
		}
		else if (VehicleDamagePercentage >= 0.5f)
		{
			PlayerVehicleController->SetThrottleMultiplier(0.7f);
			DamageLevel = EDamageLevel::EDL_Serious;
		}
		else if (VehicleDamagePercentage >= 0.25)
		{
			PlayerVehicleController->SetThrottleMultiplier(0.9f);
			DamageLevel = EDamageLevel::EDL_Minor;
		}

		if (DamageLevel != CurrentDamageLevel)
		{
			CurrentDamageLevel = DamageLevel;
			OnDamageLevelChangedDelegate.Broadcast(CurrentDamageLevel);
		}
	}
}

void APlayerVehiclePawn::CountDownCooldownTime()
{
	OnCooldownTimeChangedDelegate.Broadcast(CooldownTimeRemaining);
	CooldownTimeRemaining -= 1;

	if (CooldownTimeRemaining <= -1)
	{
		GetWorldTimerManager().ClearTimer(CooldownTimer);
		GetMesh()->SetSimulatePhysics(true);
		GetVehicleMovementComponent()->RecreatePhysicsState();
		GetVehicleMovementComponent()->ResetVehicle();
		CooldownTimeRemaining = 0;
	}
}

void APlayerVehiclePawn::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (PlayerState)
	{
		if (PlayerState->GetDamageMode() == EDamageMode::EDM_NoDamage) return;
		
		const float ImpactForce = NormalImpulse.Size();
		const float Time = GetWorld()->GetTimeSeconds();

		if (Time - LastHitTime < CollisionEventFrequency || ImpactForce < 400000.f) return;

		LastHitTime = Time;
		UImpactPoint* ClosestImpactPoint = FindClosestImpactPointToLocation(Hit.Location);
		const float DamagePercent = ImpactForce / 5000000 * DamageScaling;
	
		ApplyCosmeticDamage(ClosestImpactPoint, DamagePercent);
		if (PlayerState->GetDamageMode() == EDamageMode::EDM_Mechanical) ApplyMechanicalDamage(DamagePercent);
	}
}

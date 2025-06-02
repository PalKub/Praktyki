// Copyright 2025 Teyon. All Rights Reserved.


#include "PlayerVehicle/PlayerVehiclePawn.h"

#include "ChaosVehicleMovementComponent.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerController/PraktykiPlayerVehicleController.h"

APlayerVehiclePawn::APlayerVehiclePawn()
{
	PrimaryActorTick.bCanEverTick = false;
	
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
	if (UChaosWheeledVehicleMovementComponent* MovementComponent = Cast<UChaosWheeledVehicleMovementComponent>(GetVehicleMovementComponent()))
	{
		if (MovementComponent->Wheels.Num() > 3 && GetWorld()->HasBegunPlay())
		{
			float SteeringAngle; 
			if (MovementComponent->Wheels[0]->GetSteerAngle() < 0) SteeringAngle = MovementComponent->Wheels[0]->GetSteerAngle();
			else SteeringAngle = MovementComponent->Wheels[1]->GetSteerAngle();
			FRotator NewRotation;
			NewRotation.Roll = SteeringAngle;
			NewRotation.Pitch = SteeringWheelMeshComponent->GetRelativeRotation().Pitch;
			NewRotation.Yaw = SteeringWheelMeshComponent->GetRelativeRotation().Yaw;
			SteeringWheelMeshComponent->SetRelativeRotation(NewRotation);
		}
	}
}

void APlayerVehiclePawn::RecenterWheel() const
{
	if (UChaosWheeledVehicleMovementComponent* MovementComponent = Cast<UChaosWheeledVehicleMovementComponent>(GetVehicleMovementComponent()))
	{
		if (MovementComponent->Wheels.Num() > 3 && GetWorld()->HasBegunPlay())
		{
			float SteeringAngle; 
			if (MovementComponent->Wheels[0]->GetSteerAngle() < 0) SteeringAngle = MovementComponent->Wheels[0]->GetSteerAngle();
			else SteeringAngle = MovementComponent->Wheels[1]->GetSteerAngle();
			FRotator NewRotation;
			NewRotation.Roll = SteeringAngle;
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
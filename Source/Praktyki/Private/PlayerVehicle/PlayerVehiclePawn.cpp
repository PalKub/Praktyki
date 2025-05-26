// Copyright 2025 Teyon. All Rights Reserved.


#include "PlayerVehicle/PlayerVehiclePawn.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

APlayerVehiclePawn::APlayerVehiclePawn()
{
	InteriorMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Interior");
	InteriorMeshComponent->SetupAttachment(GetMesh());

	ConsoleMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Console");
	ConsoleMeshComponent->SetupAttachment(GetMesh());

	DoorLeftMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Door_Left");
	DoorLeftMeshComponent->SetupAttachment(GetMesh(), "DoorLeftSocket");

	DoorRightMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Door_Right");
	DoorRightMeshComponent->SetupAttachment(GetMesh(), "DoorRightSocket");

	FenderLeftMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Fender_Left");
	FenderLeftMeshComponent->SetupAttachment(GetMesh(), "FenderLeftSocket");

	FenderRightMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Fender_Right");
	FenderRightMeshComponent->SetupAttachment(GetMesh(), "FenderRightSocket");

	EngineMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Engine");
	EngineMeshComponent->SetupAttachment(GetMesh());

	WindshieldMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Windshield");
	WindshieldMeshComponent->SetupAttachment(GetMesh());

	FrontBumperMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Bumper_Front");
	FrontBumperMeshComponent->SetupAttachment(GetMesh(), "BumperFrontSocket");

	RearBumperMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Bumper_Rear");
	RearBumperMeshComponent->SetupAttachment(GetMesh(), "BumperRearSocket");

	HoodMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Hood");
	HoodMeshComponent->SetupAttachment(GetMesh(), "HoodSocket");

	BodyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Body");
	BodyMeshComponent->SetupAttachment(GetMesh());

	DiffuserMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Diffuser");
	DiffuserMeshComponent->SetupAttachment(GetMesh(), "DiffuserSocket");

	SpoilerMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Spoiler");
	SpoilerMeshComponent->SetupAttachment(GetMesh(), "SpoilerSocket");
	
	NetMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Net");
	NetMeshComponent->SetupAttachment(GetMesh());

	BootMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Boot");
	BootMeshComponent->SetupAttachment(GetMesh(), "BootSocket");

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

	RightMirrorMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mirror_Right");
	RightMirrorMeshComponent->SetupAttachment(GetMesh(), "MirrorRightSocket");

	SteeringWheelMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("SteeringWheel");
	SteeringWheelMeshComponent->SetupAttachment(GetMesh(), "SteeringWheelSocket");

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
}

void APlayerVehiclePawn::SetCameraRotation(const FVector2D NewRotation)
{
	SpringArm->AddRelativeRotation(FRotator(NewRotation.Y, NewRotation.X, 0.f));
}

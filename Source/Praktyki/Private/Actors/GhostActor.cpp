// Copyright 2025 Teyon. All Rights Reserved.


#include "Actors/GhostActor.h"

#include "Components/TimelineComponent.h"

AGhostActor::AGhostActor()
{
	PrimaryActorTick.bCanEverTick = false;

	MainMesh = CreateDefaultSubobject<USkeletalMeshComponent>("MainMesh");
	SetRootComponent(MainMesh);
	MainMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MainMesh->SetVisibility(false);
	
	DoorLeftMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Door_Left");
	DoorLeftMeshComponent->SetupAttachment(GetRootComponent(), "DoorLeftSocket");
	DoorLeftMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	DoorRightMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Door_Right");
	DoorRightMeshComponent->SetupAttachment(GetRootComponent(), "DoorRightSocket");
	DoorRightMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FenderLeftMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Fender_Left");
	FenderLeftMeshComponent->SetupAttachment(GetRootComponent(), "FenderLeftSocket");
	FenderLeftMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FenderRightMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Fender_Right");
	FenderRightMeshComponent->SetupAttachment(GetRootComponent(), "FenderRightSocket");
	FenderRightMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	WindshieldMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Windshield");
	WindshieldMeshComponent->SetupAttachment(GetRootComponent());
	WindshieldMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FrontBumperMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Bumper_Front");
	FrontBumperMeshComponent->SetupAttachment(GetRootComponent(), "BumperFrontSocket");
	FrontBumperMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RearBumperMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Bumper_Rear");
	RearBumperMeshComponent->SetupAttachment(GetRootComponent(), "BumperRearSocket");
	RearBumperMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	HoodMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Hood");
	HoodMeshComponent->SetupAttachment(GetRootComponent(), "HoodSocket");
	HoodMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BodyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Body");
	BodyMeshComponent->SetupAttachment(GetRootComponent());
	BodyMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	DiffuserMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Diffuser");
	DiffuserMeshComponent->SetupAttachment(GetRootComponent(), "DiffuserSocket");
	DiffuserMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SpoilerMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Spoiler");
	SpoilerMeshComponent->SetupAttachment(GetRootComponent(), "SpoilerSocket");
	SpoilerMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BootMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Boot");
	BootMeshComponent->SetupAttachment(GetRootComponent(), "BootSocket");
	BootMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FrontLeftWheelMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Front_Left_Wheel");
	FrontLeftWheelMeshComponent->SetupAttachment(GetRootComponent(), "FrontLeftWheelSocket");
	FrontLeftWheelMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FrontRightWheelMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Front_Right_Wheel");
	FrontRightWheelMeshComponent->SetupAttachment(GetRootComponent(), "FrontRightWheelSocket");
	FrontRightWheelMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BackLeftWheelMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Back_Left_Wheel");
	BackLeftWheelMeshComponent->SetupAttachment(GetRootComponent(), "BackLeftWheelSocket");
	BackLeftWheelMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BackRightWheelMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Back_Right_Wheel");
	BackRightWheelMeshComponent->SetupAttachment(GetRootComponent(), "BackRightWheelSocket");
	BackRightWheelMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	LeftMirrorMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mirror_Left");
	LeftMirrorMeshComponent->SetupAttachment(GetRootComponent(), "MirrorLeftSocket");
	LeftMirrorMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RightMirrorMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mirror_Right");
	RightMirrorMeshComponent->SetupAttachment(GetRootComponent(), "MirrorRightSocket");
	RightMirrorMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	TransformTimeline = CreateDefaultSubobject<UTimelineComponent>("TransformTimeline");
}

void AGhostActor::SetLapData(const FTransformCurve& TransformCurve, UCurveFloat* DistanceAtLapTime, UCurveFloat* LapTimeAtDistance)
{
	LapCurve = TransformCurve;
	DistanceToLapTime = DistanceAtLapTime;
	ProgressFunction.BindUFunction(this, FName("UpdateTimeline"));
	FinishedFunction.BindUFunction(this, FName("TimeLineFinished"));
	TransformTimeline->AddInterpFloat(LapTimeAtDistance, ProgressFunction);
	TransformTimeline->SetTimelineFinishedFunc(FinishedFunction);
}

void AGhostActor::StartMoving() const
{
	TransformTimeline->SetPlayRate(1.0f);
	TransformTimeline->PlayFromStart();
}

void AGhostActor::Destroyed()
{
	Super::Destroyed();

	if (TransformTimeline->IsActive()) TransformTimeline->Deactivate();
}

void AGhostActor::UpdateTimeline(const float Distance)
{
	const float Time = DistanceToLapTime->GetFloatValue(Distance);
	SetActorTransform(LapCurve.Evaluate(Time, 1.0f));
}

void AGhostActor::TimeLineFinished()
{
	TransformTimeline->Deactivate();
	Destroy();
}
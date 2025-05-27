// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PraktykiSpectatorSpline.generated.h"

class USplineComponent;

UCLASS()
class PRAKTYKI_API APraktykiSpectatorSpline : public AActor
{
	GENERATED_BODY()
	
public:	
	APraktykiSpectatorSpline();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USplineComponent> Spline;
};

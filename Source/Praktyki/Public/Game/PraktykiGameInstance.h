// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PraktykiGameInstance.generated.h"

class USplineComponent;
/**
 * 
 */
UCLASS()
class PRAKTYKI_API UPraktykiGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	void SetSpectatorCameraSpline(USplineComponent* Spline) { SpectatorCameraSpline = Spline; }
	TObjectPtr<USplineComponent> GetSpectatorCameraSpline() { return SpectatorCameraSpline; }

private:
	TObjectPtr<USplineComponent> SpectatorCameraSpline;
};
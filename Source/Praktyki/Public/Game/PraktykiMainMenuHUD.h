// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PraktykiMainMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class PRAKTYKI_API APraktykiMainMenuHUD : public AHUD
{
	GENERATED_BODY()

public:
	void OpenRacingHUDWidget();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> RacingHUDClass;

	TObjectPtr<UUserWidget> MainMenuWidget;
	TObjectPtr<UUserWidget> RacingHUDWidget;
};
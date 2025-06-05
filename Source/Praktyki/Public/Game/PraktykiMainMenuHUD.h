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
	UFUNCTION(BlueprintCallable)
	void OpenMainMenuWidget();

	UFUNCTION(BlueprintCallable)
	void OpenControlsWidget();
	
	void OpenRacingHUDWidget();
	void OpenRaceSummaryWidget();
	void OpenPauseGameWidget();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> RacingHUDClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> RaceSummaryWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> ControlWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> PauseGameWidgetClass;

	TObjectPtr<UUserWidget> MainMenuWidget;
	TObjectPtr<UUserWidget> RacingHUDWidget;
	TObjectPtr<UUserWidget> RaceSummaryWidget;
	TObjectPtr<UUserWidget> ControlsWidget;
	TObjectPtr<UUserWidget> PauseGameWidget;
};
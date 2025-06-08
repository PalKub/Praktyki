// Copyright 2025 Teyon. All Rights Reserved.


#include "Game/PraktykiMainMenuHUD.h"

#include "Blueprint/UserWidget.h"

void APraktykiMainMenuHUD::OpenRacingHUDWidget()
{
	if (MainMenuWidget) MainMenuWidget->RemoveFromParent();
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), RacingHUDClass);
	Widget->AddToViewport();
	RacingHUDWidget = Widget;
}

void APraktykiMainMenuHUD::OpenRaceSummaryWidget()
{
	if (RacingHUDWidget) RacingHUDWidget->RemoveFromParent();
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), RaceSummaryWidgetClass);
	Widget->AddToViewport();
	RaceSummaryWidget = Widget;
	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	GetOwningPlayerController()->SetInputMode(InputMode);
	GetOwningPlayerController()->bShowMouseCursor = true;
}

void APraktykiMainMenuHUD::OpenPauseGameWidget()
{
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), PauseGameWidgetClass);
	Widget->AddToViewport();
	RaceSummaryWidget = Widget;
	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	GetOwningPlayerController()->SetInputMode(InputMode);
	GetOwningPlayerController()->bShowMouseCursor = true;
}

void APraktykiMainMenuHUD::OpenMainMenuWidget()
{
	if (MainMenuWidgetClass)
	{
		if (RaceSummaryWidget) RaceSummaryWidget->RemoveFromParent();
		if (ControlsWidget) ControlsWidget->RemoveFromParent();
		if (RacingHUDWidget) RacingHUDWidget->RemoveFromParent();
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), MainMenuWidgetClass);
		Widget->AddToViewport();
		FInputModeUIOnly InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		GetOwningPlayerController()->SetInputMode(InputMode);
		GetOwningPlayerController()->bShowMouseCursor = true;
		MainMenuWidget = Widget;
	}
}

void APraktykiMainMenuHUD::OpenControlsWidget()
{
	if (ControlWidgetClass)
	{
		if (MainMenuWidget) MainMenuWidget->RemoveFromParent();
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), MainMenuWidgetClass);
		Widget->AddToViewport();
		FInputModeUIOnly InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		GetOwningPlayerController()->SetInputMode(InputMode);
		GetOwningPlayerController()->bShowMouseCursor = true;
		ControlsWidget = Widget;
	}
}

void APraktykiMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MainMenuWidgetClass)
	{
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), MainMenuWidgetClass);
		Widget->AddToViewport();
		FInputModeUIOnly InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		GetOwningPlayerController()->SetInputMode(InputMode);
		GetOwningPlayerController()->bShowMouseCursor = true;
		MainMenuWidget = Widget;
	}
}
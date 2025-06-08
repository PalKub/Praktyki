// Copyright 2025 Teyon. All Rights Reserved.


#include "Game/PraktykiMainMenuHUD.h"

#include "Blueprint/UserWidget.h"

void APraktykiMainMenuHUD::OpenRacingHUDWidget()
{
	if (RacingHUDClass)
	{
		CloseAllWidgets();
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), RacingHUDClass);
		Widget->AddToViewport();
		RacingHUDWidget = Widget;
		OpenWidgets.Add(Widget);
	}
}

void APraktykiMainMenuHUD::OpenRaceSummaryWidget()
{
	if (RaceSummaryWidgetClass)
	{
		CloseAllWidgets();
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), RaceSummaryWidgetClass);
		Widget->AddToViewport();
		RaceSummaryWidget = Widget;
		FInputModeUIOnly InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		GetOwningPlayerController()->SetInputMode(InputMode);
		GetOwningPlayerController()->bShowMouseCursor = true;
		OpenWidgets.Add(Widget);
	}
}

void APraktykiMainMenuHUD::OpenPauseGameWidget()
{
	if (PauseGameWidgetClass)
	{
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), PauseGameWidgetClass);
		Widget->AddToViewport();
		PauseGameWidget = Widget;
		FInputModeUIOnly InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		GetOwningPlayerController()->SetInputMode(InputMode);
		GetOwningPlayerController()->bShowMouseCursor = true;
		OpenWidgets.Add(Widget);
	}
}

void APraktykiMainMenuHUD::OpenMainMenuWidget()
{
	if (MainMenuWidgetClass)
	{
		CloseAllWidgets();
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), MainMenuWidgetClass);
		Widget->AddToViewport();
		FInputModeUIOnly InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		GetOwningPlayerController()->SetInputMode(InputMode);
		GetOwningPlayerController()->bShowMouseCursor = true;
		MainMenuWidget = Widget;
		OpenWidgets.Add(Widget);
	}
}

void APraktykiMainMenuHUD::OpenControlsWidget()
{
	if (ControlWidgetClass)
	{
		if (IsValid(MainMenuWidget)) MainMenuWidget->RemoveFromParent();
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), MainMenuWidgetClass);
		Widget->AddToViewport();
		FInputModeUIOnly InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		GetOwningPlayerController()->SetInputMode(InputMode);
		GetOwningPlayerController()->bShowMouseCursor = true;
		ControlsWidget = Widget;
		OpenWidgets.Add(Widget);
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

void APraktykiMainMenuHUD::CloseAllWidgets()
{
	for (UUserWidget* Widget : OpenWidgets)
	{
		if (IsValid(Widget)) Widget->RemoveFromParent();
	}
	OpenWidgets.Empty();
}

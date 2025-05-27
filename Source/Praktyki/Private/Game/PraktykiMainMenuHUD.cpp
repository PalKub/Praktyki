// Copyright 2025 Teyon. All Rights Reserved.


#include "Game/PraktykiMainMenuHUD.h"

#include "Blueprint/UserWidget.h"

void APraktykiMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MainMenuWidgetClass)
	{
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), MainMenuWidgetClass);
		Widget->AddToViewport();
		FInputModeUIOnly InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetWidgetToFocus(Widget->TakeWidget());
		GetOwningPlayerController()->SetInputMode(InputMode);
		GetOwningPlayerController()->bShowMouseCursor = true;
	}
}
// Copyright Me :)


#include "UI/HUD/AuraHUD.h"
#include "Blueprint/UserWidget.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
	}
	return OverlayWidgetController;
}

// Handles the setup for the HUD and the widget controller
void AAuraHUD::InitOverlay(APlayerController* PController, APlayerState* PState, UAbilitySystemComponent* ASC,
	UAttributeSet* AS)
{
	// Assert that crashes the game if these are not set, and gives an error message
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass uninitialized. Please fill out on BP_AuraHUD."));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass uninitialized. Please fill out on BP_AuraHUD."))

	// Creating the overlay widget itself
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(Widget);

	// Creating the widget controller
	const FWWidgetControllerParams WidgetControllerParams(PController, PState, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	// Tell the OverlayWidget about the controller
	OverlayWidget->SetWidgetController(WidgetController);
	
	Widget->AddToViewport();
}

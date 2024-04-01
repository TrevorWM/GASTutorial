// Copyright Me :)


#include "UI/Widget/AuraUserWidget.h"

// Use this to set the widget controller so that we can call the WidgetControllerSet event right after
// it is set in order to let things know the widget has a controller.
void UAuraUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}

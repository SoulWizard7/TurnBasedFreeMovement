
#include "NikOverlayWidget.h"

#include "NikEndTurnWidget.h"
#include "NikPlayerActionWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

void UNikOverlayWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ActionWidgets.SetNum(4);
}

void UNikOverlayWidget::AddActionButton(int ButtonIndex)
{
	static FName ButtonNames[] = {
		TEXT("Button0Slot"),
		TEXT("Button1Slot"),
		TEXT("Button2Slot"),
		TEXT("Button3Slot"),
	};	
	
	UNikPlayerActionWidget* ActionWidget = NewObject<UNikPlayerActionWidget>(this, PlayerActionWidgetClass);
	ActionWidget->ButtonIndex = ButtonIndex;
	ActionWidgets[ButtonIndex] = ActionWidget;
	
	SetContentForSlot(ButtonNames[ButtonIndex], ActionWidget);
}

void UNikOverlayWidget::AddEndTurnButton()
{
	static FName EndTurnName = TEXT("EndTurnSlot");
	
	UNikEndTurnWidget* Widget = NewObject<UNikEndTurnWidget>(this, EndTurnWidgetClass);
	EndTurnWidget = Widget;

	SetContentForSlot(EndTurnName, Widget);	
}

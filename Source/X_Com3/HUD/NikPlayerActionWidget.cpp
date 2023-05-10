
#include "NikPlayerActionWidget.h"
#include "Components/TextBlock.h"
#include "X_Com3/TurnManager/NikCombatManager.h"

void UNikPlayerActionWidget::SetButtonName(const FString& Name)
{
	GetNameTextBlock()->SetText(FText::FromString(Name));
}

void UNikPlayerActionWidget::ClickButton()
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.f, FColor::Green, TEXT("Clicked button"), true,
									 FVector2D(1.f));

	CombatManager->SetUnitState(ButtonIndex);
}


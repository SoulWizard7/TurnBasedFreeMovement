#include "NikEndTurnWidget.h"

#include "X_Com3/TurnManager/NikCombatManager.h"

void UNikEndTurnWidget::ClickButton()
{
	CombatManager->CombatPlayerTurn->EndTurn();
}

#include "NikCombatPlayerTurn.h"
#include "NikCombatManager.h"

void UNikCombatPlayerTurn::CombatPlayerTurn()
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.f, FColor::Blue, TEXT("Combat Player Turn Script DING"), true,
									 FVector2D(1.f));
}

void UNikCombatPlayerTurn::EndTurn()
{
	if(CombatManager->CombatState == StateOfCombat::PlayerTurn)
	{
		CombatManager->SetState(EnemyTurn);
	}
}


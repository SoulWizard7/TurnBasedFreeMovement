#include "NikCombatEnemyTurn.h"
#include "X_Com3/Units/NikEnemyUnit.h"
#include "NikCombatManager.h"

void UNikCombatEnemyTurn::CombatEnemyTurn()
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.f, FColor::Blue, TEXT("Combat Enemy Turn Script DING"), true,
									 FVector2D(1.f));
	// Add Enemy AI
	for (int i = 0; i < CombatManager->EnemyUnits.Num(); ++i)
	{
		ANikEnemyUnit* EnemyUnit = Cast<ANikEnemyUnit>(CombatManager->EnemyUnits[i]);
		EnemyUnit->RunBehaviourTree();
	}

	CombatManager->SetState(NewRound);
}

void UNikCombatEnemyTurn::EndEnemyTurn()
{
	
}

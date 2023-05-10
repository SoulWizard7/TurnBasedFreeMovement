
#pragma once
#include "NikCombatEnemyTurn.generated.h"

class ANikCombatManager;

UCLASS()
class UNikCombatEnemyTurn : public UActorComponent
{
	GENERATED_BODY()
public:
	void CombatEnemyTurn();
	void EndEnemyTurn();

	UPROPERTY()
	ANikCombatManager* CombatManager;

	
};

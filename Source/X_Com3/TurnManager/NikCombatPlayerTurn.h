#pragma once

#include "NikCombatPlayerTurn.generated.h"

class ANikCombatManager;
UCLASS()
class UNikCombatPlayerTurn : public UActorComponent
{
	GENERATED_BODY()
public:
	void CombatPlayerTurn();
	void EndTurn();

	UPROPERTY()
	ANikCombatManager* CombatManager;
	
};


#pragma once

#include "NikCombatNewRound.generated.h"

class ANikCombatManager;

UCLASS()
class UNikCombatNewRound : public UActorComponent
{
	GENERATED_BODY()
public:
	void CombatNewRound();

	UPROPERTY()
	ANikCombatManager* CombatManager;	
};

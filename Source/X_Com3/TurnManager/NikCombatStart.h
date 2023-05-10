#pragma once
#include "NikCombatStart.generated.h"

class ANikCombatManager;

UCLASS()
class UNikCombatStart : public UActorComponent
{
	GENERATED_BODY()
public:
	void CombatStart();
	void GetAllUnits();

	UPROPERTY()
	ANikCombatManager* CombatManager;
	
};

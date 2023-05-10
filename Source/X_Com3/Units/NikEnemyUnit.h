#pragma once

#include "NikUnit.h"
#include "NikEnemyUnit.generated.h"

class ANikUnit;

UCLASS()
class ANikEnemyUnit : public ANikUnit
{
	GENERATED_BODY()
public:
	ANikEnemyUnit();

	UFUNCTION(BlueprintImplementableEvent)
	void RunBehaviourTree();
	
};
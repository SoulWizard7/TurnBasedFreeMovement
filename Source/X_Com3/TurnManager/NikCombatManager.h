#pragma once
#include "NikCombatEnd.h"
#include "NikCombatEnemyTurn.h"
#include "NikCombatNewRound.h"
#include "NikCombatPlayerTurn.h"
#include "NikCombatStart.h"
#include "X_Com3/NikUnitController.h"
#include "NikCombatManager.generated.h"

class ANikPlayerUnit;
class ANikEnemyUnit;
class ANikUnitController;

UENUM()
enum StateOfCombat
{
	StartState,
	NewRound,
	PlayerTurn,
	EnemyTurn,
	EndCombat
};

UCLASS()
class ANikCombatManager : public AActor
{
	GENERATED_BODY()
public:
	ANikCombatManager();

	virtual void Tick(float DeltaSeconds) override;	
	
	void BeginPlay() override;
	void SpawnButtons();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	// **** COMBAT STATE MACHINE ****
	UPROPERTY(VisibleAnywhere)
	UNikCombatStart* CombatStart;

	UPROPERTY(VisibleAnywhere)
	UNikCombatNewRound* CombatNewRound;

	UPROPERTY(VisibleAnywhere)
	UNikCombatPlayerTurn* CombatPlayerTurn;

	UPROPERTY(VisibleAnywhere)
	UNikCombatEnemyTurn* CombatEnemyTurn;

	UPROPERTY(VisibleAnywhere)
	UNikCombatEnd* CombatEnd;
	
	StateOfCombat CombatState = StartState;
	void SetState(StateOfCombat state);

	// ******************************
	
	UPROPERTY(EditAnywhere, Category = UnitType)
	TSubclassOf<ANikEnemyUnit> Enemy;

	UPROPERTY(EditAnywhere, Category = UnitType)
	TSubclassOf<ANikPlayerUnit> Player;	

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TArray<AActor*> EnemyUnits;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TArray<AActor*> PlayerUnits;

	UPROPERTY()
	ANikUnitController* UnitController;

	void SetUnitState(int ButtonIndex);

};

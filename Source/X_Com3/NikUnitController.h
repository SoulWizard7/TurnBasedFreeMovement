#pragma once

#include "CoreMinimal.h"
#include "NikUnitController.generated.h"

class ANikUnitController;
class ANikNavLineManager;
class ANikUnit;
class ANikPlayerUnit;
class UNavigationPath;
class ANikCombatManager;

UENUM()
enum UnitState
{
	MoveState,
	Action0,
	Action1,
	Action2,
	Action3	
};

UCLASS()
class X_COM3_API ANikUnitController : public APlayerController
{
	GENERATED_BODY()

public:
	ANikUnitController();
	virtual void SetupInputComponent() override;

	void SpawnManagers();

	UPROPERTY(VisibleAnywhere)
	UNavigationPath* NavPath;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;	

	UPROPERTY(VisibleAnywhere)
	ANikPlayerUnit* SelectedPlayerUnit = nullptr;

	void LeftMouseButton();
	void RightMouseButton();
	void VisualizeAction();

	void OnSetDestinationReleased();
	FHitResult MousePosition();
	void SelectUnit();
	void DeSelectUnit();
	void SetNewMoveDestination(FVector DestLocation);
	void CreateNavMeshPath(FHitResult Hit);
	void DeactivateDecals();

	void SetActionButtonNames(FString a, FString b, FString c, FString d);
	
	UnitState State = UnitState::MoveState; 
	void SetUnitState(UnitState state);

	TArray<FVector> CreatePath(ANikUnit* selectedUnit);
	
	UPROPERTY()
	FVector capsuleOffset = FVector(0.f,0.f,44.f);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ANikNavLineManager> NavLineManagerClass;
	UPROPERTY(VisibleAnywhere)
	ANikNavLineManager* NavLineManager;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ANikCombatManager> CombatManagerClass;
	UPROPERTY(VisibleAnywhere)
	ANikCombatManager* CombatManager;
};



#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NikUnit.generated.h"

class ULineBatchComponent;
struct FBatchedLine;
class UNavigationPath;
class UDecalComponent;
class UCharacterMovementComponent;
class USceneComponent;
class ANavMeshBoundsVolume;
class ARecastNavMesh;

UCLASS()
class X_COM3_API ANikUnit : public ACharacter
{
	GENERATED_BODY()

public:
	ANikUnit();

protected:
	virtual void BeginPlay() override;

public:
	//virtual void Tick(float DeltaTime) override;

	void MovePawn();
	
	UPROPERTY(VisibleAnywhere)
	ULineBatchComponent* Line;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* DecalTransform;

	UPROPERTY(VisibleAnywhere)
	UDecalComponent* Decal;

	UPROPERTY()
	UCharacterMovementComponent* Movement;

	UPROPERTY(VisibleAnywhere)
	UNavigationPath* NavPath;

	UPROPERTY(VisibleAnywhere)
	ANavMeshBoundsVolume* NavMeshBounds;

	UPROPERTY(VisibleAnywhere)
	ARecastNavMesh* RecastNavMesh;

	UPROPERTY(VisibleAnywhere)
	bool isMoving = false;
	
	UPROPERTY(EditAnywhere, Category = UnitStats)
	float unitSpeed = 300.f;

	UPROPERTY(EditAnywhere, Category = UnitStats)
	float MaxMovement = 1000.f;

	UPROPERTY(EditAnywhere, Category = UnitStats)
	bool hasMovement = true;

	UPROPERTY(EditAnywhere, Category = UnitStats)
	bool hasAction = true;
	
};



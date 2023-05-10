#pragma once
#include "NikNavLineManager.generated.h"

class ANavDot;
class USceneComponent;
class UDecalComponent;
class UMaterial;

UCLASS()
class ANikNavLineManager : public AActor
{
	GENERATED_BODY()
public:

	ANikNavLineManager();
	void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	TArray<ANavDot*> Decals;
	
	UPROPERTY(VisibleAnywhere)
	AActor* CurrentUnit;

	UPROPERTY(EditAnywhere, Category = DotDecal)
	TSubclassOf<ANavDot> Decal;	
	
	void Print();
	
	void VisualizePathDotsV2(TArray<FVector> Path);
	
	void DeactivateDecals();
	
};

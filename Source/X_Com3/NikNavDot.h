#pragma once
#include "Components/DecalComponent.h"

#include "NikNavDot.generated.h"

class Material;
class UDecalComponent;

UCLASS()
class ANavDot : public AActor
{
	GENERATED_BODY()
public:
	ANavDot();

	UPROPERTY(EditAnywhere)
	UDecalComponent* Decal;

	UPROPERTY(EditAnywhere)
	UMaterial* DecalMaterial;

	UFUNCTION()
	void Activate() { Decal->SetVisibility(true); }
	
	UFUNCTION()
	void Deactivate() { Decal->SetVisibility(false); }
	
};

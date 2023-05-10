#include "NikNavDot.h"

#include "Components/DecalComponent.h"

ANavDot::ANavDot()
{
	Decal = CreateDefaultSubobject<UDecalComponent>(TEXT("Root"));
	RootComponent = Decal;
	Decal->SetDecalMaterial(DecalMaterial);
	Decal->DecalSize = FVector(250,10,10);
	Decal->SetWorldRotation(FRotator(90,0,0));
	Decal->SetVisibility(false);
}

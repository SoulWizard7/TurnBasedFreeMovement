#pragma once

#include "CoreMinimal.h"
#include "X_Com3PlayerController.h"

#include "X_Com3SetCharacter.generated.h"

class AX_Com3SetCharacter;

UCLASS()
class X_COM3_API AX_Com3SetCharacter : public AActor
{
	GENERATED_BODY()

public:
	AX_Com3SetCharacter();

private:

public:
	
	void SetupInput();
	void SelectUnit();

	
	
};










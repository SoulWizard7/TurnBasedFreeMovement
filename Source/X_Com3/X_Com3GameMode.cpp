// Copyright Epic Games, Inc. All Rights Reserved.

#include "X_Com3GameMode.h"
#include "X_Com3PlayerController.h"
#include "X_Com3Character.h"
#include "UObject/ConstructorHelpers.h"

AX_Com3GameMode::AX_Com3GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AX_Com3PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
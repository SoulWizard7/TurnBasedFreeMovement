#include "NikCombatNewRound.h"

#include "NikCombatManager.h"


void UNikCombatNewRound::CombatNewRound()
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.f, FColor::Blue, TEXT("Combat New Round Script DING"), true,
									 FVector2D(1.f));
	
	//Figure out who will go first.
	//Lets just do players first.
	
	CombatManager->SetState(PlayerTurn);
	
}

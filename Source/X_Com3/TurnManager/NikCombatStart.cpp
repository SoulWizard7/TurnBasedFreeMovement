#include "NikCombatStart.h"
#include "Kismet/GameplayStatics.h"
#include "NikCombatManager.h"
#include "X_Com3/Units/NikEnemyUnit.h"
#include "X_Com3/Units/NikPlayerUnit.h"


void UNikCombatStart::CombatStart()
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.f, FColor::Blue, TEXT("Combat Start Script DING"), true,
									 FVector2D(1.f));
	
	GetAllUnits();

	CombatManager->SetState(NewRound);
	//ACombatManager* wat = Cast<ACombatManager>(GetOwner());
	//wat->SetState(NewRound);
}

void UNikCombatStart::GetAllUnits()
{
	UGameplayStatics::GetAllActorsOfClass(this, CombatManager->Enemy, CombatManager->EnemyUnits);
	UGameplayStatics::GetAllActorsOfClass(this, CombatManager->Player,  CombatManager->PlayerUnits);	
}

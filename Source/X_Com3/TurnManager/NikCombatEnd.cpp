#include "NikCombatEnd.h"

void UNikCombatEnd::CombatEnd()
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.f, FColor::Blue, TEXT("Combat End Script DING"), true,
									 FVector2D(1.f));
}

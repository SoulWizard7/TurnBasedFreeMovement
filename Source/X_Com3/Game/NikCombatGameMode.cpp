#include "NikCombatGameMode.h"

#include "X_Com3/HUD/NikOverlayWidget.h"

ANikCombatGameMode::ANikCombatGameMode()
{
	DefaultPawnClass = nullptr;
}

ANikCombatGameMode* ANikCombatGameMode::Get(UObject* WorldContext)
{
	return WorldContext->GetWorld()->GetAuthGameMode<ANikCombatGameMode>();
}

void ANikCombatGameMode::StartMatch()
{
	OverlayWidget = NewObject<UNikOverlayWidget>(this, OverlayWidgetClass);
	OverlayWidget->AddToViewport();
	
	Super::StartMatch();
}

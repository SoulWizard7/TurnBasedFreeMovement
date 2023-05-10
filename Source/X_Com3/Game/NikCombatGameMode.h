#pragma once

#include "GameFramework/GameMode.h"
#include "NikCombatGameMode.generated.h"

class UNikOverlayWidget;

UCLASS()
class ANikCombatGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	ANikCombatGameMode();

	UFUNCTION(BlueprintPure, Category = "Nik|Game Mode", Meta = (DisplayName="GetCombatGameMode", WorldContext="WorldContext"))
	static ANikCombatGameMode* Get(UObject* WorldContext);

	void StartMatch() override;

	UPROPERTY(EditDefaultsOnly, Category = Widgets)
	TSubclassOf<UNikOverlayWidget> OverlayWidgetClass;

	UPROPERTY()
	UNikOverlayWidget* OverlayWidget;
	
};
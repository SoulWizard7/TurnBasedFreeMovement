#pragma once

#include "Blueprint/UserWidget.h"
#include "NikEndTurnWidget.generated.h"

class ANikCombatManager;

UCLASS()
class UNikEndTurnWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void ClickButton();

	UPROPERTY()
	ANikCombatManager* CombatManager;
};

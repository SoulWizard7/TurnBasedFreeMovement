#pragma once
#include "Blueprint/UserWidget.h"
#include "NikPlayerActionWidget.generated.h"

class UTextBlock;
class ANikCombatManager;

UCLASS()
class UNikPlayerActionWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
	UTextBlock* GetNameTextBlock();

	UFUNCTION(BlueprintImplementableEvent)
	UTextBlock* GetActionTextBlock();

	void SetButtonName(const FString& Name);

	UPROPERTY(VisibleAnywhere)
	int ButtonIndex = -1;

	UPROPERTY(VisibleAnywhere)
	ANikCombatManager* CombatManager;

	UFUNCTION(BlueprintCallable)
	void ClickButton();	
};
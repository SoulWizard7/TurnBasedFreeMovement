#pragma once

#include "Blueprint/UserWidget.h"
#include "NikOverlayWidget.generated.h"

class UCanvasPanel;
class UNikPlayerActionWidget;
class UNikEndTurnWidget;

UCLASS()
class UNikOverlayWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	void NativeConstruct() override;	
	void AddActionButton(int ButtonIndex);
	void AddEndTurnButton();
	
	UFUNCTION(BlueprintImplementableEvent)
	UCanvasPanel* GetMainCanvas();

	UPROPERTY(EditAnywhere, Category = GameOverlay)
	TSubclassOf<UNikPlayerActionWidget> PlayerActionWidgetClass;

	UPROPERTY()
	TArray<UNikPlayerActionWidget*> ActionWidgets;

	UPROPERTY(EditAnywhere, Category = GameOverlay)
	TSubclassOf<UNikEndTurnWidget> EndTurnWidgetClass;

	UNikEndTurnWidget* EndTurnWidget;

};

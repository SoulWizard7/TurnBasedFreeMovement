#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "NikEnemyAIController.generated.h"

UCLASS(Blueprintable)
class X_COM3_API ANikEnemyAIController : public AAIController
{
	GENERATED_BODY()
public:
	ANikEnemyAIController();

	UFUNCTION()
	void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	UPROPERTY(EditDefaultsOnly)
	UAIPerceptionComponent* PerceptionComp = nullptr;

protected:
	virtual void BeginPlay() override;

private:
	
};

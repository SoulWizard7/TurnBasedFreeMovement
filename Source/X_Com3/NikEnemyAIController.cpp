#include "NikEnemyAIController.h"
#include "Perception/AIPerceptionComponent.h"

ANikEnemyAIController::ANikEnemyAIController()
{
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
	PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &ANikEnemyAIController::OnPerceptionUpdated);
}

void ANikEnemyAIController::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("Stimuli Update"));
}

void ANikEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
}

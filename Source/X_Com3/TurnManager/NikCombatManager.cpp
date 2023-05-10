#include "NikCombatManager.h"
#include "Kismet/GameplayStatics.h"
#include "X_Com3/Game/NikCombatGameMode.h"
#include "X_Com3/HUD/NikEndTurnWidget.h"
#include "X_Com3/HUD/NikOverlayWidget.h"
#include "X_Com3/HUD/NikPlayerActionWidget.h"
#include "X_Com3/Units/NikEnemyUnit.h"
#include "X_Com3/Units/NikPlayerUnit.h"

ANikCombatManager::ANikCombatManager()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	CombatStart = CreateDefaultSubobject<UNikCombatStart>(TEXT("Combat Start"));
	CombatNewRound = CreateDefaultSubobject<UNikCombatNewRound>(TEXT("Combat NewRound"));
	CombatPlayerTurn = CreateDefaultSubobject<UNikCombatPlayerTurn>(TEXT("Combat Player Turn"));
	CombatEnemyTurn = CreateDefaultSubobject<UNikCombatEnemyTurn>(TEXT("Combat Enemy Turn"));
	CombatEnd = CreateDefaultSubobject<UNikCombatEnd>(TEXT("Combat End"));	
}

void ANikCombatManager::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FString msg = UEnum::GetValueAsString(CombatState);
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.f, FColor::Green, TEXT("Current combat state = ") + msg, true,
									 FVector2D(1.f));

	switch (CombatState)
	{
	case StateOfCombat::StartState:
		CombatStart->CombatStart();
		break;
	case StateOfCombat::NewRound:
		CombatNewRound->CombatNewRound();
		break;
	case StateOfCombat::PlayerTurn:
		CombatPlayerTurn->CombatPlayerTurn();
		break;
	case StateOfCombat::EnemyTurn:
		CombatEnemyTurn->CombatEnemyTurn();
		break;
	case StateOfCombat::EndCombat:
		CombatEnd->CombatEnd();
		break;
	}
}

void ANikCombatManager::BeginPlay()
{
	Super::BeginPlay();
	SpawnButtons();

	CombatStart->CombatManager = this;
	CombatNewRound->CombatManager = this;
	CombatPlayerTurn->CombatManager = this;
	CombatEnemyTurn->CombatManager = this;
}

void ANikCombatManager::SpawnButtons()
{
	ANikCombatGameMode* GameMode = ANikCombatGameMode::Get(this);
	GameMode->OverlayWidget->AddActionButton(0);
	GameMode->OverlayWidget->AddActionButton(1);
	GameMode->OverlayWidget->AddActionButton(2);
	GameMode->OverlayWidget->AddActionButton(3);

	GameMode->OverlayWidget->ActionWidgets[0]->SetButtonName(FString::Printf(TEXT("test 1")));
	GameMode->OverlayWidget->ActionWidgets[1]->SetButtonName(FString::Printf(TEXT("test 2")));
	GameMode->OverlayWidget->ActionWidgets[2]->SetButtonName(FString::Printf(TEXT("test 3")));
	GameMode->OverlayWidget->ActionWidgets[3]->SetButtonName(FString::Printf(TEXT("test 4")));

	for (int i = 0; i < GameMode->OverlayWidget->ActionWidgets.Num(); ++i)
	{
		GameMode->OverlayWidget->ActionWidgets[i]->CombatManager = this;
	}

	GameMode->OverlayWidget->AddEndTurnButton();
	GameMode->OverlayWidget->EndTurnWidget->CombatManager = this;
}

void ANikCombatManager::SetState(StateOfCombat state)
{
	CombatState = state;
}

void ANikCombatManager::SetUnitState(int ButtonIndex)
{
	if (ButtonIndex == 0)
	{
		if (UnitController->State != UnitState::Action0)
		{
			UnitController->State = UnitState::Action0;
			UnitController->DeactivateDecals();	
		}			
		else
			UnitController->State = UnitState::MoveState;
	}
	if (ButtonIndex == 1)
	{
		if (UnitController->State != UnitState::Action1)
		{
			UnitController->State = UnitState::Action1;
			UnitController->DeactivateDecals();	
		}			
		else
			UnitController->State = UnitState::MoveState;
	}
	if (ButtonIndex == 2)
	{
		if (UnitController->State != UnitState::Action2)
		{
			UnitController->State = UnitState::Action2;
			UnitController->DeactivateDecals();	
		}			
		else
			UnitController->State = UnitState::MoveState;
	}
	if (ButtonIndex == 3)
	{
		if (UnitController->State != UnitState::Action3)
		{
			UnitController->State = UnitState::Action3;
			UnitController->DeactivateDecals();	
		}			
		else
			UnitController->State = UnitState::MoveState;
	}
	
	
}



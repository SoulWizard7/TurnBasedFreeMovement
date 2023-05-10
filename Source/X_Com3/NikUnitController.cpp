#include "NikUnitController.h"
#include "GameFramework/Pawn.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "NavMesh/NavMeshPath.h"
#include "GameFramework/PlayerController.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "NikNavLineManager.h"
#include "Kismet/GameplayStatics.h"
#include "Units/NikPlayerUnit.h"
#include "Units/NikUnit.h"
#include "TurnManager/NikCombatManager.h"
#include "Game/NikCombatGameMode.h"
#include "HUD/NikOverlayWidget.h"
#include "HUD/NikPlayerActionWidget.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"

ANikUnitController::ANikUnitController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;

	NavPath = CreateDefaultSubobject<UNavigationPath>(TEXT("Navigation Path"));
}

void ANikUnitController::SetupInputComponent()
{
	Super::SetupInputComponent();	
	InputComponent->BindAction("LeftMouseButton", IE_Released, this, &ANikUnitController::LeftMouseButton);
	InputComponent->BindAction("RightMouseButton", IE_Released, this, &ANikUnitController::RightMouseButton);
	FString msg = "INPUT COMPONENTS SET! ! ! ! ";	
	UE_LOG(LogTemp, Log, TEXT("Hit%s"), *msg);	
}

void ANikUnitController::SpawnManagers()
{
	FTransform spawn = FTransform::Identity;
	ANikNavLineManager* n = GetWorld()->SpawnActor<ANikNavLineManager>(NavLineManagerClass, spawn);
	NavLineManager = n;
	NavLineManager->Print();

	ANikCombatManager* c = GetWorld()->SpawnActor<ANikCombatManager>(CombatManagerClass, spawn);
	c->UnitController = this;
	CombatManager = c;
	
}

void ANikUnitController::BeginPlay()
{
	Super::BeginPlay();
	SpawnManagers();
}

void ANikUnitController::Tick(float DeltaSeconds)
{
	FString msg = UEnum::GetValueAsString(State);
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.f, FColor::Green, TEXT("Units Current state: ") + msg, true,
									 FVector2D(1.f));
	
	if (SelectedPlayerUnit != nullptr)
	{
		VisualizeAction();		
	}
}

void ANikUnitController::LeftMouseButton()
{
	if(State == UnitState::MoveState)
	{
		if(SelectedPlayerUnit != nullptr) OnSetDestinationReleased();
	}	
}

void ANikUnitController::RightMouseButton()
{
	SelectUnit();
}

void ANikUnitController::VisualizeAction()
{
	switch (State)
	{
	case UnitState::MoveState:
		if(!SelectedPlayerUnit->HasPath)
		{
			CreateNavMeshPath(MousePosition());			
		}
		
		break;

	case UnitState::Action0:
		break;

	case UnitState::Action1:
		break;

	case UnitState::Action2:
		break;

	case UnitState::Action3:
		break;
			
	}
}

void ANikUnitController::DeactivateDecals()
{
	NavLineManager->DeactivateDecals();
}

void ANikUnitController::SetUnitState(UnitState state)
{
	State = state;
}
void ANikUnitController::CreateNavMeshPath(FHitResult Hit)
{
	
	AController* con = SelectedPlayerUnit->GetController();

	const FVector AgentNavLocation = con->GetNavAgentLocation();
	UNavigationSystemV1* NavSys = con ? FNavigationSystem::GetCurrent<UNavigationSystemV1>(con->GetWorld()) : nullptr;

	//

	FNavLocation Out;
	if (!NavSys->ProjectPointToNavigation(Hit.ImpactPoint, Out))
		return;
	
	const ANavigationData* NavData = NavSys->GetNavDataForProps(con->GetNavAgentPropertiesRef(), AgentNavLocation);
	FPathFindingQuery Query(con, *NavData, AgentNavLocation, Hit.ImpactPoint);
	FPathFindingResult Result = NavSys->FindPathSync(Query);
	FNavPathSharedPtr& p = Result.Path;

	//

	//NavSys->FindPathToLocationSynchronously()
	//UAIBlueprintHelperLibrary::CreateMoveToProxyObject()
	

	NavPath->SetPath(p);
	NavLineManager->VisualizePathDotsV2(CreatePath(SelectedPlayerUnit));	
}

TArray<FVector> ANikUnitController::CreatePath(ANikUnit* selectedUnit)
{
	TArray<FVector> VectorPath;	
	if (NavPath->PathPoints.Num() < 1) return VectorPath;
		
	for(FVector v : NavPath->PathPoints )
	{
		VectorPath.Add(v);
	}

	FHitResult Hit;
	TArray<AActor*> Actors;
	Actors.Add(selectedUnit);

	if (VectorPath.Num() >= 3)
	{
		for (int i = 0; i < VectorPath.Num() - 2; ++i)
		{
			if (VectorPath.Num() < 3)
			{
				break;
			}

			//Slopes dont work properly so right now this will skip slopes;
			//if(VectorPath[i].Z != VectorPath[i+1].Z) continue;

			//This code tries to remove wierd and unnecessary path-points that AStar creates ** Works porly with holes in ground and slopes, needs collider to do stuff correctly			
			if (UKismetSystemLibrary::BoxTraceSingle(this, VectorPath[i] + FVector::UpVector * 60, VectorPath[i+2] + FVector::UpVector * 60, FVector(34,34, 50), FRotator(0,0,0), ETraceTypeQuery::TraceTypeQuery1, false, Actors, EDrawDebugTrace::None, Hit, true, FLinearColor::Green, FLinearColor::Red, 0.0f ))
			{			
				GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.f, FColor::Green, Hit.Actor->GetName(), true, FVector2D(1.f));			
			}
			else
			{
				VectorPath.RemoveAt(i+1);
				if (VectorPath.Num() > 2)
				{
					i--;
				}
				else break;
			}
		}	
	}

	float pathDist = 0.f;

	//This code limits the distance of the path according to the max movement length of the selected unit
	for (int i = 0; i < VectorPath.Num() - 1; ++i)
	{		
		float temp = FVector::Distance(VectorPath[i], VectorPath[i+1]);
		pathDist += temp;
		if(pathDist > selectedUnit->MaxMovement)
		{
			pathDist -= temp;
			pathDist = selectedUnit->MaxMovement - pathDist;

			FVector Direction = VectorPath[i+1] - VectorPath[i];			
			Direction.Normalize();			

			FVector NewEndPathPoint = VectorPath[i] + Direction * pathDist;

			VectorPath[i+1] = NewEndPathPoint;

			for (int j = i+2; j < VectorPath.Num(); ++i)
			{
				VectorPath.RemoveAt(j);				
			}
			break;
		}		
	}	
	return VectorPath;
}

void ANikUnitController::SetActionButtonNames(FString a, FString b, FString c, FString d)
{
	ANikCombatGameMode* GameMode = ANikCombatGameMode::Get(this);

	GameMode->OverlayWidget->ActionWidgets[0]->SetButtonName(a);
	GameMode->OverlayWidget->ActionWidgets[1]->SetButtonName(b);
	GameMode->OverlayWidget->ActionWidgets[2]->SetButtonName(c);
	GameMode->OverlayWidget->ActionWidgets[3]->SetButtonName(d);
}

void ANikUnitController::OnSetDestinationReleased()
{
	if (SelectedPlayerUnit != nullptr)
	{
		// Trace to see what is under the mouse cursor
		//FHitResult Hit;
		//GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (MousePosition().bBlockingHit)
		{
			// We hit something, move there

			FString msg = "MOUSE LEFT CLICK";	
			UE_LOG(LogTemp, Log, TEXT("Hit %s"), *msg);

			//TODO SEND PATH TO NEWMOVEDESTINATION
			SetNewMoveDestination(MousePosition().ImpactPoint);
		}
	}
}

FHitResult ANikUnitController::MousePosition()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	return Hit;
}

void ANikUnitController::SelectUnit()
{
	if(SelectedPlayerUnit != nullptr)
	{
		DeSelectUnit();
	}
	
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, true, Hit);	

	if (Hit.bBlockingHit)
	{
		FString msg = "MOUSE RIGHT CLICK";	
		UE_LOG(LogTemp, Log, TEXT("Hit %s"), *msg);

		FString msg1 = Hit.GetActor()->GetName();	
		UE_LOG(LogTemp, Log, TEXT("Hit %s"), *msg1);
		
		if(Hit.GetActor()->IsA<ANikPlayerUnit>())
		{
			SelectedPlayerUnit = Cast<ANikPlayerUnit>(Hit.GetActor());
			SelectedPlayerUnit->SetCanAffectNavigationGeneration(false);
			NavLineManager->CurrentUnit = Hit.GetActor();

			SetActionButtonNames("1","2","3","4");

			//** Updates the NavmeshObsticle for units **
			//** REMEMBER RECAST NAVIGATION DEFAULTS NEEDS DYNAMIC RUNTIME GENERATION TO WORK **
			UNavigationSystemV1* navigation_system = UNavigationSystemV1::GetCurrent(GetWorld());
			if (navigation_system) navigation_system->Build();
		}		
	}
}

void ANikUnitController::DeSelectUnit()
{
	SelectedPlayerUnit->SetCanAffectNavigationGeneration(true);
	SelectedPlayerUnit = nullptr;
	State = MoveState;
	DeactivateDecals();
	SetActionButtonNames("","","","");
}

void ANikUnitController::SetNewMoveDestination(FVector DestLocation)
{	
	if (SelectedPlayerUnit)
	{
		if (SelectedPlayerUnit->HasPath) return;
		
		float const Distance = FVector::Dist(DestLocation, SelectedPlayerUnit->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{				
			SelectedPlayerUnit->Path = CreatePath(SelectedPlayerUnit);
			SelectedPlayerUnit->HasPath = true;
			NavLineManager->DeactivateDecals();
		}
	}
}

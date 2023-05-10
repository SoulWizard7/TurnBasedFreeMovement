
#include "NikUnit.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/LineBatchComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NavigationPath.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"

ANikUnit::ANikUnit()
{	
	PrimaryActorTick.bCanEverTick = true;
	
	Decal = CreateDefaultSubobject<UDecalComponent>(TEXT("Ground Decal"));
	Decal->SetupAttachment(RootComponent);

	Line = CreateDefaultSubobject<ULineBatchComponent>(TEXT("Line"));
	NavPath = CreateDefaultSubobject<UNavigationPath>(TEXT("Navigation Path"));
	SetCanAffectNavigationGeneration(true);
}

void ANikUnit::BeginPlay()
{
	Super::BeginPlay();
	
	Movement = GetCharacterMovement();
}
/*
void AUnit::Tick(float DeltaTime)
{
	AController* con = GetController();
	if(con->IsFollowingAPath())
	{
		isMoving = true;
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.f, FColor::Green, TEXT("unit is moving"), true, FVector2D(1.f));
	}
	else isMoving = false;
}*/

void ANikUnit::MovePawn()
{
	AController* con = GetController();
	//UAIBlueprintHelperLibrary::SimpleMoveToLocation(con, NewPos);

	FString msg = "MovePawn1";	
	UE_LOG(LogTemp, Log, TEXT("Hit %s"), *msg);
}


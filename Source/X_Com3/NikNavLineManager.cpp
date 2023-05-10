#include "NikNavLineManager.h"
#include "Components/DecalComponent.h"
#include "NikNavDot.h"

ANikNavLineManager::ANikNavLineManager()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Decals.Shrink();
}

void ANikNavLineManager::BeginPlay()
{
	Super::BeginPlay();	

	for (int i = 0; i < 80; ++i)
	{
		//FActorSpawnParameters Parameters = FActorSpawnParameters(NULL, NULL, this, NULL, NULL);
		auto dot = GetWorld()->SpawnActor(Decal, &GetActorTransform());
		Decals.Add(Cast<ANavDot>(dot));
	}	
}

void ANikNavLineManager::Print()
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.f, FColor::Green, TEXT("Print from navLineManager"), true,
	                                 FVector2D(1.f));
}

void ANikNavLineManager::VisualizePathDotsV2(TArray<FVector> Path)
{			
	TArray<FVector> VectorPath = Path;
	
	float distBetweenDots = 30.f;	
	TArray<FVector> dotPos;

	for (int i = 1; i < VectorPath.Num(); ++i)
	{
		FVector start = FVector(VectorPath[i - 1].X, VectorPath[i - 1].Y, VectorPath[i - 1].Z);
		FVector dest = FVector(VectorPath[i].X, VectorPath[i].Y, VectorPath[i].Z);

		FVector direction = dest - start;
		direction.Normalize();

		float length = FVector::Distance(start, dest);
		float tempLength = length;
		int points = 0;

		while (tempLength > distBetweenDots)
		{
			tempLength -= distBetweenDots;
			points++;
		}

		for (int j = 0; j < points; ++j)
		{
			FVector tempPos = start;
			FVector tempDir = direction;
			float temp = j * distBetweenDots;
			float tempLength1 = length - temp;
			tempDir *= tempLength1;
			tempPos += tempDir;
			dotPos.Add(tempPos);
		}		
	}

	FString msg = FString::Printf (TEXT("current dot nr: %i"), dotPos.Num());  	
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.f, FColor::Green, msg, true, FVector2D(1.f));

	while (Decals.Num() < dotPos.Num())
	{
		auto dot = GetWorld()->SpawnActor(Decal, &GetActorTransform());
		Decals.Add(Cast<ANavDot>(dot));
	}

	for (int i = 0; i < Decals.Num(); ++i)
	{
		if (i < dotPos.Num())
		{
			Decals[i]->Decal->SetVisibility(true);
			Decals[i]->SetActorLocation(dotPos[i]);			
		}
		else
		{
			Decals[i]->Decal->SetVisibility(false);
		}
	}	
}

void ANikNavLineManager::DeactivateDecals()
{
	for (int i = 0; i < Decals.Num(); ++i)
	{
		Decals[i]->Deactivate();
	}
}

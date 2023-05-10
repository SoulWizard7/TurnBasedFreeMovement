#include "NikPlayerUnit.h"

ANikPlayerUnit::ANikPlayerUnit()
{
	
}

void ANikPlayerUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FString msg = FString::Printf (TEXT("current path points: %i"), Path.Num());  	
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.f, FColor::Green, msg, true, FVector2D(1.f));

	if (HasPath)
	{
		MovePlayerUnit(DeltaTime);
	}	
}

void ANikPlayerUnit::MovePlayerUnit(float DeltaTime)
{
	if(Path.Num() == 0) return;	

	CurDirection = Path[CurPathPoint] - GetActorLocation();
	CurDirection.Normalize();

	AddMovementInput(CurDirection * unitSpeed * DeltaTime);

	float dist = FVector::Distance(GetActorLocation(), Path[CurPathPoint]);
	if (dist < 100.f)
	{
		if (CurPathPoint == Path.Num() - 1)
		{
			HasPath = false;
			Path.Empty();
			CurPathPoint = 1;
		}
		else
		{			
			CurPathPoint++;
		}		
	}	
}


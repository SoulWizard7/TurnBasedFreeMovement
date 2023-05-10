#pragma once

#include "NikUnit.h"
#include "NikPlayerUnit.generated.h"

class ANikUnit;


UCLASS()
class ANikPlayerUnit : public ANikUnit
{
	GENERATED_BODY()
public:
	ANikPlayerUnit();
	
	virtual void Tick(float DeltaTime) override;

	bool HasPath = false;
	void MovePlayerUnit(float DeltaTime);

	UPROPERTY()
	FVector CurDirection = FVector::ZeroVector;
	UPROPERTY()
	int CurPathPoint = 1;

	UPROPERTY(VisibleAnywhere)
	TArray<FVector> Path;

	UFUNCTION(BlueprintImplementableEvent)
	void Action0();

	UFUNCTION(BlueprintImplementableEvent)
	void Action1();

	UFUNCTION(BlueprintImplementableEvent)
	void Action2();

	UFUNCTION(BlueprintImplementableEvent)
	void Action3();

	
	
};

#include "UEnvQueryTest_FullCover.h"

#include "CollisionQueryParams.h"
#include "WorldCollision.h"
#include "Engine/World.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_VectorBase.h"
#include "EnvironmentQuery/Contexts/EnvQueryContext_Querier.h"

#define LOCTEXT_NAMESPACE "EnvQueryGenerator"

UEnvQueryTest_FullCover::UEnvQueryTest_FullCover(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Cost = EEnvTestCost::High;
	ValidItemType = UEnvQueryItemType_VectorBase::StaticClass();
	SetWorkOnFloatValues(false);
	
	Context = UEnvQueryContext_Querier::StaticClass();
	TraceData.SetGeometryOnly();
}

void UEnvQueryTest_FullCover::RunTest(FEnvQueryInstance& QueryInstance) const
{
	UObject* DataOwner = QueryInstance.Owner.Get();
	BoolValue.BindData(DataOwner, QueryInstance.QueryID);
	TraceFromContext.BindData(DataOwner, QueryInstance.QueryID);
	ItemHeightOffset.BindData(DataOwner, QueryInstance.QueryID);
	ContextHeightOffset.BindData(DataOwner, QueryInstance.QueryID);

	bool bWantsHit = BoolValue.GetValue();
	bool bTraceToItem = TraceFromContext.GetValue();
	float ItemZ = ItemHeightOffset.GetValue();
	float ContextZ = ContextHeightOffset.GetValue();

	FCollisionQueryParams OverlapParams(SCENE_QUERY_STAT(EnvQueryOverlap), OverlapData.bOverlapComplex);
	
	const ECollisionChannel OverlapCollisionChannel = OverlapData.OverlapChannel;
	const FVector TraceExtentOverlap(OverlapData.ExtentX, OverlapData.ExtentY, OverlapData.ExtentZ);

	FCollisionShape CollisionShape;
	switch (OverlapData.OverlapShape)
	{
	case EEnvOverlapShape::Box:
		CollisionShape = FCollisionShape::MakeBox(TraceExtentOverlap);
		break;

	case EEnvOverlapShape::Sphere:
		CollisionShape = FCollisionShape::MakeSphere(TraceExtentOverlap.X);
		break;

	case EEnvOverlapShape::Capsule:
		CollisionShape = FCollisionShape::MakeCapsule(TraceExtentOverlap.X, TraceExtentOverlap.Z);
		break;

	default:
		return;
	}

	typedef bool(UEnvQueryTest_FullCover::*FRunOverlapSignature)(const FVector&, const FCollisionShape&, const TArray<AActor*>&, UWorld*, enum ECollisionChannel, const FCollisionQueryParams&) const;
	FRunOverlapSignature OverlapFunc = (OverlapData.bOnlyBlockingHits ? (FRunOverlapSignature)&UEnvQueryTest_FullCover::RunOverlapBlocking : (FRunOverlapSignature)&UEnvQueryTest_FullCover::RunOverlap);

	TArray<AActor*> IgnoredActorsOverlap;
	if (OverlapData.bSkipOverlapQuerier)
	{
		QueryInstance.PrepareContext(UEnvQueryContext_Querier::StaticClass(), IgnoredActorsOverlap);
	}	

	TArray<FVector> ContextLocations;
	if (!QueryInstance.PrepareContext(Context, ContextLocations))
	{
		return;
	}

	FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(EnvQueryTrace), TraceData.bTraceComplex);

	TArray<AActor*> IgnoredActors;
	if (QueryInstance.PrepareContext(Context, IgnoredActors))
	{
		TraceParams.AddIgnoredActors(IgnoredActors);
	}
	
	ECollisionChannel TraceCollisionChannel = UEngineTypes::ConvertToCollisionChannel(TraceData.TraceChannel);	
	FVector TraceExtent(TraceData.ExtentX, TraceData.ExtentY, TraceData.ExtentZ);
	FRunTraceSignature TraceFunc;
	
	switch (TraceData.TraceShape)
	{
	case EEnvTraceShape::Box:
		TraceFunc.BindUObject(const_cast<UEnvQueryTest_FullCover*>(this), bTraceToItem ? &UEnvQueryTest_FullCover::RunBoxTraceTo : &UEnvQueryTest_FullCover::RunBoxTraceFrom);
		break;

	default:
		return;
	}

	for (int32 ContextIndex = 0; ContextIndex < ContextLocations.Num(); ContextIndex++)
	{
		ContextLocations[ContextIndex].Z += ContextZ;
	}

	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		const FVector ItemLocation = GetItemLocation(QueryInstance, It.GetIndex()) + FVector(0, 0, ItemZ);
		AActor* ItemActor = GetItemActor(QueryInstance, It.GetIndex());

		IgnoredActors.Push(ItemActor);

		const bool OverlapHit = (this->*OverlapFunc)(ItemLocation + OverlapData.ShapeOffset, CollisionShape, IgnoredActors, QueryInstance.World, OverlapCollisionChannel, OverlapParams);

		if(OverlapHit) //is next to a full cover object
		{
			//GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.f, FColor::Blue, TEXT("OverLap Hit FullCover"), true,FVector2D(1.f));

			int32 InCoverFromPlayers = 0;
			
			for (int32 ContextIndex = 0; ContextIndex < ContextLocations.Num(); ContextIndex++)
			{
				if(TraceFunc.Execute(ItemLocation, ContextLocations[ContextIndex], ItemActor, QueryInstance.World, TraceCollisionChannel, TraceParams, TraceExtent))
				{
					InCoverFromPlayers++;
				}
				else
				{
					It.SetScore(TestPurpose, FilterType, false, bWantsHit);					
				}
			}

			if (InCoverFromPlayers == ContextLocations.Num()) //is behind cover
			{
				for (int32 ContextIndex = 0; ContextIndex < ContextLocations.Num(); ContextIndex++)
				{
					FVector direction = (ContextLocations[ContextIndex] - ItemLocation);
					direction = FVector::CrossProduct(direction, FVector::UpVector);
					direction.Normalize();

					const bool Left = TraceFunc.Execute(ItemLocation + direction * CornerTraceCheckDistance, ContextLocations[ContextIndex], ItemActor, QueryInstance.World, TraceCollisionChannel, TraceParams, TraceExtent);
					const bool Right = TraceFunc.Execute(ItemLocation - direction * CornerTraceCheckDistance, ContextLocations[ContextIndex], ItemActor, QueryInstance.World, TraceCollisionChannel, TraceParams, TraceExtent);

					if (!Left || !Right) // can shoot around corner
					{
						It.SetScore(TestPurpose, FilterType, true, bWantsHit);
						It.ForceItemState(EEnvItemStatus::Passed, 1);
					}					
				}
			}			
		}
		else
		{
			It.SetScore(TestPurpose, FilterType, false, bWantsHit);					
		}
		
		IgnoredActors.Pop(/*bAllowShrinking=*/false);		
	}	
}

void UEnvQueryTest_FullCover::PostLoad()
{
	Super::PostLoad();
	TraceData.OnPostLoad();
}

bool UEnvQueryTest_FullCover::RunBoxTraceTo(const FVector& ItemPos, const FVector& ContextPos, AActor* ItemActor, UWorld* World, enum ECollisionChannel Channel, const FCollisionQueryParams& Params, const FVector& Extent)
{
	FCollisionQueryParams TraceParams(Params);
	TraceParams.AddIgnoredActor(ItemActor);

	const bool bHit = World->SweepTestByChannel(ContextPos, ItemPos, FQuat((ItemPos - ContextPos).Rotation()), Channel, FCollisionShape::MakeBox(Extent), TraceParams);
	return bHit;
}

bool UEnvQueryTest_FullCover::RunBoxTraceFrom(const FVector& ItemPos, const FVector& ContextPos, AActor* ItemActor, UWorld* World, enum ECollisionChannel Channel, const FCollisionQueryParams& Params, const FVector& Extent)
{
	FCollisionQueryParams TraceParams(Params);
	TraceParams.AddIgnoredActor(ItemActor);

	const bool bHit = World->SweepTestByChannel(ItemPos, ContextPos, FQuat((ContextPos - ItemPos).Rotation()), Channel, FCollisionShape::MakeBox(Extent), TraceParams);
	return bHit;
}

bool UEnvQueryTest_FullCover::RunOverlap(const FVector& ItemPos, const FCollisionShape& CollisionShape, const TArray<AActor*>& IgnoredActors, UWorld* World, enum ECollisionChannel Channel, const FCollisionQueryParams& Params) const
{
	FCollisionQueryParams OverlapParams(Params);
	OverlapParams.AddIgnoredActors(IgnoredActors);

	const bool bHit = World->OverlapAnyTestByChannel(ItemPos, FQuat::Identity, Channel, CollisionShape, OverlapParams);
	return bHit;
}

bool UEnvQueryTest_FullCover::RunOverlapBlocking(const FVector& ItemPos, const FCollisionShape& CollisionShape, const TArray<AActor*>& IgnoredActors, UWorld* World, enum ECollisionChannel Channel, const FCollisionQueryParams& Params) const
{
	FCollisionQueryParams OverlapParams(Params);
	OverlapParams.AddIgnoredActors(IgnoredActors);

	const bool bHit = World->OverlapBlockingTestByChannel(ItemPos, FQuat::Identity, Channel, CollisionShape, OverlapParams);
	return bHit;
}


FText UEnvQueryTest_FullCover::GetDescriptionTitle() const
{
	UEnum* ChannelEnum = StaticEnum<ETraceTypeQuery>();
	FString ChannelDesc = ChannelEnum->GetDisplayNameTextByValue(TraceData.TraceChannel).ToString();

	FString DirectionDesc = TraceFromContext.IsDynamic() ?
		FString::Printf(TEXT("%s, direction: %s"), *UEnvQueryTypes::DescribeContext(Context).ToString(), *TraceFromContext.ToString()) :
		FString::Printf(TEXT("%s %s"), TraceFromContext.DefaultValue ? TEXT("from") : TEXT("to"), *UEnvQueryTypes::DescribeContext(Context).ToString());

	return FText::FromString(FString::Printf(TEXT("%s: %s on %s"), 
		*Super::GetDescriptionTitle().ToString(), *DirectionDesc, *ChannelDesc));
}

FText UEnvQueryTest_FullCover::GetDescriptionDetails() const
{
	return FText::Format(FText::FromString("{0}\n{1}"),
		TraceData.ToText(FEnvTraceData::Detailed), DescribeBoolTestParams("hit"));
}
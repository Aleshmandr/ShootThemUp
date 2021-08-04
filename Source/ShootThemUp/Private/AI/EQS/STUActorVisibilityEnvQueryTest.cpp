// Shoot Them Up Game. All Rights Reserved.


#include "AI/EQS/STUActorVisibilityEnvQueryTest.h"

#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"

USTUActorVisibilityEnvQueryTest::USTUActorVisibilityEnvQueryTest(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	Cost = EEnvTestCost::Low;
	SetWorkOnFloatValues(false);

	// To search for GameplayTags, currently we require the item type to be an actor.  Certainly it must at least be a
	// class of some sort to be able to find the interface required.
	ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
}

void USTUActorVisibilityEnvQueryTest::RunTest(FEnvQueryInstance& QueryInstance) const
{
	UObject* QueryOwner = QueryInstance.Owner.Get();
	if (QueryOwner == nullptr)
	{
		return;
	}

	BoolValue.BindData(QueryOwner, QueryInstance.QueryID);
	const bool bWantsValid = BoolValue.GetValue();

	// loop through all items
	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		AActor* ItemActor = GetItemActor(QueryInstance, It.GetIndex());
		const bool bSatisfiesTest = ItemActor != nullptr && ItemActor->GetRootComponent()->IsVisible();

		It.SetScore(TestPurpose, FilterType, bSatisfiesTest, bWantsValid);
	}
}

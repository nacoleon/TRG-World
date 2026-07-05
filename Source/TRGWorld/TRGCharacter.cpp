// TRG-World — C++ base for the player miner. Reparent BP_ThirdPersonCharacter to this.

#include "TRGCharacter.h"

#include "CrystalNode.h"
#include "HealthComponent.h"
#include "MiningResourceComponent.h"
#include "TRGMonster.h"
#include "Kismet/GameplayStatics.h"

ATRGCharacter::ATRGCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	Resources = CreateDefaultSubobject<UMiningResourceComponent>(TEXT("Resources"));
}

ACrystalNode* ATRGCharacter::TryMine()
{
	TArray<AActor*> Nodes;
	UGameplayStatics::GetAllActorsOfClass(this, ACrystalNode::StaticClass(), Nodes);

	ACrystalNode* Nearest = nullptr;
	float NearestDistSq = InteractRange * InteractRange;
	const FVector Origin = GetActorLocation();

	for (AActor* Actor : Nodes)
	{
		ACrystalNode* Node = Cast<ACrystalNode>(Actor);
		if (Node == nullptr || Node->IsDepleted())
		{
			continue;
		}

		const float DistSq = FVector::DistSquared(Origin, Node->GetActorLocation());
		if (DistSq <= NearestDistSq)
		{
			NearestDistSq = DistSq;
			Nearest = Node;
		}
	}

	if (Nearest != nullptr)
	{
		Nearest->Mine(this);
	}
	return Nearest;
}

AActor* ATRGCharacter::Attack()
{
	TArray<AActor*> Monsters;
	UGameplayStatics::GetAllActorsOfClass(this, ATRGMonster::StaticClass(), Monsters);

	ATRGMonster* Nearest = nullptr;
	float NearestDistSq = AttackRange * AttackRange;
	const FVector Origin = GetActorLocation();

	for (AActor* Actor : Monsters)
	{
		ATRGMonster* Monster = Cast<ATRGMonster>(Actor);
		if (Monster == nullptr)
		{
			continue;
		}

		const float DistSq = FVector::DistSquared(Origin, Monster->GetActorLocation());
		if (DistSq <= NearestDistSq)
		{
			NearestDistSq = DistSq;
			Nearest = Monster;
		}
	}

	if (Nearest != nullptr)
	{
		if (UHealthComponent* MonsterHealth = Nearest->FindComponentByClass<UHealthComponent>())
		{
			MonsterHealth->ApplyDamage(AttackDamage);
		}
	}
	return Nearest;
}

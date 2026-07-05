// TRG-World — a mineable crystal node. The miner walks up and mines it for crystals.

#include "CrystalNode.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MiningResourceComponent.h"

ACrystalNode::ACrystalNode()
{
	PrimaryActorTick.bCanEverTick = false;

	InteractSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractSphere"));
	SetRootComponent(InteractSphere);
	InteractSphere->InitSphereRadius(200.f);
	InteractSphere->SetCollisionProfileName(TEXT("Trigger"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(InteractSphere);
	Mesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));
}

int32 ACrystalNode::Mine(AActor* Miner)
{
	if (IsDepleted() || Miner == nullptr)
	{
		return 0;
	}

	const int32 Award = FMath::Min(CrystalsPerHit, CrystalsRemaining);
	CrystalsRemaining -= Award;

	if (UMiningResourceComponent* Resources = Miner->FindComponentByClass<UMiningResourceComponent>())
	{
		Resources->AddCrystals(Award);
	}

	if (IsDepleted())
	{
		OnDepleted.Broadcast();
		Mesh->SetVisibility(false);
		SetActorEnableCollision(false);
	}

	return Award;
}

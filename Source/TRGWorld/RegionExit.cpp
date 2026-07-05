// TRG-World — boss-gated region exit. Unlocks when the boss dies; entering it completes the region.

#include "RegionExit.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TRGBoss.h"
#include "TRGGameMode.h"
#include "Kismet/GameplayStatics.h"

ARegionExit::ARegionExit()
{
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	SetRootComponent(Trigger);
	Trigger->SetBoxExtent(FVector(150.f));
	Trigger->SetCollisionProfileName(TEXT("Trigger"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Trigger);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ARegionExit::BeginPlay()
{
	Super::BeginPlay();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ARegionExit::OnTriggerOverlap);

	if (Boss != nullptr)
	{
		Boss->OnBossDefeated.AddDynamic(this, &ARegionExit::HandleBossDefeated);
	}
}

void ARegionExit::HandleBossDefeated()
{
	Unlock();
}

void ARegionExit::Unlock()
{
	bUnlocked = true;
}

void ARegionExit::OnTriggerOverlap(UPrimitiveComponent* /*OverlappedComponent*/, AActor* OtherActor,
	UPrimitiveComponent* /*OtherComp*/, int32 /*OtherBodyIndex*/, bool /*bFromSweep*/, const FHitResult& /*SweepResult*/)
{
	if (!bUnlocked)
	{
		return;
	}

	if (OtherActor != UGameplayStatics::GetPlayerPawn(this, 0))
	{
		return;
	}

	OnRegionCompleted.Broadcast();

	if (ATRGGameMode* GameMode = Cast<ATRGGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		GameMode->CompleteRegion();
	}
}

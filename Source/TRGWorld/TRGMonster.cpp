// TRG-World — a cave monster that chases the player and attacks on contact.

#include "TRGMonster.h"

#include "HealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ATRGMonster::ATRGMonster()
{
	PrimaryActorTick.bCanEverTick = true;

	Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

void ATRGMonster::BeginPlay()
{
	Super::BeginPlay();

	if (Health != nullptr)
	{
		Health->OnDeath.AddDynamic(this, &ATRGMonster::HandleHealthDeath);
	}

	TargetPlayer = UGameplayStatics::GetPlayerPawn(this, 0);
}

void ATRGMonster::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (TargetPlayer == nullptr)
	{
		TargetPlayer = UGameplayStatics::GetPlayerPawn(this, 0);
		return;
	}

	const FVector ToTarget = TargetPlayer->GetActorLocation() - GetActorLocation();
	const float Distance = ToTarget.Size();
	if (Distance > SightRange)
	{
		return;
	}

	if (Distance > AttackRange)
	{
		const FVector Direction = ToTarget.GetSafeNormal2D();
		if (!Direction.IsNearlyZero())
		{
			AddMovementInput(Direction, 1.f);
			SetActorRotation(FRotator(0.f, Direction.Rotation().Yaw, 0.f));
		}
	}
	else
	{
		const float Now = GetWorld()->GetTimeSeconds();
		if (Now - LastAttackTime >= AttackCooldown)
		{
			LastAttackTime = Now;
			if (UHealthComponent* TargetHealth = TargetPlayer->FindComponentByClass<UHealthComponent>())
			{
				TargetHealth->ApplyDamage(AttackDamage);
			}
		}
	}
}

void ATRGMonster::HandleHealthDeath()
{
	HandleDeath();
}

void ATRGMonster::HandleDeath()
{
	if (UCharacterMovementComponent* Movement = GetCharacterMovement())
	{
		Movement->DisableMovement();
	}
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
	SetLifeSpan(3.f);
}

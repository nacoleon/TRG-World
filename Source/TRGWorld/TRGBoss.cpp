// TRG-World — the region boss. A tougher monster whose defeat unlocks the exit.

#include "TRGBoss.h"

#include "HealthComponent.h"

ATRGBoss::ATRGBoss()
{
	if (Health != nullptr)
	{
		Health->MaxHealth = 500.f;
	}

	AttackDamage = 25.f;
	AttackCooldown = 2.0f;
	AttackRange = 200.f;
}

void ATRGBoss::HandleDeath()
{
	OnBossDefeated.Broadcast();
	Super::HandleDeath();
}

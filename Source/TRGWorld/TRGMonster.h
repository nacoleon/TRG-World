// TRG-World — a cave monster that chases the player and attacks on contact.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TRGMonster.generated.h"

class UHealthComponent;

UCLASS()
class TRGWORLD_API ATRGMonster : public ACharacter
{
	GENERATED_BODY()

public:
	ATRGMonster();

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="TRG")
	TObjectPtr<UHealthComponent> Health;

	/** Stops chasing beyond this range. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TRG")
	float SightRange = 2000.f;

	/** Distance at which it can melee the player. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TRG")
	float AttackRange = 150.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TRG")
	float AttackDamage = 10.f;

	/** Seconds between melee hits. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TRG")
	float AttackCooldown = 1.5f;

protected:
	virtual void BeginPlay() override;

	/** Overridable death behavior (the boss overrides this to fire its event). */
	virtual void HandleDeath();

	UPROPERTY(Transient)
	TObjectPtr<APawn> TargetPlayer;

private:
	UFUNCTION()
	void HandleHealthDeath();

	float LastAttackTime = -1000.f;
};

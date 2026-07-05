// TRG-World — reusable health/damage component (player, monsters, boss).

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS(ClassGroup=(TRG), meta=(BlueprintSpawnableComponent))
class TRGWORLD_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health", meta=(ClampMin="1"))
	float MaxHealth = 100.f;

	UPROPERTY(BlueprintReadOnly, Category="Health")
	float CurrentHealth = 100.f;

	UPROPERTY(BlueprintAssignable, Category="Health")
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="Health")
	FOnDeath OnDeath;

	/** Subtract damage; broadcasts OnHealthChanged, then OnDeath once at zero. */
	UFUNCTION(BlueprintCallable, Category="Health")
	void ApplyDamage(float Amount);

	UFUNCTION(BlueprintCallable, Category="Health")
	void Heal(float Amount);

	UFUNCTION(BlueprintPure, Category="Health")
	bool IsDead() const { return bIsDead; }

protected:
	virtual void BeginPlay() override;

private:
	bool bIsDead = false;
};

// TRG-World — C++ base for the player miner. Reparent BP_ThirdPersonCharacter to this.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TRGCharacter.generated.h"

class UHealthComponent;
class UMiningResourceComponent;
class ACrystalNode;

UCLASS()
class TRGWORLD_API ATRGCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATRGCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="TRG")
	TObjectPtr<UHealthComponent> Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="TRG")
	TObjectPtr<UMiningResourceComponent> Resources;

	/** Max distance to mine a crystal node. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TRG")
	float InteractRange = 250.f;

	/** Max distance a melee attack reaches. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TRG")
	float AttackRange = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TRG")
	float AttackDamage = 25.f;

	/** Mine the nearest crystal node in range. BP wires the Mine button here. */
	UFUNCTION(BlueprintCallable, Category="TRG")
	ACrystalNode* TryMine();

	/** Damage the nearest monster in range. BP wires the Attack button here. */
	UFUNCTION(BlueprintCallable, Category="TRG")
	AActor* Attack();
};

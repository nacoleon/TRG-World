// TRG-World — a mineable crystal node. The miner walks up and mines it for crystals.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CrystalNode.generated.h"

class USphereComponent;
class UStaticMeshComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCrystalNodeDepleted);

UCLASS()
class TRGWORLD_API ACrystalNode : public AActor
{
	GENERATED_BODY()

public:
	ACrystalNode();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Crystal")
	TObjectPtr<USphereComponent> InteractSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Crystal")
	TObjectPtr<UStaticMeshComponent> Mesh;

	/** Total crystals left in the node. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Crystal", meta=(ClampMin="0"))
	int32 CrystalsRemaining = 30;

	/** Crystals awarded per mine action. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Crystal", meta=(ClampMin="1"))
	int32 CrystalsPerHit = 10;

	UPROPERTY(BlueprintAssignable, Category="Crystal")
	FOnCrystalNodeDepleted OnDepleted;

	/** Mine the node; awards crystals to Miner's UMiningResourceComponent. Returns amount awarded. */
	UFUNCTION(BlueprintCallable, Category="Crystal")
	int32 Mine(AActor* Miner);

	UFUNCTION(BlueprintPure, Category="Crystal")
	bool IsDepleted() const { return CrystalsRemaining <= 0; }
};

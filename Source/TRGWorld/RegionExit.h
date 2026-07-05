// TRG-World — boss-gated region exit. Unlocks when the boss dies; entering it completes the region.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RegionExit.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UPrimitiveComponent;
class ATRGBoss;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRegionCompleted);

UCLASS()
class TRGWORLD_API ARegionExit : public AActor
{
	GENERATED_BODY()

public:
	ARegionExit();

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Exit")
	TObjectPtr<UBoxComponent> Trigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Exit")
	TObjectPtr<UStaticMeshComponent> Mesh;

	/** The boss that gates this exit. If set, the exit auto-unlocks on its defeat. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Exit")
	TObjectPtr<ATRGBoss> Boss;

	UPROPERTY(BlueprintReadOnly, Category="Exit")
	bool bUnlocked = false;

	UPROPERTY(BlueprintAssignable, Category="Exit")
	FOnRegionCompleted OnRegionCompleted;

	UFUNCTION(BlueprintCallable, Category="Exit")
	void Unlock();

protected:
	UFUNCTION()
	void HandleBossDefeated();

	UFUNCTION()
	void OnTriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};

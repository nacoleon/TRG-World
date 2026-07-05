// TRG-World — tracks a miner's crystals and converts them into TRG Runes (v1 economy is simulated).

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MiningResourceComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnResourcesChanged, int32, Crystals, int32, Runes);

UCLASS(ClassGroup=(TRG), meta=(BlueprintSpawnableComponent))
class TRGWORLD_API UMiningResourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMiningResourceComponent();

	UPROPERTY(BlueprintReadOnly, Category="Mining")
	int32 Crystals = 0;

	UPROPERTY(BlueprintReadOnly, Category="Mining")
	int32 Runes = 0;

	/** Crystals needed to mint one TRG Rune. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mining", meta=(ClampMin="1"))
	int32 CrystalsPerRune = 10;

	UPROPERTY(BlueprintAssignable, Category="Mining")
	FOnResourcesChanged OnResourcesChanged;

	UFUNCTION(BlueprintCallable, Category="Mining")
	void AddCrystals(int32 Amount);

	/** Converts as many crystals as possible into Runes; returns Runes minted. */
	UFUNCTION(BlueprintCallable, Category="Mining")
	int32 ConvertCrystalsToRunes();
};

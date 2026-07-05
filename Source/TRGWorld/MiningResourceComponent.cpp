// TRG-World — tracks a miner's crystals and converts them into TRG Runes (v1 economy is simulated).

#include "MiningResourceComponent.h"

UMiningResourceComponent::UMiningResourceComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMiningResourceComponent::AddCrystals(int32 Amount)
{
	if (Amount <= 0)
	{
		return;
	}

	Crystals += Amount;
	OnResourcesChanged.Broadcast(Crystals, Runes);
}

int32 UMiningResourceComponent::ConvertCrystalsToRunes()
{
	if (CrystalsPerRune <= 0)
	{
		return 0;
	}

	const int32 Minted = Crystals / CrystalsPerRune;
	if (Minted > 0)
	{
		Crystals -= Minted * CrystalsPerRune;
		Runes += Minted;
		OnResourcesChanged.Broadcast(Crystals, Runes);
	}
	return Minted;
}

// TRG-World — game mode. Tracks region completion for the vertical slice.

#include "TRGGameMode.h"

#include "Engine/Engine.h"

void ATRGGameMode::CompleteRegion()
{
	if (bRegionComplete)
	{
		return;
	}

	bRegionComplete = true;
	OnRegionComplete.Broadcast();

	if (GEngine != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Region Complete!"));
	}
}

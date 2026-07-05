// TRG-World — game mode. Tracks region completion for the vertical slice.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TRGGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRegionCompleteSignature);

UCLASS()
class TRGWORLD_API ATRGGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category="TRG")
	bool bRegionComplete = false;

	UPROPERTY(BlueprintAssignable, Category="TRG")
	FOnRegionCompleteSignature OnRegionComplete;

	UFUNCTION(BlueprintCallable, Category="TRG")
	void CompleteRegion();
};

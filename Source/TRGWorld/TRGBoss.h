// TRG-World — the region boss. A tougher monster whose defeat unlocks the exit.

#pragma once

#include "CoreMinimal.h"
#include "TRGMonster.h"
#include "TRGBoss.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBossDefeated);

UCLASS()
class TRGWORLD_API ATRGBoss : public ATRGMonster
{
	GENERATED_BODY()

public:
	ATRGBoss();

	UPROPERTY(BlueprintAssignable, Category="TRG")
	FOnBossDefeated OnBossDefeated;

protected:
	virtual void HandleDeath() override;
};

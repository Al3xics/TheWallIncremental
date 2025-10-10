#pragma once
#include "Ability/TWIAbility.h"
#include "TWIExplosiveWaveAbility.generated.h"

UCLASS()
class ATWIExplosiveWaveAbility : public ATWIAbility
{
	GENERATED_BODY()
public:
	ATWIExplosiveWaveAbility();

protected:
	UPROPERTY(EditDefaultsOnly, Category="ExplosiveWave")
	float LocalRadiusMultiplier = 0.7f;

	virtual void OnActivate() override;
};

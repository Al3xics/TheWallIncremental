#pragma once
#include "Ability/TWIAbility.h"
#include "TWIMagicMissileAbility.generated.h"

UCLASS()
class ATWIMagicMissileAbility : public ATWIAbility
{
	GENERATED_BODY()
public:
	ATWIMagicMissileAbility();

protected:
	/** Rayon plus petit que la valeur container */
	UPROPERTY(EditDefaultsOnly, Category="MagicMissile")
	float LocalRadiusMultiplier = 0.5f;

	virtual void OnActivate() override;
};

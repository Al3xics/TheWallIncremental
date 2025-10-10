#pragma once
#include "Ability/TWIAbility.h"
#include "TWIPoisonBombAbility.generated.h"

UCLASS()
class ATWIPoisonBombAbility : public ATWIAbility
{
	GENERATED_BODY()
public:
	ATWIPoisonBombAbility();

protected:
	virtual void OnActivate() override;
	virtual void OnLogicTick() override;
};

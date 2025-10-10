#pragma once
#include "Ability/TWIAbility.h"
#include "TWICycloneAbility.generated.h"

UCLASS()
class ATWICycloneAbility : public ATWIAbility
{
	GENERATED_BODY()
public:
	ATWICycloneAbility();

protected:
	UPROPERTY(EditDefaultsOnly, Category="Cyclone")
	float PullSpeed = 600.f;

	/** plus grand que la normale */
	ATWICycloneAbility(const FObjectInitializer&);

	virtual void OnActivate() override;
	virtual void OnTickAbility(float DeltaSeconds) override;
	virtual void OnLogicTick() override;
};

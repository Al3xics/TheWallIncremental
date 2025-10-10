#pragma once
#include "Ability/TWIAbility.h"
#include "TheWallIncremental/Public/Components/TWIStatComponent.h"
#include "TWIFreezingZoneAbility.generated.h"



UCLASS()
class ATWIFreezingZoneAbility : public ATWIAbility
{
	GENERATED_BODY()
public:
	ATWIFreezingZoneAbility();

protected:
	UPROPERTY(EditDefaultsOnly, Category="Freeze")
	float SlowPercent = 0.3f; // -30% speed

	/** mémorise le delta appliqué pour restaurer la vitesse à la sortie */
	TMap<TWeakObjectPtr<AActor>, float> AppliedSlow;

	virtual void OnActivate() override;
	virtual void OnLogicTick() override;
	virtual void OnEnemyEnter(class ATWIEnemy* Enemy) override;
	virtual void OnEnemyExit(class ATWIEnemy* Enemy) override;
};

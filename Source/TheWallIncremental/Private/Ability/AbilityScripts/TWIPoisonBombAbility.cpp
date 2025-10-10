#include "TheWallIncremental/Public/Ability/AbilityScripts/TWIPoisonBombAbility.h"
#include "Characters/TWIEnemy.h"

ATWIPoisonBombAbility::ATWIPoisonBombAbility()
{
	bUseArea = true;
	LogicTickInterval = 0.5f;
}

void ATWIPoisonBombAbility::OnActivate()
{
	Super::OnActivate();
}

void ATWIPoisonBombAbility::OnLogicTick()
{
	for (TWeakObjectPtr<ATWIEnemy> E : OverlappingEnemies)
	{
		if (ATWIEnemy* Enemy = E.Get())
		{
			Enemy->ApplyDamage(DamagePerTick);
		}
	}
}

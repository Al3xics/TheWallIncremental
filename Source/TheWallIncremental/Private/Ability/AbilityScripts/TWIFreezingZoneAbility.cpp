#include "TheWallIncremental/Public/Ability/AbilityScripts/TWIFreezingZoneAbility.h"
#include "Characters/TWIEnemy.h"
#include "Components/TWIStatComponent.h" // ajuste
#include "TheWallIncremental/Public/Data/Types.h"

ATWIFreezingZoneAbility::ATWIFreezingZoneAbility()
{
	bUseArea = true;
	LogicTickInterval = 0.5f; // applique DamagePerTick périodiquement
}

void ATWIFreezingZoneAbility::OnActivate()
{
	Super::OnActivate(); // active la zone standard (rayon = Radius * RadiusMultiplier)
}

void ATWIFreezingZoneAbility::OnLogicTick()
{
	for (TWeakObjectPtr<ATWIEnemy> E : OverlappingEnemies)
	{
		if (ATWIEnemy* Enemy = E.Get())
		{
			Enemy->ApplyDamage(DamagePerTick);
		}
	}
}

void ATWIFreezingZoneAbility::OnEnemyEnter(ATWIEnemy* Enemy)
{
	if (!Enemy) return;
	if (UTWIStatComponent* SC = Enemy->FindComponentByClass<UTWIStatComponent>())
	{
		if (SC->HasStat(EStat::Speed))
		{
			const float cur = SC->GetStat(EStat::Speed);
			const float delta = -cur * SlowPercent;
			SC->ModifyStat(EStat::Speed, delta);
			AppliedSlow.Add(Enemy, delta);
		}
	}
}

void ATWIFreezingZoneAbility::OnEnemyExit(ATWIEnemy* Enemy)
{
	if (!Enemy) return;
	if (float* Delta = AppliedSlow.Find(Enemy))
	{
		if (UTWIStatComponent* SC = Enemy->FindComponentByClass<UTWIStatComponent>())
		{
			SC->ModifyStat(EStat::Speed, -(*Delta));
		}
		AppliedSlow.Remove(Enemy);
	}
}

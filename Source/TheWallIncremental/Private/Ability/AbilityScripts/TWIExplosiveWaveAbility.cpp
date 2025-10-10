#include "TheWallIncremental/Public/Ability/AbilityScripts/TWIExplosiveWaveAbility.h"
#include "Characters/TWIEnemy.h"
#include "Kismet/GameplayStatics.h"

ATWIExplosiveWaveAbility::ATWIExplosiveWaveAbility()
{
	bUseArea = true;
}

void ATWIExplosiveWaveAbility::OnActivate()
{
	const float R = FMath::Max(10.f, Radius * LocalRadiusMultiplier);
	ForEachEnemyInRadius([&](ATWIEnemy* E)
	{
		E->ApplyDamage(1e9f); // kill immédiat
	}, R);

	DestroyAbility();
}

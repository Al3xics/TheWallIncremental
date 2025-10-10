#include "TheWallIncremental/Public/Ability/AbilityScripts/TWIMagicMissileAbility.h"

ATWIMagicMissileAbility::ATWIMagicMissileAbility()
{
	// Zone requise, mais très brève :
	bUseArea = true;
	// lifetime court : tu peux aussi le piloter via la stat LifeTime de la courbe
	if (Lifetime <= 0.f) { /* laissé au container */ }
}

void ATWIMagicMissileAbility::OnActivate()
{
	// Burst immédiat dans un petit rayon, puis destruction
	const float R = FMath::Max(10.f, Radius * LocalRadiusMultiplier);
	DealDamageInRadius(R, DamagePerTick);
	DestroyAbility();
}

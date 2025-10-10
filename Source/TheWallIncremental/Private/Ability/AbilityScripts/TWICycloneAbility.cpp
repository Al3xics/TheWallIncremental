#include "TheWallIncremental/Public/Ability/AbilityScripts/TWICycloneAbility.h"
#include "Characters/TWIEnemy.h"

ATWICycloneAbility::ATWICycloneAbility()
{
	bUseArea = true;
	LogicTickInterval = 0.5f;
	RadiusMultiplier = 1.4f; // plus grand par défaut
}

void ATWICycloneAbility::OnActivate()
{
	Super::OnActivate();
}

void ATWICycloneAbility::OnTickAbility(float DeltaSeconds)
{
	for (TWeakObjectPtr<ATWIEnemy> E : OverlappingEnemies)
	{
		if (ATWIEnemy* Enemy = E.Get())
		{
			FVector Dir = (Target - Enemy->GetActorLocation());
			Dir.Z = 0.f;
			const float dist = Dir.Size();
			if (dist > KINDA_SMALL_NUMBER)
			{
				Dir /= dist;
				const FVector delta = Dir * PullSpeed * DeltaSeconds;
				Enemy->AddActorWorldOffset(delta, true);
			}
		}
	}
}

void ATWICycloneAbility::OnLogicTick()
{
	for (TWeakObjectPtr<ATWIEnemy> E : OverlappingEnemies)
	{
		if (ATWIEnemy* Enemy = E.Get())
		{
			Enemy->ApplyDamage(DamagePerTick);
		}
	}
}

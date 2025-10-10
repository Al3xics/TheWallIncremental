// Private/Ability/TWIAbilityContainer.cpp
#include "Ability/TWIAbilityContainer.h"
#include "Ability/TWIAbility.h"
#include "Resources/TWIResourceSubsystem.h"
#include "Characters/TWIPlayerController.h"
#include "Curves/CurveFloat.h"
#include "Engine/World.h"

void UTWIAbilityContainer::Initialize()
{
	for (const FAbility& A : Progressions)
	{
		if (!Levels.Contains(A.Stat))
		{
			Levels.Add(A.Stat, 1); // niveau 1 par défaut
		}
	}
	if (BuyCost > 0)
	{
		bPurchased = false;
	}
}

const FAbility* UTWIAbilityContainer::FindCurve(EAbilityStat Stat) const
{
	for (const FAbility& A : Progressions)
	{
		if (A.Stat == Stat) return &A;
	}
	return nullptr;
}

void UTWIAbilityContainer::EnsureLevelInit(EAbilityStat Stat)
{
	if (!Levels.Contains(Stat))
	{
		Levels.Add(Stat, 1);
	}
}

float UTWIAbilityContainer::EvalCurveFloat(const UCurveBase* Curve, float InX) const
{
	if (!Curve) return 0.f;
	if (const UCurveFloat* CF = Cast<UCurveFloat>(Curve))
	{
		return CF->GetFloatValue(InX);
	}
	// Si tu veux supporter d'autres types de curves, étends ici.
	return 0.f;
}

float UTWIAbilityContainer::GetStatValue(EAbilityStat Stat) const
{
	const FAbility* C = FindCurve(Stat);
	if (!C) return 0.f;

	const int32* LevelPtr = Levels.Find(Stat);
	const float Lvl = LevelPtr ? static_cast<float>(*LevelPtr) : 1.f;
	return EvalCurveFloat(C->CurveStat, Lvl);
}

int32 UTWIAbilityContainer::GetUpgradeCost(EAbilityStat Stat) const
{
	const FAbility* C = FindCurve(Stat);
	if (!C) return 0;

	const int32 NextLevel = (Levels.Contains(Stat) ? Levels[Stat] + 1 : 2);
	return FMath::RoundToInt(EvalCurveFloat(C->CurveCost, static_cast<float>(NextLevel)));
}

float UTWIAbilityContainer::GetCooldownRemaining() const
{
	const UWorld* World = GetWorld();
	if (!World) return 0.f;
	return FMath::Max(0.f, NextReadyTime - World->GetTimeSeconds());
}

bool UTWIAbilityContainer::CanActivate(UTWIResourceSubsystem* ResourceSys) const
{
	if (!AbilityClass) return false;
	if (GetCooldownRemaining() > 0.f) return false;

	if (!bPurchased)
	{
		if (!ResourceSys) return false;
		if (ResourceSys->GetGold() < BuyCost) return false;
	}
	return true;
}

void UTWIAbilityContainer::PlaceAndActivate(ATWIPlayerController* InstigatorPC, const FVector& WorldLocation)
{
	if (!InstigatorPC || !InstigatorPC->GetWorld() || !AbilityClass) return;

	UWorld* World = InstigatorPC->GetWorld();

	// Achat au moment de la première utilisation
	if (!bPurchased)
	{
		if (UTWIResourceSubsystem* Res = World->GetSubsystem<UTWIResourceSubsystem>())
		{
			if (Res->GetGold() >= BuyCost)
			{
				Res->SpendGold(BuyCost);
				bPurchased = true;
			}
			else
			{
				return;
			}
		}
	}

	// Spawn ability actor
	FActorSpawnParameters Params;
	Params.Owner = InstigatorPC;
	Params.Instigator = InstigatorPC->GetPawn();

	ATWIAbility* Ability = World->SpawnActor<ATWIAbility>(AbilityClass, WorldLocation, FRotator::ZeroRotator, Params);
	if (!Ability) return;

	// Lire les stats actuelles
	const float LifeTime      = GetStatValue(EAbilityStat::LifeTime);
	const float Radius        = GetStatValue(EAbilityStat::Radius);
	const float DamagePerTick = GetStatValue(EAbilityStat::DamagePerTick);
	const float Cooldown      = GetStatValue(EAbilityStat::Cooldown);

	Ability->InitializeAbility(WorldLocation, LifeTime, Radius, DamagePerTick, InstigatorPC);
	Ability->ActivateAbility();

	NextReadyTime = World->GetTimeSeconds() + Cooldown;
}

bool UTWIAbilityContainer::UpgradeStat(uint8 AbilityStatEnumValue)
{
	const EAbilityStat Stat = static_cast<EAbilityStat>(AbilityStatEnumValue);
	EnsureLevelInit(Stat);

	const int32 Cost = GetUpgradeCost(Stat);
	UWorld* World = GetWorld();
	if (!World) return false;

	if (UTWIResourceSubsystem* Res = World->GetSubsystem<UTWIResourceSubsystem>())
	{
		if (Res->GetGold() < Cost) return false;

		Res->SpendGold(Cost);
		Levels[Stat] += 1;
		return true;
	}
	return false;
}

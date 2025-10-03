#pragma once

#include "CoreMinimal.h"
#include "Curves/CurveBase.h"
#include "Types.generated.h"

UENUM(BlueprintType)
enum class EStat : uint8
{
	MinHP,
	HP,
	MaxHP,
	MinSpeed,
	Speed,
	MaxSpeed
};

UENUM(BlueprintType)
enum class EAbilityStat : uint8
{
	Cooldown,
	LifeTime,
	Radius,
	DamagePerTick
};

USTRUCT(BlueprintType)
struct FAbility
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	EAbilityStat stat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	UCurveBase* curveStat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	UCurveBase* curveCost;
};
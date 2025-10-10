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
struct FAbilityStat
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	EAbilityStat Stat = EAbilityStat::Cooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	UCurveBase* CurveStat = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	UCurveBase* CurveCost = nullptr;
};
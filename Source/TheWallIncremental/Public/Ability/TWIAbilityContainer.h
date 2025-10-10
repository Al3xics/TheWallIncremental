#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TheWallIncremental/Public/Data/Types.h" // EAbilityStat, FAbility
#include "TheWallIncremental/Public/Resources/TWIResourceSubsystem.h"
#include "TheWallIncremental/Public/Ability/TWIAbility.h"
#include "TWIAbilityContainer.generated.h"


UCLASS(BlueprintType, Blueprintable)
class UTWIAbilityContainer : public UObject
{
	GENERATED_BODY()

public:
	/** Actor concrète à instancier lors de l’activation */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	TSubclassOf<ATWIAbility> AbilityClass;

	/** Coût d'achat initial si l'ability est verrouillée au début (0 = déjà achetée) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	int32 BuyCost = 0;

	/** Progressions des stats et coûts (via courbes) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	TArray<FAbility> Progressions;

	/** Niveau courant par stat (x de la courbe). Par défaut on part à 1. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Runtime")
	TMap<EAbilityStat, int32> Levels;

	/** Prochaine dispo (cooldown absolu temps monde) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Runtime")
	float NextReadyTime = 0.f;

	/** Achetée ? (si BuyCost > 0, alors false au départ) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Runtime")
	bool bPurchased = true;

public:
	/** À appeler après création (ex: dans PlayerController::BeginPlay) */
	UFUNCTION(BlueprintCallable, Category="Ability")
	void Initialize();

	/** Ready ? (cooldown + achat + ressources si achat nécessaire) */
	UFUNCTION(BlueprintCallable, Category="Ability")
	bool CanActivate(UTWIResourceSubsystem* ResourceSys) const;

	/** Spawn l’ability et l’active si possible. Pose le cooldown. */
	UFUNCTION(BlueprintCallable, Category="Ability")
	void PlaceAndActivate(ATWIPlayerController* InstigatorPC, const FVector& WorldLocation);

	/** Upgrade d’une stat (dépense l’or si suffisant) */
	UFUNCTION(BlueprintCallable, Category="Ability")
	bool UpgradeStat(uint8 AbilityStatEnumValue);

	/** Valeur actuelle de la stat au niveau courant (x = level) */
	UFUNCTION(BlueprintPure, Category="Ability")
	float GetStatValue(EAbilityStat Stat) const;

	/** Coût pour passer au prochain niveau de Stat */
	UFUNCTION(BlueprintPure, Category="Ability")
	int32 GetUpgradeCost(EAbilityStat Stat) const;

	/** Cooldown restant (0 si prêt) */
	UFUNCTION(BlueprintPure, Category="Ability")
	float GetCooldownRemaining() const;

protected:
	const FAbility* FindCurve(EAbilityStat Stat) const;
	void EnsureLevelInit(EAbilityStat Stat);
	float EvalCurveFloat(const UCurveBase* Curve, float InX) const;
};

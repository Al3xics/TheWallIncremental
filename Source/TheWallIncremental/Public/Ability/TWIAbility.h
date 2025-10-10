#pragma once
#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "TheWallIncremental/Public/Characters/TWIEnemy.h"
#include "TWIAbility.generated.h"


/**
 * Base d'ability avec support intégré des zones:
 * - Sphere de collision optionnelle (bUseArea)
 * - Liste d'ennemis overlappés
 * - Ticks continus + ticks logiques discrets
 * - Lifetime auto & DestroyAbility()
 */
UCLASS(Abstract)
class ATWIAbility : public AActor
{
	GENERATED_BODY()

public:
	ATWIAbility();

	// ---- Données runtime injectées par le Container ----
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ability")
	FVector Target = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ability")
	float Lifetime = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ability")
	float Radius = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ability")
	float DamagePerTick = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ability")
	TObjectPtr<ATWIPlayerController> SourceController = nullptr;

	/** Tick logique discret (0 = désactivé) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	float LogicTickInterval = 0.f;

	// ---- Zone (activée par défaut) ----
	/** Active la zone/overlaps pour cette ability. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Area")
	bool bUseArea = true;

	/** Multiplicateur appliqué au Radius fourni par le container. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Area", meta=(EditCondition="bUseArea"))
	float RadiusMultiplier = 1.f;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Area", meta=(EditCondition="bUseArea"))
	TObjectPtr<USphereComponent> Sphere;

	/** Ennemis actuellement dans la zone (si bUseArea) */
	UPROPERTY(VisibleAnywhere, Category="Area", meta=(EditCondition="bUseArea"))
	TSet<TWeakObjectPtr<ATWIEnemy>> OverlappingEnemies;

public:
	// ----- API appelée par le Container -----
	UFUNCTION(BlueprintCallable, Category="Ability")
	virtual void InitializeAbility(const FVector& InTarget, float InLifetime, float InRadius, float InDamagePerTick, ATWIPlayerController* InSource);

	UFUNCTION(BlueprintCallable, Category="Ability")
	virtual void ActivateAbility();

	UFUNCTION(BlueprintCallable, Category="Ability")
	virtual void DestroyAbility();

protected:
	// ----- Cycle de vie -----
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	// ----- Hooks pour classes dérivées -----
	virtual void OnActivate() {}
	virtual void OnTickAbility(float DeltaSeconds) {}
	virtual void OnLogicTick() {}
	virtual void OnEnd() {}

	// ----- Hooks zone -----
	virtual void OnEnemyEnter(ATWIEnemy* Enemy) {}
	virtual void OnEnemyExit(ATWIEnemy* Enemy) {}

	// ----- Aide -----
	/** Utility: applique une fonction à tous les ennemis dans le rayon (au moment de l'appel). */
	void ForEachEnemyInRadius(TFunctionRef<void(ATWIEnemy*)> Fn, float InRadius) const;

	/** Utility: dégâts instantanés à tous les ennemis dans un rayon. */
	void DealDamageInRadius(float InRadius, float Damage) const;

private:
	// gestion du tick discret
	float LogicTickAccumulator = 0.f;

	// overlaps
	UFUNCTION()
	void HandleBeginOverlap(UPrimitiveComponent* Overlapped, AActor* Other, UPrimitiveComponent* OtherComp,
	                        int32 BodyIndex, bool bFromSweep, const FHitResult& Sweep);

	UFUNCTION()
	void HandleEndOverlap(UPrimitiveComponent* Overlapped, AActor* Other, UPrimitiveComponent* OtherComp, int32 BodyIndex);
};

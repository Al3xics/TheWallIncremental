#pragma once

#include "CoreMinimal.h"
#include "TheWallIncremental/Public/Ability/TWIAbilityContainer.h"
#include "GameFramework/PlayerController.h"
#include "TheWallIncremental/Public/Resources/TWIResourceSubsystem.h"
#include "TWIPlayerController.generated.h"


UCLASS()
class ATWIPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATWIPlayerController();

	// --- Abilities ----
	/** Liste runtime des abilities (instances de UAbilityContainer) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Abilities")
	TArray<UTWIAbilityContainer*> Abilities;

	/** Ability sélectionnée courante */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Abilities")
	UTWIAbilityContainer* CurrentAbility;

	/** Classes d’abilities à instancier au BeginPlay (réglable dans l’éditeur) */
	UPROPERTY(EditDefaultsOnly, Category="Abilities")
	TArray<TSubclassOf<UTWIAbilityContainer>> AbilityContainerClasses;

	/** Sélectionne une ability par index (pour des boutons UI) */
	UFUNCTION(BlueprintCallable, Category="Abilities")
	void SelectAbilityByIndex(int32 Index);

	/** Sélectionne une ability directement (si tu passes une ref depuis l’UI) */
	UFUNCTION(BlueprintCallable, Category="Abilities")
	void SelectAbility(UTWIAbilityContainer* Ability);

	/** Tente d’activer l’ability courante à l’endroit cliqué */
	UFUNCTION(BlueprintCallable, Category="Abilities")
	void TryActivateCurrentAbilityAt(const FVector& WorldLocation);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	// Input callbacks
	void OnPrimaryClickPressed();

	// Helpers
	bool GetMouseGroundHit(FHitResult& OutHit) const;

	// Accès rapide au système de ressource
	UTWIResourceSubsystem* GetResourceSubsystem() const;
};

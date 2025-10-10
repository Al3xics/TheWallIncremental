// Systems/TWIPlayerController.cpp
#include "TheWallIncremental/Public/Characters/TWIPlayerController.h"
#include "TheWallIncremental/Public/Ability/TWIAbilityContainer.h"          // UTWIAbilityContainer
#include "TheWallIncremental/Public/Resources/TWIResourceSubsystem.h"          // UTWIResourceSubSystem
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

ATWIPlayerController::ATWIPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	CurrentAbility = nullptr;
}

void ATWIPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Instancier les containers configurés dans l’éditeur
	Abilities.Reset();
	for (const TSubclassOf<UTWIAbilityContainer>& Cls : AbilityContainerClasses)
	{
		if (!*Cls) continue;

		// Outer = ce PlayerController pour garder la référence et permettre le GC sûr
		UTWIAbilityContainer* NewContainer = NewObject<UTWIAbilityContainer>(this, Cls);
		if (NewContainer)
		{
			Abilities.Add(NewContainer);

			// (Optionnel) si ton container a besoin d’un init de contexte :
			// NewContainer->Initialize(this);
		}
	}

	CurrentAbility = Abilities.IsValidIndex(0) ? Abilities[0] : nullptr;
}

void ATWIPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	check(InputComponent);

	// Project Settings > Input : crée ces mappings
	// Action Mappings:
	//   - PrimaryClick -> LeftMouseButton

	InputComponent->BindAction("PrimaryClick", IE_Pressed, this, &ATWIPlayerController::OnPrimaryClickPressed);
}

// -------- Abilities --------

void ATWIPlayerController::SelectAbilityByIndex(int32 Index)
{
	if (Abilities.IsValidIndex(Index))
	{
		CurrentAbility = Abilities[Index];
		// TODO: feedback UI (event/delegate/son)
	}
}

void ATWIPlayerController::SelectAbility(UTWIAbilityContainer* Ability)
{
	if (Ability && Abilities.Contains(Ability))
	{
		CurrentAbility = Ability;
	}
}

// void ATWIPlayerController::UpgradeAbility(uint8 AbilityStatEnumValue)
// {
// 	if (!CurrentAbility) return;
//
// 	if (UTWIResourceSubSystem* Res = GetResourceSubsystem())
// 	{
// 		CurrentAbility->UpgradeStat(AbilityStatEnumValue); // Le container gère les coûts/curves/spend
// 	}
// }

void ATWIPlayerController::TryActivateCurrentAbilityAt(const FVector& WorldLocation)
{
	if (!CurrentAbility) return;

	if (UTWIResourceSubsystem* Res = GetResourceSubsystem())
	{
		if (CurrentAbility->CanActivate(Res))
		{
			CurrentAbility->PlaceAndActivate(this, WorldLocation);
		}
		else
		{
			// TODO: feedback UI cooldown / or insuffisant
		}
	}
}

// -------- Input --------

void ATWIPlayerController::OnPrimaryClickPressed()
{
	FHitResult Hit;
	if (GetMouseGroundHit(Hit))
	{
		TryActivateCurrentAbilityAt(Hit.ImpactPoint);
	}
}

// -------- Helpers --------

bool ATWIPlayerController::GetMouseGroundHit(FHitResult& OutHit) const
{
	// Assure-toi que le sol/lane bloque ECC_Visibility (ou remplace par ton canal personnalisé)
	return GetHitResultUnderCursor(ECC_Visibility, /*bTraceComplex*/ false, OutHit);
}

UTWIResourceSubsystem* ATWIPlayerController::GetResourceSubsystem() const
{
	if (UWorld* W = GetWorld())
	{
		return W->GetSubsystem<UTWIResourceSubsystem>();
	}
	return nullptr;
}

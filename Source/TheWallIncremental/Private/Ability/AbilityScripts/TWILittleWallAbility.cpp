// Private/Ability/TWILittleWallAbility.cpp
#include "TheWallIncremental/Public/Ability/AbilityScripts/TWILittleWallAbility.h"
#include "Components/StaticMeshComponent.h"

ATWILittleWallAbility::ATWILittleWallAbility()
{
	bUseArea = false; // pas besoin de zone de détection

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetCollisionResponseToAllChannels(ECR_Block);

	PrimaryActorTick.bCanEverTick = false;
}

void ATWILittleWallAbility::OnActivate()
{
	// Positionné par le Container via Target
	SetActorLocation(Target);

	CurrentHP = MaxHP;

	// Option : s’autodétruit après Lifetime si défini
	if (Lifetime > 0.f)
	{
		FTimerHandle Th;
		GetWorldTimerManager().SetTimer(Th, this, &ATWILittleWallAbility::DestroyAbility, Lifetime, false);
	}
}

void ATWILittleWallAbility::ApplyDamage(float Amount)
{
	CurrentHP = FMath::Max(0.f, CurrentHP - Amount);
	if (CurrentHP <= 0.f)
	{
		DestroyAbility(); // on détruit le mur
	}
}

void ATWILittleWallAbility::OnEnd()
{
	// Effet visuel, son, particules...
}

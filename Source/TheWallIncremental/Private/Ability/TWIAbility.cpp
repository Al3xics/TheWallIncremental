#include "Ability/TWIAbility.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
// Ajuste ces includes :
#include "Characters/TWIEnemy.h"          // ATWIEnemy avec IsAlive(), TakeDamage(float)
#include "GameFramework/Character.h"

ATWIAbility::ATWIAbility()
{
	PrimaryActorTick.bCanEverTick = true;

	// On crée la Sphere tout le temps, mais on ne l'active que si bUseArea
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	RootComponent = Sphere;
	Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetGenerateOverlapEvents(false);
}

void ATWIAbility::InitializeAbility(const FVector& InTarget, float InLifetime, float InRadius, float InDamagePerTick, ATWIPlayerController* InSource)
{
	Target = InTarget;
	Lifetime = InLifetime;
	Radius = InRadius;
	DamagePerTick = InDamagePerTick;
	SourceController = InSource;
	SetActorLocation(Target);
}

void ATWIAbility::ActivateAbility()
{
	// Setup zone si demandée (après Initialize pour connaître Radius)
	if (bUseArea && Sphere)
	{
		const float UseRadius = FMath::Max(10.f, Radius * FMath::Max(0.01f, RadiusMultiplier));
		Sphere->SetWorldLocation(Target);
		Sphere->SetSphereRadius(UseRadius);
		Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
		// Si tes ennemis sont des ACharacter, ECC_Pawn conviendra :
		Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
		Sphere->SetGenerateOverlapEvents(true);
		Sphere->OnComponentBeginOverlap.AddDynamic(this, &ATWIAbility::HandleBeginOverlap);
		Sphere->OnComponentEndOverlap.AddDynamic(this, &ATWIAbility::HandleEndOverlap);
	}

	OnActivate();
}

void ATWIAbility::DestroyAbility()
{
	OnEnd();
	Destroy();
}

void ATWIAbility::BeginPlay()
{
	Super::BeginPlay();
}

void ATWIAbility::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Lifetime
	if (Lifetime > 0.f)
	{
		Lifetime -= DeltaSeconds;
		if (Lifetime <= 0.f)
		{
			DestroyAbility();
			return;
		}
	}

	// Tick logique discret
	if (LogicTickInterval > 0.f)
	{
		LogicTickAccumulator += DeltaSeconds;
		while (LogicTickAccumulator >= LogicTickInterval)
		{
			LogicTickAccumulator -= LogicTickInterval;
			OnLogicTick();
		}
	}

	OnTickAbility(DeltaSeconds);
}

void ATWIAbility::HandleBeginOverlap(UPrimitiveComponent*, AActor* Other, UPrimitiveComponent*, int32, bool, const FHitResult&)
{
	if (!bUseArea) return;
	if (ATWIEnemy* Enemy = Cast<ATWIEnemy>(Other))
	{
		OverlappingEnemies.Add(Enemy);
		OnEnemyEnter(Enemy);
	}
}

void ATWIAbility::HandleEndOverlap(UPrimitiveComponent*, AActor* Other, UPrimitiveComponent*, int32)
{
	if (!bUseArea) return;
	if (ATWIEnemy* Enemy = Cast<ATWIEnemy>(Other))
	{
		if (OverlappingEnemies.Remove(Enemy) > 0)
		{
			OnEnemyExit(Enemy);
		}
	}
}

void ATWIAbility::ForEachEnemyInRadius(TFunctionRef<void(ATWIEnemy*)> Fn, float InRadius) const
{
	UWorld* World = GetWorld();
	if (!World) return;

	TArray<AActor*> Found;
	UGameplayStatics::GetAllActorsOfClass(World, ATWIEnemy::StaticClass(), Found);

	const float R = FMath::Max(10.f, InRadius);
	const float RSq = R * R;
	for (AActor* A : Found)
	{
		if (ATWIEnemy* E = Cast<ATWIEnemy>(A))
		{
			if (FVector::DistSquared(E->GetActorLocation(), Target) <= RSq)
			{
				Fn(E);
			}
		}
	}
}

void ATWIAbility::DealDamageInRadius(float InRadius, float Damage) const
{
	ForEachEnemyInRadius([&](ATWIEnemy* E)
	{
		E->ApplyDamage(Damage);
	}, InRadius);
}

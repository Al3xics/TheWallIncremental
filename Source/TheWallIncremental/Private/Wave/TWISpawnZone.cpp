// Fill out your copyright notice in the Description page of Project Settings.


#include "Wave/TWISpawnZone.h"

#include "Components/ArrowComponent.h"
#include "Wave/TWIWaveSubsystem.h"


// Sets default values
ATWISpawnZone::ATWISpawnZone()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	SpawnBox->SetupAttachment(Root);
	SpawnBox->SetBoxExtent(FVector(200.f, 2000.f, 50.f)); // taille par défaut
	SpawnBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SpawnBox->SetLineThickness(7);

	DirectionIndicator = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	DirectionIndicator->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ATWISpawnZone::BeginPlay()
{
	Super::BeginPlay();

	if (UWorld* World = GetWorld())
	{
		if (UTWIWaveSubsystem* WaveSubsystem = World->GetSubsystem<UTWIWaveSubsystem>())
			WaveSubsystem->RegisterSpawnZone(this);
	}
}

// Called every frame
void ATWISpawnZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

FVector ATWISpawnZone::GetRandomSpawnPoint() const
{
	if (!SpawnBox) return GetActorLocation();

	const FVector Extent = SpawnBox->GetScaledBoxExtent();
	const FVector Origin = SpawnBox->GetComponentLocation();

	const FVector RandomPoint = FVector(
		FMath::RandRange(-Extent.X, Extent.X),
		FMath::RandRange(-Extent.Y, Extent.Y),
		FMath::RandRange(-Extent.Z, Extent.Z)
	);

	return Origin + RandomPoint;
}

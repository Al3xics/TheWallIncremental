// Fill out your copyright notice in the Description page of Project Settings.


#include "TheWallIncremental/Public/Characters/TWIWall.h"

#include "Data/TWILogCategory.h"


// Sets default values
ATWIWall::ATWIWall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox  = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SetRootComponent(CollisionBox);
	CollisionBox->SetBoxExtent(FVector(100.f, 100.f, 100.f));
	CollisionBox->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(CollisionBox);

	StatComponent = CreateDefaultSubobject<UTWIStatComponent>(TEXT("StatComponent"));
	StatComponent->InitializeStat(EStat::MaxHP, 100.f);
	StatComponent->InitializeStat(EStat::HP, 0.f);
}

// Called when the game starts or when spawned
void ATWIWall::BeginPlay()
{
	Super::BeginPlay();

	// If the HP stat was removed, we add it again to the map because it is required
	if (!StatComponent->HasStat(EStat::HP))
		StatComponent->InitializeStat(EStat::HP, 0.f);

	// Initialize HP to MaxHP
	float maxHP = StatComponent->GetStat(EStat::MaxHP);
	StatComponent->SetStat(EStat::HP, maxHP);
}

// Called every frame
void ATWIWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATWIWall::ApplyDamage(float Amount)
{
	StatComponent->AddToStat(EStat::HP, -Amount);
	UE_LOG(LogWall, Log, TEXT("Wall took %f damage"), Amount);
	if (!IsAlive())
		DestroyWall();
}

bool ATWIWall::IsAlive() const
{
	return StatComponent->GetStat(EStat::HP) > 0.f;
}

void ATWIWall::DestroyWall()
{
	UE_LOG(LogWall, Log, TEXT("Wall Destroyed"));
	Destroy();
}


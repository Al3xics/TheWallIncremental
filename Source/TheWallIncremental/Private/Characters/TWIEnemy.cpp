// Fill out your copyright notice in the Description page of Project Settings.


#include "TheWallIncremental/Public/Characters/TWIEnemy.h"

#include "Data/TWILogCategory.h"


// Sets default values
ATWIEnemy::ATWIEnemy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StatComponent = CreateDefaultSubobject<UTWIStatComponent>(TEXT("StatComponent"));
	StatComponent->InitializeStat(EStat::MaxHP, 100.f);
	StatComponent->InitializeStat(EStat::HP, 0.f);
	StatComponent->InitializeStat(EStat::MaxSpeed, 200.f);
	StatComponent->InitializeStat(EStat::Speed, 0.f);
	StatComponent->InitializeStat(EStat::MinSpeed, 100.f);

	MovementComponent = CreateDefaultSubobject<UCharacterMovementComponent>(TEXT("CharacterMovementComponent"));
}

// Called when the game starts or when spawned
void ATWIEnemy::BeginPlay()
{
	Super::BeginPlay();

	// If the HP stat was removed, we add it again to the map because it is required
	if (!StatComponent->HasStat(EStat::HP))
		StatComponent->InitializeStat(EStat::HP, 0.f);
	// If the Speed stat was removed, we add it again to the map because it is required
	if (!StatComponent->HasStat(EStat::Speed))
		StatComponent->InitializeStat(EStat::Speed, 0.f);

	// Initialize Speed to random value between MinSpeed and MaxSpeed
	float randomSpeed = FMath::RandRange(StatComponent->GetStat(EStat::MinSpeed), StatComponent->GetStat(EStat::MaxSpeed));
	StatComponent->SetStat(EStat::Speed, randomSpeed);
}

// Called every frame
void ATWIEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveToWall();
}

void ATWIEnemy::MoveToWall()
{
	
}

void ATWIEnemy::TakeDamage(float Amount)
{
	StatComponent->AddToStat(EStat::HP, -Amount);
	UE_LOG(LogEnemy, Log, TEXT("Enemy took %f damage"), Amount);
	if (!IsAlive())
		DestroyEnemy();
}

bool ATWIEnemy::IsAlive() const
{
	return StatComponent->GetStat(EStat::HP) > 0.f;
}

void ATWIEnemy::UpgradeHealth(float Amount)
{
	StatComponent->AddToStat(EStat::HP, Amount);
}

void ATWIEnemy::DestroyEnemy()
{
	UE_LOG(LogEnemy, Log, TEXT("Enemy Destroyed"));
	Destroy();
}


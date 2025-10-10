// Fill out your copyright notice in the Description page of Project Settings.


#include "TheWallIncremental/Public/Characters/TWIEnemy.h"

#include "Characters/TWIWall.h"
#include "Data/TWILogCategory.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ATWIEnemy::ATWIEnemy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox  = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SetRootComponent(CollisionBox);
	CollisionBox->SetBoxExtent(FVector(100.f, 100.f, 100.f));
	CollisionBox->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	CollisionBox->OnComponentHit.AddDynamic(this, &ATWIEnemy::OnHitWall);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(CollisionBox);

	StatComponent = CreateDefaultSubobject<UTWIStatComponent>(TEXT("StatComponent"));
	StatComponent->InitializeStat(EStat::MaxHP, 100.f);
	StatComponent->InitializeStat(EStat::HP, 0.f);
	StatComponent->InitializeStat(EStat::MaxSpeed, 200.f);
	StatComponent->InitializeStat(EStat::Speed, 0.f);
	StatComponent->InitializeStat(EStat::MinSpeed, 100.f);
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

	// Search the world for the target
	TArray<AActor*> FoundWalls;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATWIWall::StaticClass(), FoundWalls);
	if (FoundWalls.Num() > 0)
		TargetWall = Cast<ATWIWall>(FoundWalls[0]);
	else
		UE_LOG(LogEnemy, Warning, TEXT("No wall found for enemy to move toward!"));
}

// Called every frame
void ATWIEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveToWall();
}

void ATWIEnemy::MoveToWall()
{
	if (!TargetWall) return;

	FVector Direction = (TargetWall->GetActorLocation() - GetActorLocation()).GetSafeNormal();
	float Speed = StatComponent->GetStat(EStat::Speed);

	// Utilise directement la physique du mouvement
	FVector NewLocation = GetActorLocation() + Direction * Speed * GetWorld()->GetDeltaSeconds();
	SetActorLocation(NewLocation, true);
}

void ATWIEnemy::ApplyDamage(float Amount)
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

void ATWIEnemy::OnHitWall(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,	FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor->IsA(ATWIWall::StaticClass()))
	{
		if (ATWIWall* Wall = Cast<ATWIWall>(OtherActor))
			Wall->ApplyDamage(DamageOnHit);
	}
	// else if (OtherActor && OtherActor->IsA(ATWILittleWallAbility::StaticClass()))
	// {
	// 	if (ATWILittleWallAbility* LittleWall = Cast<ATWILittleWallAbility>(OtherActor))
	// 		LittleWall->ApplyDamage(DamageOnHit);
	// }
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "TheWallIncremental/Public/Wave/TWIWaveSubsystem.h"

#include "Characters/TWIEnemy.h"
#include "Data/TWILogCategory.h"
#include "Kismet/GameplayStatics.h"

void UTWIWaveSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	if (WaveConfigAsset.IsNull() == false)
	{
		// Load asset
		WaveConfig = WaveConfigAsset.LoadSynchronous();

		if (WaveConfig) UE_LOG(LogWaveSubsystem, Log, TEXT("Loaded WaveConfig: HPScaling=%.2f, SpawnRateScaling=%.2f"), WaveConfig->EnemyHPScaling, WaveConfig->EnemiesSpawnRateScaling);

		if (const UWorld* World = GetWorld())
		{
			TArray<AActor*> FoundZone;
			UGameplayStatics::GetAllActorsOfClass(World, ATWISpawnZone::StaticClass(), FoundZone);
			if (FoundZone.Num() > 0)
			{
				SpawnZone = Cast<ATWISpawnZone>(FoundZone[0]);
				UE_LOG(LogWaveSubsystem, Log, TEXT("Found SpawnZone: %s"), *SpawnZone->GetName());
			}
			else
			{
				UE_LOG(LogWaveSubsystem, Warning, TEXT("No SpawnZone found!"));
			}
		}
	}
	else
	{
		UE_LOG(LogWaveSubsystem, Warning, TEXT("No WaveConfig asset assigned to WaveSubsystem!"));
	}
}

void UTWIWaveSubsystem::Deinitialize()
{
	Super::Deinitialize();
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	UE_LOG(LogWaveSubsystem, Log, TEXT("UTWIWaveSubsystem Deinitialized"));
}

void UTWIWaveSubsystem::RegisterSpawnZone(ATWISpawnZone* Zone)
{
	SpawnZone = Zone;

	StartNextWave();
}

void UTWIWaveSubsystem::StartNextWave()
{
	if (!WaveConfig || !SpawnZone.IsValid())
	{
		UE_LOG(LogWaveSubsystem, Warning, TEXT("No WaveConfig or SpawnZone found!"));
		return;
	}

	WaveIndex++;
	SpawnedEnemies = 0;
	
	UE_LOG(LogWaveSubsystem, Log, TEXT("Starting wave %d"), WaveIndex);

	float SpawnInterval = GetScaledSpawnRate();
	GetWorld()->GetTimerManager().SetTimer(
		SpawnTimerHandle,
		this,
		&UTWIWaveSubsystem::SpawnEnemyBatch,
		SpawnInterval,
		true
	);
}

void UTWIWaveSubsystem::SpawnEnemyBatch()
{
	if (!WaveConfig->EnemyClass)
	{
		UE_LOG(LogWaveSubsystem, Warning, TEXT("EnemyClass inside WaveConfig in null"));
		return;
	}
	
	if (SpawnedEnemies >= WaveConfig->EnemiesPerWave)
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
		UE_LOG(LogWaveSubsystem, Log, TEXT("Finished spawning wave %d"), WaveIndex);

		GetWorld()->GetTimerManager().SetTimer(
			NextWaveHandle,
			this,
			&UTWIWaveSubsystem::StartNextWave,
			WaveConfig->TimeBetweenWaves,
			true
		);
		
		return;
	}

	FVector SpawnLocation = SpawnZone->GetRandomSpawnPoint();
	AActor* Enemy = GetWorld()->SpawnActor<ATWIEnemy>(WaveConfig->EnemyClass, SpawnLocation, FRotator::ZeroRotator);
	
	if (ATWIEnemy* EnemyActor = Cast<ATWIEnemy>(Enemy))
	{
		// Apply HP scaling to enemy
		if (EnemyActor->StatComponent)
		{
			float EnemyScaledHP = GetEnemyScaledHP(EnemyActor);
			EnemyActor->StatComponent->SetStat(EStat::MaxHP, EnemyScaledHP);
			EnemyActor->StatComponent->SetStat(EStat::HP, EnemyScaledHP);
		}
	}

	SpawnedEnemies++;
}

void UTWIWaveSubsystem::EndGame()
{
	UE_LOG(LogWaveSubsystem, Log, TEXT("Game Over !"));
}

float UTWIWaveSubsystem::GetEnemyScaledHP(ATWIEnemy* Enemy) const
{
	if (!Enemy || !WaveConfig) return 0.f;

	float Growth = WaveConfig->EnemyHPScaling * WaveIndex;
	float ScaledHP = Enemy->StatComponent->GetStat(EStat::MaxHP) * (1.0f + Growth);

	return ScaledHP;
}

float UTWIWaveSubsystem::GetScaledSpawnRate() const
{
	if (!WaveConfig) return 1.f;

	float Growth = WaveConfig->EnemiesSpawnRateScaling * WaveIndex;
	float ScaledSpawnRate = WaveConfig->TimeBetweenEnemiesSpawn / (1.0f + Growth);
    ScaledSpawnRate = FMath::Max(ScaledSpawnRate, WaveConfig->MinSpawnIntervalBetweenEnemies);

	return ScaledSpawnRate;
}

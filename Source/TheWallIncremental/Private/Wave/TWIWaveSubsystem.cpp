// Fill out your copyright notice in the Description page of Project Settings.


#include "TheWallIncremental/Public/Wave/TWIWaveSubsystem.h"
#include "Data/TWILogCategory.h"

void UTWIWaveSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	if (WaveConfigAsset.IsNull() == false)
	{
		// Load asset
		WaveConfig = WaveConfigAsset.LoadSynchronous();

		if (WaveConfig) UE_LOG(LogWaveSubsystem, Log, TEXT("Loaded WaveConfig: HPScaling=%.2f, SpawnRateScaling=%.2f"), WaveConfig->EnemyHPScaling, WaveConfig->SpawnRateScaling);
	}
	else
	{
		UE_LOG(LogWaveSubsystem, Warning, TEXT("No WaveConfig asset assigned to WaveSubsystem!"));
	}
}

void UTWIWaveSubsystem::Deinitialize()
{
	Super::Deinitialize();
	UE_LOG(LogWaveSubsystem, Log, TEXT("UTWIWaveSubsystem Deinitialized"));
}

void UTWIWaveSubsystem::StartNextWave()
{
	
}

void UTWIWaveSubsystem::SpawnEnemyBatch()
{
	
}

void UTWIWaveSubsystem::EndGame()
{
	UE_LOG(LogWaveSubsystem, Log, TEXT("Game Over !"));
}

float UTWIWaveSubsystem::GetEnemyHPScaling() const
{
	return WaveConfig ? WaveConfig->EnemyHPScaling : 1.0f;
}

float UTWIWaveSubsystem::GetSpawnRateScaling() const
{
	return WaveConfig ? WaveConfig->SpawnRateScaling : 1.0f;
}

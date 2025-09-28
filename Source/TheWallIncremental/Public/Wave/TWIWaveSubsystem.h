// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "TWIWaveSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class THEWALLINCREMENTAL_API UTWIWaveSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

private:
	int WaveIndex;
	float EnemyHPScaling;
	float SpawnRateScaling;

public:
	UFUNCTION(BlueprintCallable, Category = "Wave")
	void StartNextWave();

	UFUNCTION(BlueprintCallable, Category = "Wave")
	void SpawnEnemyBatch();

	UFUNCTION(BlueprintCallable, Category = "Wave")
	void EndGame();
};

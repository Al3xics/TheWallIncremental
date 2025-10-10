// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/TWIEnemy.h"
#include "Engine/DataAsset.h"
#include "Wave/TWISpawnZone.h"
#include "TWIWaveConfig.generated.h"

/**
 * 
 */
UCLASS()
class THEWALLINCREMENTAL_API UTWIWaveConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	// ====== Variables ======
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Wave|Enemy", meta=(ClampMin="0.0", ClampMax="1.0", UIMin="0.0", UIMax="1.0",
																			ToolTip="Percentage of HP lost per wave (0.1 = 10% less each wave)."))
	float EnemyHPScaling = 0.1f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Wave|Enemy", meta=(ClampMin="0.0", ClampMax="1.0", UIMin="0.0", UIMax="1.0",
																			ToolTip="Percentage of time between each enemy spawn (0.1 = 10% less each wave)."))
	float EnemiesSpawnRateScaling = 0.1f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Wave|Spawning", meta=(ClampMin="0.0"))
	int EnemiesPerWave = 50;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Wave|Spawning")
	TSubclassOf<ATWIEnemy> EnemyClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Wave|Spawning")
	float TimeBetweenEnemiesSpawn = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Wave|Spawning", meta=(ClampMin="0.01", ToolTip="Minimum possible spawn interval between enemies"))
	float MinSpawnIntervalBetweenEnemies = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Wave|Spawning")
	float TimeBetweenWaves = 30.0f;
};

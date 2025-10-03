// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DataAsset/TWIWaveConfig.h"
#include "Subsystems/WorldSubsystem.h"
#include "TWIWaveSubsystem.generated.h"

/**
 * 
 */
UCLASS(Config=Engine)
class THEWALLINCREMENTAL_API UTWIWaveSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

private:
	int WaveIndex = 0;
	UTWIWaveConfig* WaveConfig = nullptr;

	UPROPERTY(Config) // This variable is set in the "/Config/DefaultEngine.ini" file to use a Data-Driven method
	TSoftObjectPtr<UTWIWaveConfig> WaveConfigAsset;

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category = "Wave")
	void StartNextWave();

	UFUNCTION(BlueprintCallable, Category = "Wave")
	void SpawnEnemyBatch();

	UFUNCTION(BlueprintCallable, Category = "Wave")
	void EndGame();

	UFUNCTION(BlueprintCallable, Category = "Wave")
	float GetEnemyHPScaling() const;
	
	UFUNCTION(BlueprintCallable, Category = "Wave")
	float GetSpawnRateScaling() const;
};

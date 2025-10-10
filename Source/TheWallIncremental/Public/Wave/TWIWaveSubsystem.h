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
	// ====== Variables ======
	int WaveIndex = 0;
	UTWIWaveConfig* WaveConfig = nullptr;
	TWeakObjectPtr<ATWISpawnZone> SpawnZone = nullptr;
	FTimerHandle SpawnTimerHandle;
	FTimerHandle NextWaveHandle;
	int32 SpawnedEnemies = 0;

	UPROPERTY(Config) // This variable is set in the "/Config/DefaultEngine.ini" file to use a Data-Driven method
	TSoftObjectPtr<UTWIWaveConfig> WaveConfigAsset;

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// ====== Functions ======
	UFUNCTION(BlueprintCallable, Category = "Wave")
	void RegisterSpawnZone(ATWISpawnZone* Zone);
	
	UFUNCTION(BlueprintCallable, Category = "Wave")
	void StartNextWave();

	UFUNCTION(BlueprintCallable, Category = "Wave")
	void SpawnEnemyBatch();

	UFUNCTION(BlueprintCallable, Category = "Wave")
	void EndGame();

	UFUNCTION(BlueprintCallable, Category = "Wave")
	float GetEnemyScaledHP(ATWIEnemy* Enemy) const;
	
	UFUNCTION(BlueprintCallable, Category = "Wave")
	float GetScaledSpawnRate() const;
};

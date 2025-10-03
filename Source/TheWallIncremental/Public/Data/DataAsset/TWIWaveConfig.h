// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TWIWaveConfig.generated.h"

/**
 * 
 */
UCLASS()
class THEWALLINCREMENTAL_API UTWIWaveConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Wave")
	float EnemyHPScaling = 1.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Wave")
	float SpawnRateScaling = 1.0f;
};

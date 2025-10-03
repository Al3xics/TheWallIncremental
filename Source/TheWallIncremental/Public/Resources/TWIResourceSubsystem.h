// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "TWIResourceSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class THEWALLINCREMENTAL_API UTWIResourceSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

private:
	int32 Gold = 0;

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	UFUNCTION(BlueprintCallable, Category = "Resources")
	void AddGold(const int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Resources")
	void SpendGold(const int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Resources")
	int32 GetGold() const;
};

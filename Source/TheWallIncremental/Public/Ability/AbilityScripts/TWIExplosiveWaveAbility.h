// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheWallIncremental/Public/Ability/TWIAbility.h"
#include "TWIExplosiveWaveAbility.generated.h"

UCLASS()
class THEWALLINCREMENTAL_API ATWIExplosiveWaveAbility : public ATWIAbility
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATWIExplosiveWaveAbility();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

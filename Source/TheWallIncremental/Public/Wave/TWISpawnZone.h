// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "TWISpawnZone.generated.h"

UCLASS()
class THEWALLINCREMENTAL_API ATWISpawnZone : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATWISpawnZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// ====== Components ======
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Spawn")
	USceneComponent* Root;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Spawn")
	UBoxComponent* SpawnBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Spawn")
	UArrowComponent* DirectionIndicator;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	FVector GetRandomSpawnPoint() const;
};

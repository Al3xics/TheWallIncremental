// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/TWIStatComponent.h"
#include "GameFramework/Actor.h"
#include "TWIWall.generated.h"

UCLASS()
class THEWALLINCREMENTAL_API ATWIWall : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	// ====== Components ======
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wall")
	UBoxComponent* CollisionBox ;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wall")
	UStaticMeshComponent* MeshComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wall")
	UTWIStatComponent* StatComponent;

public:
	ATWIWall();
	virtual void Tick(float DeltaTime) override;

	// ====== Functions ======
	UFUNCTION(BlueprintCallable, Category = "Wall")
	void ApplyDamage(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Wall")
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "Wall")
	void DestroyWall();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TWIStatComponent.h"
#include "GameFramework/Actor.h"
#include "TWIWall.generated.h"

UCLASS()
class THEWALLINCREMENTAL_API ATWIWall : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	ATWIWall();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wall")
	UTWIStatComponent* StatComponent;

	UFUNCTION(BlueprintCallable, Category = "Wall")
	void TakeDamage(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Wall")
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "Wall")
	void DestroyWall();
};

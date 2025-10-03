// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TWIStatComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TWIEnemy.generated.h"

UCLASS()
class THEWALLINCREMENTAL_API ATWIEnemy : public AActor
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	ATWIEnemy();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	UTWIStatComponent* StatComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	UCharacterMovementComponent* MovementComponent;

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void MoveToWall();

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void TakeDamage(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void UpgradeHealth(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void DestroyEnemy();
};

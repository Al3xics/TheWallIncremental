// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/TWIStatComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "TWIEnemy.generated.h"

UCLASS()
class THEWALLINCREMENTAL_API ATWIEnemy : public AActor
{
	GENERATED_BODY()

private:
	// ====== Variables ======
	AActor* TargetWall = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// ====== Components ======
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wall")
	UBoxComponent* CollisionBox ;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wall")
	UStaticMeshComponent* MeshComponent;

	// ====== Variables ======
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float DamageOnHit = 10.f;

	// ====== Functions ======
	UFUNCTION()
	void OnHitWall(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
	ATWIEnemy();
	virtual void Tick(float DeltaTime) override;

	// ====== Components ======
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	UTWIStatComponent* StatComponent;

	// ====== Functions ======
	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void MoveToWall();

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void ApplyDamage(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void UpgradeHealth(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void DestroyEnemy();
};

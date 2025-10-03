// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/Types.h"
#include "TWIStatComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class THEWALLINCREMENTAL_API UTWIStatComponent : public UActorComponent
{
	GENERATED_BODY()

private:

protected:
	virtual void BeginPlay() override;

public:
	UTWIStatComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats")
	TMap<EStat, float> Stats;
	
	UFUNCTION(BlueprintCallable, Category = "Stats")
	float GetStat(EStat Stat) const;

	UFUNCTION(BlueprintCallable, Category = "Stats")
	bool HasStat(EStat Stat) const;

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void AddToStat(EStat Stat, float Delta);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void SetStat(EStat Stat, float Value);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void InitializeStat(EStat Stat, float Value);
};
// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TWIStatComponent.h"
#include "Data/TWILogCategory.h"


// Sets default values for this component's properties
UTWIStatComponent::UTWIStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UTWIStatComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UTWIStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

float UTWIStatComponent::GetStat(EStat Stat) const
{
	if (HasStat(Stat))
		return Stats[Stat];

	UE_LOG(LogStatComponent, Error, TEXT("Stat %s not found"), *StaticEnum<EStat>()->GetNameStringByValue(static_cast<int64>(Stat)));
	return 0.0f;
}

bool UTWIStatComponent::HasStat(EStat Stat) const
{
	return Stats.Contains(Stat);
}

void UTWIStatComponent::AddToStat(EStat Stat, float Delta)
{
	if (HasStat(Stat))
		Stats[Stat] += Delta;
}

void UTWIStatComponent::SetStat(EStat Stat, float Value)
{
	if (HasStat(Stat))
		Stats[Stat] = Value;
}

void UTWIStatComponent::InitializeStat(EStat Stat, float Value)
{
	Stats.Add(Stat, Value);
	UE_LOG(LogStatComponent, Log, TEXT("Stat %s initialized with value %f"), *StaticEnum<EStat>()->GetNameStringByValue(static_cast<int64>(Stat)), Value);
}


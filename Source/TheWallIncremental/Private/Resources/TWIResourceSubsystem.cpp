// Fill out your copyright notice in the Description page of Project Settings.


#include "TheWallIncremental/Public/Resources/TWIResourceSubsystem.h"
#include "Data/TWILogCategory.h"

void UTWIResourceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogResourceSubsystem, Log, TEXT("UTWIResourceSubsystem Initialized"));
}

void UTWIResourceSubsystem::Deinitialize()
{
	Super::Deinitialize();
	UE_LOG(LogResourceSubsystem, Log, TEXT("UTWIResourceSubsystem Deinitialized"));
}

void UTWIResourceSubsystem::AddGold(const int32 Amount)
{
	Gold += Amount;
}

void UTWIResourceSubsystem::SpendGold(const int32 Amount)
{
	Gold = FMath::Max(0, Gold - Amount);
}

int32 UTWIResourceSubsystem::GetGold() const
{
	return Gold;
}

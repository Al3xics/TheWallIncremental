// Fill out your copyright notice in the Description page of Project Settings.


#include "TheWallIncremental/Public/Ability/AbilityScripts/TWICycloneAbility.h"


// Sets default values
ATWICycloneAbility::ATWICycloneAbility()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATWICycloneAbility::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATWICycloneAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


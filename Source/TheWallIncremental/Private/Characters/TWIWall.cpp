// Fill out your copyright notice in the Description page of Project Settings.


#include "TheWallIncremental/Public/Characters/TWIWall.h"


// Sets default values
ATWIWall::ATWIWall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATWIWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATWIWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


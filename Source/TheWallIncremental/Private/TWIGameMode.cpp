// Fill out your copyright notice in the Description page of Project Settings.


#include "TWIGameMode.h"

#include "Characters/TWIPlayerController.h"

ATWIGameMode::ATWIGameMode()
{
	// Use our custom PlayerController class
	PlayerControllerClass = ATWIPlayerController::StaticClass();

	// Set default pawn class to nothing as we don't play a character
	DefaultPawnClass = nullptr;
}

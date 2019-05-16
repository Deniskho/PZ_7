// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "PZ_3GameMode.h"
#include "PZ_3HUD.h"
#include "PZ_3Character.h"
#include "UObject/ConstructorHelpers.h"

APZ_3GameMode::APZ_3GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = APZ_3HUD::StaticClass();
}

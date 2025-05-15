// Copyright Epic Games, Inc. All Rights Reserved.

#include "HorrorTutorialGameMode.h"
#include "HorrorTutorialCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHorrorTutorialGameMode::AHorrorTutorialGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}

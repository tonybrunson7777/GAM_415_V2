// Copyright Epic Games, Inc. All Rights Reserved.

#include "GAM_415_V2GameMode.h"
#include "GAM_415_V2Character.h"
#include "UObject/ConstructorHelpers.h"

AGAM_415_V2GameMode::AGAM_415_V2GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}

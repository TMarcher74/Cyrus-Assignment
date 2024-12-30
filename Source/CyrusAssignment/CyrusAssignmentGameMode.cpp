// Copyright Epic Games, Inc. All Rights Reserved.

#include "CyrusAssignmentGameMode.h"
#include "CyrusAssignmentCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACyrusAssignmentGameMode::ACyrusAssignmentGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}

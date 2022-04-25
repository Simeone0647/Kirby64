// Copyright Epic Games, Inc. All Rights Reserved.

#include "Kirby64GameMode.h"
#include "Kirby64Character.h"
#include "UObject/ConstructorHelpers.h"

AKirby64GameMode::AKirby64GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

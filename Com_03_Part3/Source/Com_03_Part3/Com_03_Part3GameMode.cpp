// Copyright Epic Games, Inc. All Rights Reserved.

#include "Com_03_Part3GameMode.h"
#include "Com_03_Part3PlayerController.h"
#include "Com_03_Part3Character.h"
#include "UObject/ConstructorHelpers.h"

ACom_03_Part3GameMode::ACom_03_Part3GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ACom_03_Part3PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
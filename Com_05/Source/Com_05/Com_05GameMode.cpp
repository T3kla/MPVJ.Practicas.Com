// Copyright Epic Games, Inc. All Rights Reserved.

#include "Com_05GameMode.h"
#include "Com_05Character.h"
#include "UObject/ConstructorHelpers.h"

ACom_05GameMode::ACom_05GameMode()
{
    // set default pawn class to our Blueprinted character
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(
        TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
    if (PlayerPawnBPClass.Class != NULL)
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }
}

// Copyright Epic Games, Inc. All Rights Reserved.

#include "Com_07GameMode.h"
#include "Com_07Ball.h"

ACom_07GameMode::ACom_07GameMode()
{
	// set default pawn class to our ball
	DefaultPawnClass = ACom_07Ball::StaticClass();
}

// Copyright Epic Games, Inc. All Rights Reserved.

#include "DungeonCrawlerGameMode.h"
#include "DungeonCrawlerCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADungeonCrawlerGameMode::ADungeonCrawlerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

#include "GameModes/MyGameMode.h"
#include "UObject/ConstructorHelpers.h"

AMyGameMode::AMyGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClass(TEXT("/Game/Blueprints/BP_PlayerCharacter"));
	if (PlayerPawnClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnClass.Class;
	}
}
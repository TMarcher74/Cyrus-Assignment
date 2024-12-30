// Copyright Epic Games, Inc. All Rights Reserved.

#include "CyrusAssignmentGameMode.h"
#include "CyrusAssignmentCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Spawner.h" // To access ASpawner

ACyrusAssignmentGameMode::ACyrusAssignmentGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
void ACyrusAssignmentGameMode::BeginPlay()
{
    Super::BeginPlay();

    // UHttpCommunication* HttpCommunication = NewObject<UHttpCommunication>();
    // if (HttpCommunication)
    // {
    //     HttpCommunication->FetchJSONData();
    // }

    if (GetWorld())
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		// Define spawn location and rotation
		FVector SpawnLocation(0.f, 0.f, 100.f); // Change as per your desired location
		FRotator SpawnRotation(0.f, 0.f, 0.f);

		// Spawn the Spawner actor
		ASpawner* SpawnerActor = GetWorld()->SpawnActor<ASpawner>(ASpawner::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);

		if (SpawnerActor)
		{
			// Call the SpawnBoxes function or wait for data
			SpawnerActor->OnDataReady(); // Ensure the data is available when it's ready
		}
	}
}
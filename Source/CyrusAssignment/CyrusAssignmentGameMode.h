// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
//#include "HttpCommunication.h"

#include "CyrusAssignmentGameMode.generated.h"

UCLASS(minimalapi)
class ACyrusAssignmentGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACyrusAssignmentGameMode();

protected:
	virtual void BeginPlay() override;
};




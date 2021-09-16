// Copyright Epic Games, Inc. All Rights Reserved.


#include "GeometrySandboxMyGameModeBase.h"

#include "SandboxPawn.h"
#include "SandboxPlayerController.h"

AGeometrySandboxMyGameModeBase::AGeometrySandboxMyGameModeBase()
{
	DefaultPawnClass = ASandboxPawn::StaticClass();
	PlayerControllerClass = ASandboxPlayerController::StaticClass();
}

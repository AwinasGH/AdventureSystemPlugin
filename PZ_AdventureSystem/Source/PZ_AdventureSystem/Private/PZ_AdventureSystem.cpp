// Copyright Epic Games, Inc. All Rights Reserved.

#include "PZ_AdventureSystem.h"

#define LOCTEXT_NAMESPACE "FPZ_AdventureSystemModule"

void FPZ_AdventureSystemModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FPZ_AdventureSystemModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FPZ_AdventureSystemModule, PZ_AdventureSystem)
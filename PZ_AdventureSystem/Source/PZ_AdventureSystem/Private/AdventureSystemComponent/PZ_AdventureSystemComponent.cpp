// Fill out your copyright notice in the Description page of Project Settings.

#include "PZ_AdventureSystem/Public/AdventureSystemComponent/PZ_AdventureSystemComponent.h"


//...............AdventureSystem................//

#include "AdventureSystemComponent/TargetSystem/TargetManager/PZ_TargetManager.h"
#include "AdventureSystemComponent/TargetSystem/TargetBase/PZ_BaseTarget.h"

//..............................................//

#include "GameFramework/Character.h"

#include "Kismet/GameplayStatics.h"


UPZ_AdventureSystemComponent::UPZ_AdventureSystemComponent()
{
	OnCharacterEnteredLocation.AddDynamic(this, &UPZ_AdventureSystemComponent::OnEnteredLocation);
	OnCharacterLeftLocation.AddDynamic(this, &UPZ_AdventureSystemComponent::OnLeftLocation);
}

void UPZ_AdventureSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	TargetManager = Cast<APZ_TargetManager>(UGameplayStatics::GetActorOfClass(GetWorld(), APZ_TargetManager::StaticClass()));
	CurrentLocationName = DefaultLocationName;
}


void UPZ_AdventureSystemComponent::OnEnteredLocation(const TArray<APZ_BaseTarget*>& LocalTargetsArray, const FName& LocationName)
{
	if( LocationName != NAME_None )
	{
		LocationQueue.Add(LocationName);
		CurrentLocationName = LocationName;
	}
	

	if( !IsValid(TargetManager) ) return;
	
	for( const auto& LLocalTarget : LocalTargetsArray)
	{
		TargetManager->AddTarget(LLocalTarget, LLocalTarget->GetIsActive());
	}
}

void UPZ_AdventureSystemComponent::OnLeftLocation(const TArray<APZ_BaseTarget*>& LocalTargetsArray, const FName& LocationName)
{
	if( LocationName != NAME_None )
	{
		if( CurrentLocationName != NAME_None )
		{
			if( LocationQueue.Num() == 1 )
			{
				CurrentLocationName = NAME_None;
				LocationQueue.RemoveAt(0);
			}
			else if( LocationQueue.Num() > 1 )
			{
				LocationQueue.RemoveAt(LocationQueue.Num() - 1);
				CurrentLocationName = LocationQueue.Last();
			}
		}
	}
	

	if( !IsValid(TargetManager) ) return;

	for( const auto& LLocalTarget : LocalTargetsArray)
	{
		TargetManager->RemoveTarget(LLocalTarget);
	}
}
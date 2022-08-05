// Fill out your copyright notice in the Description page of Project Settings.


#include "AdventureSystemComponent/TargetSystem/TargetManager/PZ_TargetManager.h"


//...............Compass................//


#include "PZ_AdventureSystem/Public/AdventureSystemComponent/CompassSystem/CompassMarkerWD/PZ_CompassMarkerWD.h"
#include "AdventureSystemComponent/CompassSystem/CompassTarget/PZ_CompassTarget.h"


//......................................//


#include "AdventureSystemComponent/TargetSystem/TargetBase/PZ_BaseTarget.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"

#include "Kismet/GameplayStatics.h"


APZ_TargetManager::APZ_TargetManager()
{
}




void APZ_TargetManager::BeginPlay()
{
	Super::BeginPlay();

	check(PlayerCameraClass);
	check(CompassMarkerWDClass);

	
	const ACharacter* LPlayerCharacter = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!IsValid(LPlayerCharacter)) return;

	PlayerCamera = Cast<UCameraComponent>(LPlayerCharacter->GetComponentByClass(PlayerCameraClass));
	if ( !IsValid(PlayerCamera) ) return;

	TArray<AActor*> AllTargets;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APZ_BaseTarget::StaticClass(), AllTargets);
	
	for ( int i = 0; i < AllTargets.Num(); ++i )
	{
		APZ_BaseTarget* LBaseTarget = Cast<APZ_BaseTarget>(AllTargets[i]);
		if( !IsValid(LBaseTarget) || !LBaseTarget->GetIsGlobal() ) continue;
		
		if ( APZ_CompassTarget* LTarget = Cast<APZ_CompassTarget>(AllTargets[i]) )
		{
			CreateAndInitMarkerWD(LTarget);

			Targets.Add(LTarget);
		}
		else { Targets.Add(LBaseTarget); }
	}
	
}


UPZ_CompassMarkerWD* APZ_TargetManager::CreateAndInitMarkerWD(APZ_CompassTarget* InTargetActor)
{
	if ( !IsValid(InTargetActor) || !IsValid(CompassMarkerWDClass) || !IsValid(PlayerCamera) ) return nullptr;

	UPZ_CompassMarkerWD* LCompassMarkerWD = NewObject<UPZ_CompassMarkerWD>(this, CompassMarkerWDClass);
	if ( IsValid(LCompassMarkerWD) ) LCompassMarkerWD->InitializeMarker(InTargetActor, PlayerCamera);	

	CompassMarkers.Add(FName(InTargetActor->GetName()), LCompassMarkerWD);

	return LCompassMarkerWD;
}


void APZ_TargetManager::ActivateTarget(APZ_BaseTarget* TargetToActivate)
{
	if ( !IsValid(TargetToActivate) ) return;


	for ( int i = 0; i < Targets.Num(); ++i )
	{
		if ( !IsValid(Targets[i]) || Targets[i] != TargetToActivate ) continue;

		if( const APZ_CompassTarget* LCompassTarget = Cast<APZ_CompassTarget>(Targets[i]) )
		{
			TargetToActivate->IsActive = true;
		
			if ( UPZ_CompassMarkerWD* LCompassMarkerWD = CompassMarkers.FindRef(FName(LCompassTarget->GetName())) )
			{
				LCompassMarkerWD->SetVisibility(ESlateVisibility::Visible);

				if( OnMarkerActivatedBind.IsBound() ) OnMarkerActivatedBind.Broadcast(LCompassMarkerWD);
			}
		}
		else
		{
			TargetToActivate->IsActive = true;
		}
		break;
	}	
}


void APZ_TargetManager::DeactivateTarget(APZ_BaseTarget* TargetToDeactivate)
{
	if ( !IsValid(TargetToDeactivate) ) return;


	for ( int i = 0; i < Targets.Num(); ++i )
	{
		if ( !IsValid(Targets[i]) || Targets[i] != TargetToDeactivate ) continue;

		if( const APZ_CompassTarget* LCompassTarget = Cast<APZ_CompassTarget>(Targets[i]) )
		{
			TargetToDeactivate->IsActive = false;
		
			if ( UPZ_CompassMarkerWD* LCompassMarkerWD = CompassMarkers.FindRef(FName(LCompassTarget->GetName())) )
			{
				LCompassMarkerWD->SetVisibility(ESlateVisibility::Collapsed);

				if( OnMarkerDeactivatedBind.IsBound() ) OnMarkerDeactivatedBind.Broadcast(LCompassMarkerWD);
			}
		}
		else
		{
			TargetToDeactivate->IsActive = false;
		}
		break;
	}	
}


void APZ_TargetManager::AddTarget(APZ_BaseTarget* TargetToAdd, bool bIsActive)
{
	if ( !IsValid(TargetToAdd) ) return;

	TargetToAdd->IsActive = bIsActive;

	Targets.Add(TargetToAdd);

	if( APZ_CompassTarget* LCompassTargetToAdd = Cast<APZ_CompassTarget>(TargetToAdd) )
	{
		UPZ_CompassMarkerWD* LCompassMarkerWD = CreateAndInitMarkerWD(LCompassTargetToAdd);
		if( IsValid(LCompassMarkerWD) && OnMarkerDeactivatedBind.IsBound() ) OnMarkerActivatedBind.Broadcast(LCompassMarkerWD);

		const ESlateVisibility LMarkerVisibility = bIsActive ? ESlateVisibility::Visible : ESlateVisibility::Collapsed;
		LCompassMarkerWD->SetVisibility(LMarkerVisibility);
	}
}

void APZ_TargetManager::DestroyTarget(APZ_BaseTarget* TargetToDestroy)
{
	if ( !IsValid(TargetToDestroy) ) return;

	for ( int i = 0; i < Targets.Num(); ++i )
	{
		if ( !IsValid(Targets[i]) || Targets[i] != TargetToDestroy ) continue;
		
		Targets.Remove(TargetToDestroy);

		if ( UPZ_CompassMarkerWD* LCompassMarkerWD = CompassMarkers.FindRef(FName(TargetToDestroy->GetName())) )
		{
			if ( OnMarkerDeactivatedBind.IsBound() ) OnMarkerDeactivatedBind.Broadcast(LCompassMarkerWD);

			if( CompassMarkers.Contains(FName(TargetToDestroy->GetName())) ) CompassMarkers.Remove(FName(TargetToDestroy->GetName()));	

			LCompassMarkerWD->RemoveFromParent();			
		}
		
		TargetToDestroy->Destroy();
	}
}

void APZ_TargetManager::RemoveTarget(APZ_BaseTarget* TargetToRemove)
{
	if ( !IsValid(TargetToRemove) ) return;

	for ( int i = 0; i < Targets.Num(); ++i )
	{
		if ( !IsValid(Targets[i]) || Targets[i] != TargetToRemove ) continue;

		Targets.Remove(TargetToRemove);
		
		if ( UPZ_CompassMarkerWD* LCompassMarkerWD = CompassMarkers.FindRef(FName(TargetToRemove->GetName())) )
		{
			if ( OnMarkerDeactivatedBind.IsBound() ) OnMarkerDeactivatedBind.Broadcast(LCompassMarkerWD);

			if( CompassMarkers.Contains(FName(TargetToRemove->GetName())) ) CompassMarkers.Remove(FName(TargetToRemove->GetName()));	

			LCompassMarkerWD->RemoveFromParent();			
		}
	}
}


TArray<UPZ_CompassMarkerWD*> APZ_TargetManager::GetActiveCompassMarkersWDs() const
{
	TArray<UPZ_CompassMarkerWD*> LResult;

	for ( const auto& LCompassMarkerWD : CompassMarkers )
	{
		if (LCompassMarkerWD.Value->GetVisibility() == ESlateVisibility::Visible) LResult.Add(LCompassMarkerWD.Value);
	}
	return LResult;
}

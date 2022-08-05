// Copyright (c) 2020 - 2022 GameWheelStudio. All rights reserved.

#include "AdventureSystemComponent/LocationSystem/Location/PZ_Location.h"

//...............AdventureSystem................//

#include "AdventureSystemComponent/PZ_AdventureSystemComponent.h"
#include "AdventureSystemComponent/TargetSystem/TargetBase/PZ_BaseTarget.h"

//..............................................//

#include "Components/BoxComponent.h"

#include "GameFramework/Character.h"


APZ_Location::APZ_Location(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	BoxTrigger = CreateDefaultSubobject<UBoxComponent>("BoxTrigger");
	
	if( IsValid(BoxTrigger) ) SetRootComponent(BoxTrigger);
}

void APZ_Location::BeginPlay()
{
	Super::BeginPlay();
	
	if( !IsValid(BoxTrigger) ) return;

	BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &APZ_Location::OnTriggerBeginOverlap);
	BoxTrigger->OnComponentEndOverlap.AddDynamic(this, &APZ_Location::OnTriggerEndOverlap);
}


void APZ_Location::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
											UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
												bool bFromSweep, const FHitResult& SweepResult)
{
	if( IsValid(AdventureComponent = Cast<UPZ_AdventureSystemComponent>(OtherActor->GetComponentByClass(UPZ_AdventureSystemComponent::StaticClass()))) )
	{
		AdventureComponent->OnCharacterEnteredLocation.Broadcast(LocationData.LocalTargets, LocationData.LocationName);
	}
}

void APZ_Location::OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
											UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if( IsValid(AdventureComponent) )
	{
		AdventureComponent->OnCharacterLeftLocation.Broadcast(LocationData.LocalTargets, LocationData.LocationName);
	}
}

// Copyright (c) 2020 - 2022 GameWheelStudio. All rights reserved.

#pragma once

#include "CoreMinimal.h"

#include "AdventureSystemComponent/LocationSystem/Location/PZ_LocationInfo.h"

#include "PZ_Location.generated.h"


class UBoxComponent;

class UPZ_AdventureSystemComponent;
class APZ_BaseTarget;


/*
	Location trigger for AdventureSystemComponent
*/
UCLASS()
class PZ_ADVENTURESYSTEM_API APZ_Location : public AActor
{
	GENERATED_BODY()
	

//constructor
public:

	APZ_Location(const FObjectInitializer& ObjectInitializer);
	
//c++ private methods
private:


//c++ protected methods
protected:

	virtual void BeginPlay() override;

	
	UFUNCTION()
		void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	

//c++ public methods
public:


	
//c++ protected values
protected:
	
	UPROPERTY()
		UPZ_AdventureSystemComponent* AdventureComponent = nullptr;
	

//>>..............................................................................................................<<//
	


//Blueprint values
protected:
	
	/*
		Trigger for handling player entering and leaving location
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Location|Components")
		UBoxComponent* BoxTrigger = nullptr;
	
	/*
		Struct for keeping location data
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Location|Data")
		FLocationData LocationData;
};

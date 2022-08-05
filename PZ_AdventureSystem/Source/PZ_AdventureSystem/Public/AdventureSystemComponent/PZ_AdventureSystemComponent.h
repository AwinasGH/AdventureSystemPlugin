// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PZ_AdventureSystemComponent.generated.h"


class APZ_LocationTrigger;

class APZ_TargetManager;
class APZ_BaseTarget;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCharacterEnteredLocation, const TArray<APZ_BaseTarget*>&, LocalTargetsArray, const FName&, LocationName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCharacterLeftLocation, const TArray<APZ_BaseTarget*>&, LocalTargetsArray, const FName&, LocationName);



/*
	Character component for managing his location
*/
UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PZ_ADVENTURESYSTEM_API UPZ_AdventureSystemComponent : public UActorComponent
{
	GENERATED_BODY()
	


//constructor
public:

	UPZ_AdventureSystemComponent();


//c++ private methods
private:
	

//c++ protected methods
protected:
	

	virtual void BeginPlay() override;
	
	
	UFUNCTION()
		void OnEnteredLocation(const TArray<APZ_BaseTarget*>& LocalTargetsArray, const FName& LocationName);

	UFUNCTION()
		void OnLeftLocation(const TArray<APZ_BaseTarget*>& LocalTargetsArray, const FName& LocationName);
	
	
//c++ public methods
public:
	
	UFUNCTION(BlueprintCallable, Category = "AdventureSystemComponent|Getters")
		 FORCEINLINE APZ_TargetManager* GetTargetManager() const { return TargetManager; }

	UFUNCTION(BlueprintCallable, Category = "AdventureSystemComponent|Getters")
		 FORCEINLINE FName& GetCurrentLocationName() { return CurrentLocationName; }

	UFUNCTION(BlueprintCallable, Category = "AdventureSystemComponent|Getters")
		 FORCEINLINE TArray<APZ_BaseTarget*>& GetCurrentLocationLocalTargets() { return CurrentLocationLocalTargets; }


//...............................................LocationQueue Interface...............................................//
	
	
	UFUNCTION(BlueprintCallable, Category = "AdventureSystemComponent|LocationQueueInterface|Getters")
		const FName& GetLastLocationInQueue() const { return LocationQueue.Last(); }

	UFUNCTION(BlueprintCallable, Category = "AdventureSystemComponent|LocationQueueInterface|Getters")
		const TArray<FName>& GetLocationQueue() const { return LocationQueue; }

	UFUNCTION(BlueprintCallable, Category = "AdventureSystemComponent|LocationQueueInterface|Getters")
		const FName& GetFirstLocationInQueue() const { return LocationQueue[0]; }
	

//.....................................................................................................................//
	
	
//c++ public values
public:
	
	UPROPERTY(BlueprintAssignable)
		FOnCharacterEnteredLocation OnCharacterEnteredLocation;

	UPROPERTY(BlueprintAssignable)
		FOnCharacterLeftLocation OnCharacterLeftLocation;
	
	
//c++ protected values
protected:

	UPROPERTY()
		TArray<APZ_BaseTarget*> CurrentLocationLocalTargets;

	UPROPERTY()
		APZ_TargetManager* TargetManager = nullptr;

	/*
		Current location name.
	*/
	FName CurrentLocationName = NAME_None;
	/*
		Location names Queue.
	*/
	TArray<FName> LocationQueue;
	
	
	
//>>..............................................................................................................<<//
	


//Blueprint values
public:


	/*
		Default Location Name name.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FName DefaultLocationName = NAME_None;
};

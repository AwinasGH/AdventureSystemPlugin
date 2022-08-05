// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PZ_TargetManager.generated.h"


class UCameraComponent;


class APZ_BaseTarget;
class APZ_CompassTarget;

class UPZ_CompassMarkerWD;


DECLARE_MULTICAST_DELEGATE_OneParam(FOnMarkerActivated, UPZ_CompassMarkerWD*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMarkerDeactivated, UPZ_CompassMarkerWD*);


/*
	Manager for targets for PZ_CompassWD widget
 */
UCLASS()
class PZ_ADVENTURESYSTEM_API APZ_TargetManager : public AActor
{
	GENERATED_BODY()


//constructor
public:

	APZ_TargetManager();


//c++ private methods
private:

	UPZ_CompassMarkerWD* CreateAndInitMarkerWD(APZ_CompassTarget* InTargetActor);


//c++ protected methods
protected:

	virtual void BeginPlay() override;



//c++ public methods
public:

	UFUNCTION(BlueprintCallable, Category = "TargetManagers|Getters")
		FORCEINLINE TMap<FName, UPZ_CompassMarkerWD*>& GetCompassMarkers() { return CompassMarkers; }

	UFUNCTION(BlueprintCallable, Category = "TargetManagers|Getters")
		TArray<UPZ_CompassMarkerWD*> GetActiveCompassMarkersWDs() const;

	/*
		Activates already existing target and corresponding MarkerWD
	*/
	UFUNCTION(BlueprintCallable, Category = "TargetManagers|Functions")
		void ActivateTarget(APZ_BaseTarget* TargetToActivate);

	/*
		Deactivates already existing target and corresponding MarkerWD
	*/
	UFUNCTION(BlueprintCallable, Category = "TargetManagers|Functions")
		void DeactivateTarget(APZ_BaseTarget* TargetToDeactivate);

	/*
		Adds new target and if it's compass target creates new MarkerWD
	*/
	UFUNCTION(BlueprintCallable, Category = "TargetManagers|Functions")
		void AddTarget(APZ_BaseTarget* TargetToAdd, bool bIsActive);

	/*
		Destroys target actor and corresponding MarkerWD
	*/
	UFUNCTION(BlueprintCallable, Category = "TargetManagers|Functions")
		void DestroyTarget(APZ_BaseTarget* TargetToDestroy);

	/*
		Removes target from array and corresponding MarkerWD
	*/
	UFUNCTION(BlueprintCallable, Category = "TargetManagers|Functions")
		void RemoveTarget(APZ_BaseTarget* TargetToDestroy);


//c++ public values
public:	

	FOnMarkerActivated OnMarkerActivatedBind;

	FOnMarkerDeactivated OnMarkerDeactivatedBind;


//c++ private values
private:

	UPROPERTY()
		UCameraComponent* PlayerCamera = nullptr;

	UPROPERTY()
		TMap<FName, UPZ_CompassMarkerWD*> CompassMarkers;

//>>..............................................................................................................<<//


//Blueprint values
protected:

	/*
		Array of ALL targets
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TargetManager|Targets")
		TArray<APZ_BaseTarget*> Targets;

	/*
		Class for widget marker to create. Image will be overriden with target's image.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = "TargetManager|Widget")
		TSubclassOf<UPZ_CompassMarkerWD> CompassMarkerWDClass;

	/*
		Class for PlayerCameraComponent.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,  Category = "Target|Classes")
		TSubclassOf<UCameraComponent> PlayerCameraClass;

};

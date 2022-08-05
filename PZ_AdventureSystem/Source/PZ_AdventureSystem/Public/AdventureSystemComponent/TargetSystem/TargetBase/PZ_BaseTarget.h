// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PZ_BaseTarget.generated.h"


class UTexture2D;

/*
	Base Target actor for AdventureSystem
*/
UCLASS(Abstract)
class PZ_ADVENTURESYSTEM_API APZ_BaseTarget : public AActor
{
	GENERATED_BODY()


//c++ public methods
public:

	friend class APZ_TargetManager;
	

	UFUNCTION(BlueprintCallable, Category = "BaseTarget|BaseTargetFunctions")
		FORCEINLINE bool GetIsActive() const { return IsActive; }

	UFUNCTION(BlueprintCallable, Category = "BaseTarget|BaseTargetFunctions")
		FORCEINLINE bool GetIsGlobal() const { return IsGlobal; }
	
	

//>>....................................................................................................................<<//



	
//Blueprint values
protected:

	/*
		Defines Target's activity
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = "CompassTarget|Default")
		bool IsActive = true;
	/*
		Defines Target's scope
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = "CompassTarget|Default")
		bool IsGlobal = false;
};

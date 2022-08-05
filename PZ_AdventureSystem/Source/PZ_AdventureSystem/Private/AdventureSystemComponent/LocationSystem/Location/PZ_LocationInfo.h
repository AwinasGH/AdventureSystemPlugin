#pragma once


#include "PZ_LocationInfo.generated.h"


class APZ_BaseTarget;



USTRUCT(BlueprintType)
struct FLocationData
{
	GENERATED_USTRUCT_BODY()

public:
	

	FLocationData(){}

	FLocationData(const FName& InLocationName, const TArray<APZ_BaseTarget*>& InLocalTargets) :
			LocationName(InLocationName), LocalTargets(InLocalTargets)
	{
		
	}
	

public:
	
	/*
		Location name value. 
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Location|Data")
		FName LocationName = NAME_None;

	/*
		Location local Targets. TEMPORARY HAS EditInstanceOnly specifier, waits for SaveSystem update.
	*/
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Location|Data")
		TArray<APZ_BaseTarget*> LocalTargets;
};
#pragma once

#include "CoreMinimal.h"
#include "AdventureSystemComponent/TargetSystem/TargetBase/PZ_BaseTarget.h"
#include "PZ_CompassTarget.generated.h"

/*
	Target actor for CompassWD markers
*/
UCLASS()
class PZ_ADVENTURESYSTEM_API APZ_CompassTarget : public APZ_BaseTarget
{
	GENERATED_BODY()
	
	
//c++ public methods
public:

	UFUNCTION(BlueprintCallable, Category = "CompassTarget|Getters")
		FORCEINLINE UTexture2D* GetMarkerTexture() const { return MarkerTexture; }
	

//>>....................................................................................................................<<//

	
//Blueprint values
protected:

	/*
		Marker texture. Will override default marker widget image.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = "CompassTarget|Widget")
		UTexture2D* MarkerTexture;
	
};

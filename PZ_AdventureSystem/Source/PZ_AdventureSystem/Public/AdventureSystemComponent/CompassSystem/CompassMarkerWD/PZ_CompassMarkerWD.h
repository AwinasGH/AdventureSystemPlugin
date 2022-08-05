#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PZ_CompassMarkerWD.generated.h"


class UCameraComponent;

class APZ_CompassTarget;

class UCanvasPanelSlot;
class UCanvasPanel;
class UImage;


/*
	Widget for compass markers 
*/
UCLASS(Abstract)
class PZ_ADVENTURESYSTEM_API UPZ_CompassMarkerWD : public UUserWidget
{
	GENERATED_BODY()


//constructor
public:

	UPZ_CompassMarkerWD(const FObjectInitializer& ObjectInitializer);


//c++ private methods
private:

	bool IsMarkerBehind(const FVector& DirectionToTarget, const FVector& CameraForwardVector);


//c++ protected methods
protected:

	virtual void NativeConstruct() override;


//c++ public methods
public:

	void InitializeMarker(APZ_CompassTarget* InTarget, UCameraComponent* InPlayerCamera);

	void InitializeSlot(FAnchors Anchors, FVector2D Alignment);

	void UpdateMarker(UCanvasPanelSlot* MarkerSlot);	


//c++ private values
private:

	FVector TargetLocation = FVector::ZeroVector;

	UCameraComponent* PlayerCamera = nullptr;

	UTexture2D* MarkerTexture = nullptr;

//>>>...............................................................................................................................................................................<<<//





//Blueprint values
public:

	/*
		Image representing marker in compass.
	*/
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CompassMarkerWD|Widgets")
		UImage* MarkerImage = nullptr;
	/*
		Main marker canvas.
	*/
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "CompassMarkerWD|Widgets")
		UCanvasPanel* MarkerCanvas = nullptr;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GD|Values")
		float MarkerMovingSpeed = 700.0f;
	
};

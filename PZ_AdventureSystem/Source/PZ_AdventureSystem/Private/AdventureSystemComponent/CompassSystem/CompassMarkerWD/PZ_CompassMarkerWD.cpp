
#include "AdventureSystemComponent/CompassSystem/CompassMarkerWD/PZ_CompassMarkerWD.h"

#include "AdventureSystemComponent/CompassSystem/CompassTarget/PZ_CompassTarget.h"


//...............Subwidgets/Elements................//

#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"

//..................................................//

#include "Camera/CameraComponent.h"

#include "Kismet/KismetMathLibrary.h"



UPZ_CompassMarkerWD::UPZ_CompassMarkerWD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}



void UPZ_CompassMarkerWD::NativeConstruct()
{
	Super::NativeConstruct();

	if( IsValid(MarkerImage) && IsValid(MarkerTexture) ) MarkerImage->SetBrushFromTexture(MarkerTexture);
}

void UPZ_CompassMarkerWD::InitializeMarker(APZ_CompassTarget* InTarget, UCameraComponent* InPlayerCamera)
{
	if( !IsValid(InTarget) || !IsValid(InPlayerCamera) ) return;

	if( IsValid(InTarget->GetMarkerTexture()) ) MarkerTexture = InTarget->GetMarkerTexture();

	PlayerCamera = InPlayerCamera;
	TargetLocation = InTarget->GetActorLocation();

	InTarget->GetIsActive() ? SetVisibility(ESlateVisibility::Visible) : SetVisibility(ESlateVisibility::Collapsed);
}


void UPZ_CompassMarkerWD::InitializeSlot(FAnchors Anchors, FVector2D Alignment)
{
	UCanvasPanelSlot* LSlot = Cast<UCanvasPanelSlot>(Slot);

	if( !IsValid(LSlot) ) return;

	LSlot->SetAnchors(Anchors);
	LSlot->SetAlignment(Alignment);
	LSlot->SetPosition(FVector2D(0.0f, 0.0f));
}


void UPZ_CompassMarkerWD::UpdateMarker(UCanvasPanelSlot* MarkerSlot)
{
	if( !IsValid(PlayerCamera) || !IsValid(MarkerSlot) ) return;

	const FRotator LRotation = UKismetMathLibrary::FindLookAtRotation(TargetLocation, PlayerCamera->GetComponentLocation());

	const FVector LDirection = LRotation.RotateVector(FVector::ForwardVector);
	FVector2D LDirection2D = FVector2D(LDirection.X, LDirection.Y);
	LDirection2D.Normalize();


	const FVector2D LRightVector2D = FVector2D(PlayerCamera->GetRightVector().X, PlayerCamera->GetRightVector().Y);
	const float LAngleToRight = FVector2D::DotProduct(LRightVector2D, LDirection2D);


	const FVector2D LForwardVector2D = FVector2D(PlayerCamera->GetForwardVector().X, PlayerCamera->GetForwardVector().Y);
	const float LAngleToForward = FVector2D::DotProduct(LForwardVector2D, LDirection2D);


	const float LMarkerXPosition = LAngleToRight / LAngleToForward * MarkerMovingSpeed;


	if( IsMarkerBehind(LDirection, PlayerCamera->GetForwardVector()) )
	{
		MarkerSlot->SetPosition(FVector2D(LMarkerXPosition, 200.0f));
	}
	else
	{
		MarkerSlot->SetPosition(FVector2D(LMarkerXPosition, 0.0f));
	}
}

bool UPZ_CompassMarkerWD::IsMarkerBehind(const FVector& DirectionToTarget, const FVector& CameraForwardVector)
{
	const float LProjection = FVector::DotProduct(DirectionToTarget.GetSafeNormal(), CameraForwardVector.GetSafeNormal());

	const float LAngleInDegrees = FMath::RadiansToDegrees(FMath::Acos(LProjection));

	return LAngleInDegrees < 140.0f ? true : false;
}

#include "DirectionalFlipbookComponent.h"
#include "Kismet/GameplayStatics.h"

void UDirectionalFlipbookComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	FacePlayerCamera();

	UpdateFlipbookDirection(); // Check if flipbook needs updated to match rotation

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UDirectionalFlipbookComponent::FacePlayerCamera()
{
	
	if (UWorld* World = GetWorld()) {
		
		if (UGameplayStatics::GetGameInstance(World)) {
			if (APlayerCameraManager* PlayerCamera = World->GetFirstPlayerController()->PlayerCameraManager)
			{
				//Get look rotation from player camera to this component's location
				FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(PlayerCamera->GetCameraLocation(), GetComponentLocation());
				
				//Only concerned with updating rotation Yaw
				FRotator NewRot = FRotator(0.0f, (LookAtRot + FRotator(0.0f, 90.0f, 0.0f)).Yaw, 0.0f);
				SetWorldRotation(NewRot);
			}
		}
	}
}


void UDirectionalFlipbookComponent::UpdateFlipbookDirection()
{
	SpriteAngle = GetOwner()->GetActorRotation().Yaw - GetComponentRotation().Yaw + 270.0f;
	UPaperFlipbook* NewFlipbook = SourceDirectionalFlipbook->GetFlipbookFromAngle(UKismetMathLibrary::FWrap(SpriteAngle, 0.0f, 360.0f));

	if (NewFlipbook != SourceFlipbook) {
		SetFlipbook(NewFlipbook);
	}
}
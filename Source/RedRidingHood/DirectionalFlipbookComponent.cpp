#include "DirectionalFlipbookComponent.h"
#include "Kismet/GameplayStatics.h"

void UDirectionalFlipbookComponent::BeginPlay()
{
	Super::BeginPlay();

	if (SourceDirectionalFlipbook != nullptr) 
	{
		//DirectionalFlipbook can be set before runtime, if so we need to instantiate its anim notifies here
		InstantiateAnimNotifies(); 
	}
}

void UDirectionalFlipbookComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	FacePlayerCamera();

	// Check if flipbook needs updated to match rotation
	UpdateFlipbookDirection(); 

	const float OldTime = AccumulatedTime;

	// Original PaperFlipbook Tick event, handles animation, rendering etc.
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/* Checking for any Anim Notifies between previous and current timeline positions, and looping through any found to call their notify events*/
	TArray<UAnimNotify2D*> TriggeredAnimNotifies;
	GetAnimNotifiesFromDeltaPositions(OldTime, AccumulatedTime, TriggeredAnimNotifies);

	if (TriggeredAnimNotifies.Num() > 0) 
	{
		for (int32 Index = 0; Index < TriggeredAnimNotifies.Num(); Index++) 
		{
			TriggeredAnimNotifies[Index]->Notify(this);
		}
	}
}

void UDirectionalFlipbookComponent::GetAnimNotifiesFromDeltaPositions(const float& PreviousPosition, const float& CurrentPosition, TArray<UAnimNotify2D*>& OutAnimNotifies) const
{
	if ((CurrentNotifies.Num() == 0) || (PreviousPosition == CurrentPosition))
	{
		return;
	}

	//Looping through every current notify, checking if they fall between the animation's previous and current timeline position
	for (int NotifyIndex = 0; NotifyIndex < CurrentNotifies.Num(); NotifyIndex++) 
	{
		const FAnimNotify2DTrigger& Notify = CurrentNotifies[NotifyIndex];

		if (Notify.Time > PreviousPosition && Notify.Time <= CurrentPosition) 
		{

			if (Notify.InstancedNotify != nullptr) 
			{
				OutAnimNotifies.Add(Notify.InstancedNotify);
			}
		}
	}
}

void UDirectionalFlipbookComponent::SetDirectionalFlipbook(UDirectionalFlipbookDataAsset* NewDirectionalFlipbook)
{
	if (NewDirectionalFlipbook != SourceDirectionalFlipbook) 
	{
		SourceDirectionalFlipbook = NewDirectionalFlipbook;

		//Get new DirectionalFlipbook's anim notifies and instantiate them
		InstantiateAnimNotifies(); 

		//Update PaperFlipbook being displayed, based on new DirectionalFlipbook
		UpdateFlipbookDirection(); 
	}
}

TArray<FAnimNotify2DTrigger> UDirectionalFlipbookComponent::GetCurrentNotifies() const
{
	return CurrentNotifies;
}

void UDirectionalFlipbookComponent::FacePlayerCamera()
{
	
	if (UWorld* World = GetWorld()) 
	{
		if (UGameplayStatics::GetGameInstance(World)) 
		{
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

	if (NewFlipbook != SourceFlipbook) 
	{
		const float OldPosition = AccumulatedTime;
		SetFlipbook(NewFlipbook);

		//SetFlipbook resets flipbook's timeline position to 0, so we have to set it back to where it was before
		AccumulatedTime = OldPosition;
		CalculateCurrentFrame();
	}
}

void UDirectionalFlipbookComponent::InstantiateAnimNotifies()
{
	CurrentNotifies.Empty();

	for (int32 Index = 0; Index < SourceDirectionalFlipbook->Notifies.Num(); Index++)
	{
		FAnimNotify2DTrigger NotifyTrigger = SourceDirectionalFlipbook->Notifies[Index];

		if (NotifyTrigger.NotifyClass != nullptr)
		{
			NotifyTrigger.InstancedNotify = NewObject<UAnimNotify2D>(this, NotifyTrigger.NotifyClass);
			CurrentNotifies.Add(NotifyTrigger);
		}
	}
}

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "PaperFlipbookComponent.h"
#include "DirectionalFlipbookDataAsset.h"
#include "DirectionalFlipbookComponent.generated.h"

USTRUCT(BlueprintType)
struct FInstancedAnimNotify2D
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Time;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAnimNotify2D* InstancedNotify;

	//Setting instanced notify class
	void SetNotify(UAnimNotify2D* NewNotify) {
		InstancedNotify = NewNotify;
	}

	//Constructor
	FInstancedAnimNotify2D()
	{
		InstancedNotify = nullptr;
		Time = 0.0f;
	}

	FInstancedAnimNotify2D(UAnimNotify2D* NewNotify, float NewTime)
	{
		InstancedNotify = NewNotify;
		Time = NewTime;
	}
};

/**
 *  Directional Flipbook Component
 */
UCLASS(ShowCategories = (Mobility, ComponentReplication), ClassGroup = Paper2D, meta = (BlueprintSpawnableComponent))
class REDRIDINGHOOD_API UDirectionalFlipbookComponent : public UPaperFlipbookComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(Category = Sprite, EditAnywhere, BlueprintReadWrite)
	bool bUseCustomRotation = false;

	UPROPERTY(Category = Sprite, EditAnywhere, BlueprintReadWrite)
	FRotator CustomRotation;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float SpriteAngle = 0.0f;

	UFUNCTION(BlueprintCallable)
	void SetDirectionalFlipbook(UDirectionalFlipbookDataAsset* NewDirectionalFlipbook);


protected:

	UPROPERTY(Category = Sprite, EditAnywhere, meta = (DisplayThumbnail = "true"))
	UDirectionalFlipbookDataAsset* SourceDirectionalFlipbook;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<FInstancedAnimNotify2D> CurrentNotifies;

private:

	bool bAnimNotifiesActivated = false;

public:

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	void GetAnimNotifiesFromDeltaPositions(const float& PreviousPosition, const float& CurrentPosition, TArray<UAnimNotify2D*>& OutAnimNotifies) const;

#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e);

#endif

protected:

	void FacePlayerCamera();
	void UpdateFlipbookDirection();
	void InstantiateAnimNotifies();

};

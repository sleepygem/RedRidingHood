#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "PaperFlipbookComponent.h"
#include "DirectionalFlipbookDataAsset.h"
#include "DirectionalFlipbookComponent.generated.h"

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

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<FAnimNotify2DTrigger> GetCurrentNotifies() const;

protected:

	UPROPERTY(Category = Sprite, EditAnywhere, meta = (DisplayThumbnail = "true"))
	UDirectionalFlipbookDataAsset* SourceDirectionalFlipbook;

	UPROPERTY()
	TArray<FAnimNotify2DTrigger> CurrentNotifies;

public:

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	void GetAnimNotifiesFromDeltaPositions(const float& PreviousPosition, const float& CurrentPosition, TArray<UAnimNotify2D*>& OutAnimNotifies) const;

protected:

	void FacePlayerCamera();
	void UpdateFlipbookDirection();
	void InstantiateAnimNotifies();
};

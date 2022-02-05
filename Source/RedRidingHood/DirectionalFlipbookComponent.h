#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "PaperFlipbookComponent.h"
#include "DirectionalFlipbookDataAsset.h"
#include "DirectionalFlipbookComponent.generated.h"

/**
 * 
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

protected:

	UPROPERTY(Category = Sprite, EditAnywhere, meta = (DisplayThumbnail = "true"))
	UDirectionalFlipbookDataAsset* SourceDirectionalFlipbook;

public:

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	void FacePlayerCamera();
	void UpdateFlipbookDirection();
};

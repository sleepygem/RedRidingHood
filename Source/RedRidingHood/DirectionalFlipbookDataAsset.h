// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PaperFlipbook.h"
#include "AnimNotify2D.h"
#include "DirectionalFlipbookDataAsset.generated.h"


UENUM(BlueprintType)
enum class EDirectionalType : uint8 {
	OneDirectional		UMETA(DisplayName = "One Directional"),
	TwoDirectional		UMETA(DisplayName = "Two Directional"),
	FourDirectional		UMETA(DisplayName = "Four Directional"),
	EightDirectional	UMETA(DisplayName = "Eight Directional")
};

USTRUCT(BlueprintType)
struct FAnimNotify2DTrigger
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Time;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UAnimNotify2D> NotifyClass;

	//Constructor
	FAnimNotify2DTrigger() 
	{
		Time = 0.0f;
	}
};


/**
 *  Directional Flipbook Asset
 */
UCLASS(BlueprintType)
class REDRIDINGHOOD_API UDirectionalFlipbookDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UPaperFlipbook*> Flipbooks;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EDirectionalType DirectionType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAnimNotify2DTrigger> Notifies;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	UPaperFlipbook* GetFlipbookFromAngle(float InAngle) const;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool Looping;

private:
	
	uint32 SpriteIndexFromAngle(float InAngle) const;
};

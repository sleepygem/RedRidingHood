// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
//#include "DirectionalFlipbookDataAsset.h"
#include "AnimNotify2D.generated.h"

class UDirectionalFlipbookAsset;

/**
 * 
 */
UCLASS(abstract, Blueprintable)
class REDRIDINGHOOD_API UAnimNotify2D : public UObject
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintImplementableEvent)
	bool Received_Notify(UDirectionalFlipbookDataAsset* DirectionalFlipbook);

	void Notify(UDirectionalFlipbookDataAsset* DirectionalFlipbook);
};

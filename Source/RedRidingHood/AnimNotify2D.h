// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
//#include "DirectionalFlipbookDataAsset.h"
#include "AnimNotify2D.generated.h"

class UDirectionalFlipbookComponent;

/**
 * 
 */
UCLASS(abstract, Blueprintable)
class REDRIDINGHOOD_API UAnimNotify2D : public UObject
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintImplementableEvent)
	void Received_Notify(UDirectionalFlipbookComponent* DirectionalFlipbook);

	void Notify(UDirectionalFlipbookComponent* DirectionalFlipbook);
};

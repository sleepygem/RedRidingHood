// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectionalFlipbookDataAsset.h"

UPaperFlipbook* UDirectionalFlipbookDataAsset::GetFlipbookFromAngle(float InAngle) const
{
	if (Flipbooks.Num() > 0) 
	{
		return Flipbooks[SpriteIndexFromAngle(InAngle)];
	}
	
	return nullptr;
}

uint32 UDirectionalFlipbookDataAsset::SpriteIndexFromAngle(float InAngle) const
{
	if (Flipbooks.Num() > 1) 
	{
		return FMath::RoundToInt(InAngle / (360.0f / Flipbooks.Num())) % Flipbooks.Num();
	}
	
	return 0;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectionalFlipbookDataAsset.h"

UPaperFlipbook* UDirectionalFlipbookDataAsset::GetFlipbookFromAngle(float InAngle) const
{
	return Flipbooks[SpriteIndexFromAngle(InAngle)];
}


void UDirectionalFlipbookDataAsset::GetAnimNotifiesFromDeltaPositions(const float& PreviousPosition, const float& CurrentPosition, TArray<TSubclassOf<class UAnimNotify2D>> &OutAnimNotifies) const
{
	if ((Notifies.Num() == 0) || (PreviousPosition == CurrentPosition))
	{
		return;
	}

	for (int NotifyIndex = 0; NotifyIndex < Notifies.Num(); NotifyIndex++) {

		const FAnimNotify2DTrigger& CurrentNotify = Notifies[NotifyIndex];

		if (CurrentNotify.Time > PreviousPosition && CurrentNotify.Time <= CurrentPosition) {
			OutAnimNotifies.Add(CurrentNotify.NotifyClass->StaticClass());//idk what, we're passing the notify class to be constructed in the array? look into what emplace does idk
		}

	}

}

uint32 UDirectionalFlipbookDataAsset::SpriteIndexFromAngle(float InAngle) const
{
	switch (DirectionType) {

	case EDirectionalType::OneDirectional:
		return 0;

	case EDirectionalType::TwoDirectional:

		return FMath::RoundToInt(InAngle / 180.0f) % 2;

	case EDirectionalType::FourDirectional:

		return FMath::RoundToInt(InAngle / 90.0f) % 4;

	case EDirectionalType::EightDirectional:

		return FMath::RoundToInt(InAngle / 45.0f) % 8;
	}

	return 0;
}

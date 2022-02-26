// Fill out your copyright notice in the Description page of Project Settings.


#include "NightWorldStreamingManager.h"

// Sets default values
ANightWorldStreamingManager::ANightWorldStreamingManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANightWorldStreamingManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANightWorldStreamingManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<FString> ANightWorldStreamingManager::GetStreamingLevelNames() const
{
	TArray<ULevelStreaming*> StreamingLevels = GetWorld()->GetStreamingLevels();

	TArray<FString> LevelNames;
	
	for (int32 i = 0; i < StreamingLevels.Num(); i++) {

		FString Level = FPackageName::GetShortName(StreamingLevels[i]->GetWorldAssetPackageFName());
		Level.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

		LevelNames.Add(Level);
	}

	return LevelNames;
}

TArray<ULevelStreaming*> ANightWorldStreamingManager::GetStreamingLevels() const
{
	return GetWorld()->GetStreamingLevels();
}

FString ANightWorldStreamingManager::GetStreamingPrefix() const
{
	return GetWorld()->StreamingLevelsPrefix;
}


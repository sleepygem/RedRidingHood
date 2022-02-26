// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Engine/LevelStreaming.h"
#include "Misc/PackageName.h"
#include "NightWorldStreamingManager.generated.h"

UCLASS()
class REDRIDINGHOOD_API ANightWorldStreamingManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANightWorldStreamingManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<FString> GetStreamingLevelNames() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<ULevelStreaming*> GetStreamingLevels() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FString GetStreamingPrefix() const;
};

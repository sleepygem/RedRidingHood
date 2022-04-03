// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FSMState.generated.h"

class UPlayerStateMachine;

/**
 * 
 */
UCLASS(abstract, Blueprintable)
class REDRIDINGHOOD_API UFSMState : public UObject
{
	GENERATED_BODY()
	

public:

	UPROPERTY(BlueprintReadOnly)
	UPlayerStateMachine* StateMachineOwner;

	UFUNCTION(BlueprintNativeEvent)
	void OnEnter();

	UFUNCTION(BlueprintNativeEvent)
	void OnExit();

	UFUNCTION(BlueprintNativeEvent)
	void OnReEnter();

	UFUNCTION(BlueprintNativeEvent)
	void Update(float DeltaTime);

	UFUNCTION(BlueprintNativeEvent)
	void HandleActionInput(FName InputName, EInputEvent InputType);

	UFUNCTION(BlueprintNativeEvent)
	void HandleAxisInput(FName AxisName, float AxisValue);

	UFUNCTION(BlueprintNativeEvent)
	void HandleDamage(AActor* SourceActor, float IncomingDamage, FVector Knockback);

#if WITH_ENGINE
	virtual class UWorld* GetWorld() const override;

#endif
};

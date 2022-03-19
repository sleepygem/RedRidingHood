// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FSMState.h"
#include "PlayerStateMachine.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REDRIDINGHOOD_API UPlayerStateMachine : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerStateMachine();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UFSMState*> StateStack;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UFUNCTION(BlueprintCallable)
	void PopState();
	
	UFUNCTION(BlueprintCallable)
	void PushState(TSubclassOf<class UFSMState> NewState);
	
	UFUNCTION(BlueprintCallable)
	void SetState(TSubclassOf<class UFSMState> NewState);

	UFUNCTION(BlueprintCallable)
	void HandleActionInput(FName InputName, EInputEvent InputType);
	
	UFUNCTION(BlueprintCallable)
	void HandleAxisInput(FName AxisName, float AxisValue);

	UFUNCTION(BlueprintCallable)
	void HandleDamage(AActor* SourceActor, float IncomingDamage, FVector Knockback);

	UFUNCTION(BlueprintPure, BlueprintCallable)
	UFSMState* GetCurrentState();


};

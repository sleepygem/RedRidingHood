// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStateMachine.h"

// Sets default values for this component's properties
UPlayerStateMachine::UPlayerStateMachine()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerStateMachine::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerStateMachine::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (UFSMState* State = StateStack.Last())
	{
		State->Update(DeltaTime);
	}
}

void UPlayerStateMachine::PopState()
{
	if (UFSMState* PreviousState = StateStack.Pop())
	{
		PreviousState->OnExit();
		PreviousState->MarkPendingKill();
	}

	if (StateStack.Num() > 0) 
	{
		StateStack.Last()->OnReEnter();
	}
}

void UPlayerStateMachine::PushState(TSubclassOf<class UFSMState> NewState)
{
	UFSMState* InstancedState = NewObject<UFSMState>(this, NewState);
	StateStack.Push(InstancedState);
	InstancedState->StateMachineOwner = this;
	InstancedState->OnEnter();
}

void UPlayerStateMachine::SetState(TSubclassOf<class UFSMState> NewState)
{
	PopState();
	PushState(NewState);
}

void UPlayerStateMachine::HandleActionInput(FName InputName, EInputEvent InputType)
{
	if (UFSMState* State = StateStack.Last())
	{
		State->HandleActionInput(InputName, InputType);
	}
}

void UPlayerStateMachine::HandleAxisInput(FName AxisName, float AxisValue)
{

	if (UFSMState* State = StateStack.Last())
	{
		State->HandleAxisInput(AxisName, AxisValue);
	}
}

void UPlayerStateMachine::HandleDamage(AActor* SourceActor, float IncomingDamage, FVector Knockback)
{
	if (UFSMState* State = StateStack.Last())
	{
		State->HandleDamage(SourceActor, IncomingDamage, Knockback);
	}
}

UFSMState* UPlayerStateMachine::GetCurrentState()
{
	return StateStack.Last();
}



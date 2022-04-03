// Fill out your copyright notice in the Description page of Project Settings.


#include "FSMState.h"

void UFSMState::OnEnter_Implementation()
{
}

void UFSMState::OnExit_Implementation()
{
}

void UFSMState::Update_Implementation(float DeltaTime)
{
}

void UFSMState::OnReEnter_Implementation() 
{
}

void UFSMState::HandleActionInput_Implementation(FName InputName, EInputEvent InputType)
{
}

void UFSMState::HandleAxisInput_Implementation(FName AxisName, float AxisValue)
{
}

void UFSMState::HandleDamage_Implementation(AActor* SourceActor, float IncomingDamage, FVector Knockback)
{
}

UWorld* UFSMState::GetWorld() const
{
	//Return null if the called from the CDO, or if the outer is being destroyed
	if (!HasAnyFlags(RF_ClassDefaultObject) && !GetOuter()->HasAnyFlags(RF_BeginDestroyed) && !GetOuter()->IsUnreachable())
	{
		//Try to get the world from the owning actor if we have one
		AActor* Outer = GetTypedOuter<AActor>();
		if (Outer != nullptr)
		{
			return Outer->GetWorld();
		}
	}
	//Else return null - the latent action will fail to initialize
	return nullptr;
}

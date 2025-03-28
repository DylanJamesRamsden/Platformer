// Fill out your copyright notice in the Description page of Project Settings.


#include "DBaseAttributeSet.h"

#include <Net/UnrealNetwork.h>

void UDBaseAttributeSet::OnRep_MaxJumpCharges(const FGameplayAttributeData& OldMaxJumpCharges)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxJumpCharges, OldMaxJumpCharges);
}

void UDBaseAttributeSet::OnRep_JumpCharges(const FGameplayAttributeData& OldJumpCharges)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, JumpCharges, OldJumpCharges);
}

void UDBaseAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxJumpCharges, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, JumpCharges, COND_None, REPNOTIFY_Always);
}

void UDBaseAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	if (Attribute == GetMaxJumpChargesAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxJumpCharges());
	}
	else if (Attribute == GetJumpChargesAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxJumpCharges());
	}
}

void UDBaseAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetJumpChargesAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxJumpCharges());
	}
}

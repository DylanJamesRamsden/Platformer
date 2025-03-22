// Fill out your copyright notice in the Description page of Project Settings.


#include "DPlayerState.h"

#include <AbilitySystemComponent.h>

#include "Platformer/AbilitySystem/DAbilitySet.h"

DEFINE_LOG_CATEGORY(LogDPlayerState);

ADPlayerState::ADPlayerState()
{
	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComp");
}

void ADPlayerState::BeginPlay()
{
	Super::BeginPlay();

	ensure(AbilitySystemComp);

	if (AbilitySet)
	{
		// Instead of calling and referencing the Ability Set in the PS, might be better to handle it directly through the
		// AbilitySystemComp
		AbilitySet->GiveToAbilitySystem(AbilitySystemComp);
	}
	else
	{
		UE_LOG(LogDPlayerState, Warning, TEXT("AbilitySet not assigned resulting in no AbilitySet being set on the AbilitySystemComp."));
	}
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "DAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMER_API UDAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void AbilityInputTagTrigger(const FGameplayTag& inputTag, const bool bValue);
	
};

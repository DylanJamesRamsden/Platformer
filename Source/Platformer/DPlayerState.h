// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "DPlayerState.generated.h"

class UAbilitySystemComponent;
class UDAbilitySet;

DECLARE_LOG_CATEGORY_EXTERN(LogDPlayerState, Log, All);

/**
 * 
 */
UCLASS()
class PLATFORMER_API ADPlayerState : public APlayerState
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "AbilityComponent")
	UAbilitySystemComponent* AbilitySystemComp;

	UPROPERTY(EditDefaultsOnly, Category = "AbilityComponent")
	const UDAbilitySet* AbilitySet = nullptr;

public:

	ADPlayerState();

	/**
	 * Gets the Ability System Component of a player state. N.B! Does not do any validation checks.
	 * @return The player state's Ability System Component.
	 */
	UAbilitySystemComponent* GetAbilitySystemComponent() { return AbilitySystemComp; }

protected:

	virtual void BeginPlay() override;
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <GameplayTagContainer.h>
#include <Engine/DataAsset.h>

#include "DInputConfig.generated.h"

class UInputAction;

USTRUCT()
struct FDTaggedInput
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	const UInputAction* InputAction = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Meta = (Categories = "Input"))
	FGameplayTag InputTag;
	
	bool IsValid() const;
};

// N.B! This class is used to assign Tagged and Ability Input Actions.

/**
 * 
 */
UCLASS(Const)
class PLATFORMER_API UDInputConfig : public UDataAsset
{
	GENERATED_BODY()

protected:

	// Input actions that apply a tag when triggered
	UPROPERTY(EditDefaultsOnly, Category = "Input", Meta = (TitleProperty = "InputAction"))
	TArray<FDTaggedInput> TaggedInputActions;

	// Abilities that are activated when an input action is triggered
	UPROPERTY(EditDefaultsOnly, Category = "Input", Meta = (TitleProperty = "InputAction"))
	TArray<FDTaggedInput> AbilityInputActions;
	
public:
	
	// Returns a input action for a given tag
	const UInputAction* FindInputActionForTag(const FGameplayTag& InputTag) const;

	// Returns all input actions
	TArray<const UInputAction*> GetInputActions() const;

	// Returns all ability actions
	TArray<FDTaggedInput> GetAbilityActions() const;
};

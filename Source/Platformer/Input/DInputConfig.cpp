// Fill out your copyright notice in the Description page of Project Settings.


#include "DInputConfig.h"

#include <InputAction.h>

bool FDTaggedInput::IsValid() const
{
	return InputAction->IsValidLowLevelFast() && InputTag.IsValid();
}

const UInputAction* UDInputConfig::FindInputActionForTag(const FGameplayTag& InputTag) const
{
	for (const FDTaggedInput& taggedInputAction : TaggedInputActions)
	{
		if (taggedInputAction.InputAction && taggedInputAction.InputTag == InputTag)
		{
			return taggedInputAction.InputAction;
		}
	}

	return nullptr;
}

TArray<const UInputAction*> UDInputConfig::GetInputActions() const
{
	TArray<const UInputAction*> inputActions;

	for (const FDTaggedInput& taggedInput : TaggedInputActions)
	{
		inputActions.Add(taggedInput.InputAction);
	}

	for (const FDTaggedInput& taggedInput : AbilityInputActions)
	{
		inputActions.Add(taggedInput.InputAction);
	}

	inputActions.Shrink();

	return inputActions;
}

TArray<FDTaggedInput> UDInputConfig::GetAbilityActions() const
{
	return AbilityInputActions;
}
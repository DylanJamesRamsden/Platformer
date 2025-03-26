// Fill out your copyright notice in the Description page of Project Settings.


#include "DEnhancedInputComponent.h"

// @TODO Move to specific GameplayTag C++ class
UE_DEFINE_GAMEPLAY_TAG(Input_Native_Move, "Input.Native.Move");

bool UDEnhancedInputComponent::UnbindAction(const UInputAction* inputAction)
{
	for (const TUniquePtr<FEnhancedInputActionEventBinding>& actionBinding : GetActionEventBindings())
	{
		if (actionBinding->GetAction() == inputAction)
		{
			return RemoveBindingByHandle(actionBinding->GetHandle());
		}
	}

	return false;
}

bool UDEnhancedInputComponent::UnbindActionByTag(const UDInputConfig* inputConfig, const FGameplayTag& inputTag)
{
	if (inputConfig && inputTag.IsValid())
	{
		if (const UInputAction* inputAction = inputConfig->FindInputActionForTag(inputTag))
		{
			return UnbindAction(inputAction);
		}
	}

	return false;
}

void UDEnhancedInputComponent::UnbindAllActions(const UDInputConfig* inputConfig)
{
	if (inputConfig)
	{
		if (!inputConfig->GetInputActions().IsEmpty())
		{
			for (const UInputAction* inputAction : inputConfig->GetInputActions())
			{
				UnbindAction(inputAction);
			}
		}
	}
}

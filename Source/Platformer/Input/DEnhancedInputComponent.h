// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <EnhancedInputComponent.h>

#include <NativeGameplayTags.h>

#include "DInputConfig.h"

#include "DEnhancedInputComponent.generated.h"

// @TODO Move to specific GameplayTag C++ class
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Native_Move);

/**
 * 
 */
UCLASS()
class PLATFORMER_API UDEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	
	/** */
	template<class UserClass, typename FuncType>
	void BindActionByTag(const UDInputConfig* inputConfig, const FGameplayTag& inputTag, ETriggerEvent triggerEvent, UserClass* object, FuncType func);

	/** */
	template<class UserClass, typename FuncType>
	void BindAbilityByTag(const UDInputConfig* inputConfig, UserClass* object, FuncType func);

	/** */
	bool UnbindAction(const UInputAction* inputAction);

	/** */
	bool UnbindActionByTag(const UDInputConfig* inputConfig, const FGameplayTag& inputTag);

	/** */
	void UnbindAllActions(const UDInputConfig* inputConfig);
};

template<class UserClass, typename FuncType>
void UDEnhancedInputComponent::BindActionByTag(const UDInputConfig* inputConfig, const FGameplayTag& inputTag, ETriggerEvent triggerEvent, UserClass* object, FuncType func)
{
	if (inputConfig && inputTag.IsValid())
	{
		if (const UInputAction* inputAction = inputConfig->FindInputActionForTag(inputTag))
		{
			BindAction(inputAction, triggerEvent, object, func);
		}
	}
}

template<class UserClass, typename FuncType>
void UDEnhancedInputComponent::BindAbilityByTag(const UDInputConfig* inputConfig, UserClass* object, FuncType func)
{
	check(inputConfig);

	for (const FDTaggedInput& action : inputConfig->GetAbilityActions())
	{
		if (action.InputAction && action.InputTag.IsValid())
		{
			if (func)
			{
				BindAction(action.InputAction, ETriggerEvent::Started, object, func, action.InputTag, true);
				BindAction(action.InputAction, ETriggerEvent::Completed, object, func, action.InputTag, false);
			}
		}
	}
}

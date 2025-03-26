// Fill out your copyright notice in the Description page of Project Settings.


#include "DAbilitySystemComponent.h"

void UDAbilitySystemComponent::AbilityInputTagTrigger(const FGameplayTag& inputTag, const bool bValue)
{
	ABILITYLIST_SCOPE_LOCK();

	if (inputTag.IsValid())
	{
		for (FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items)
		{
			if (AbilitySpec.Ability)
			{
				if (AbilitySpec.DynamicAbilityTags.HasTagExact(inputTag))
				{
					const bool bWasPressed = AbilitySpec.InputPressed;
					AbilitySpec.InputPressed = bValue;

					const bool bTryActivation = !AbilitySpec.IsActive() && (bValue);
					if (bTryActivation)
					{
						TryActivateAbility(AbilitySpec.Handle);
					}
					else if (bWasPressed != AbilitySpec.InputPressed)
					{
						const bool bSendServerEvents = (AbilitySpec.Ability->bReplicateInputDirectly && IsOwnerActorAuthoritative() == false);
						if (AbilitySpec.InputPressed)
						{
							if (bSendServerEvents)
							{
								ServerSetInputPressed(AbilitySpec.Handle);
							}

							AbilitySpecInputPressed(AbilitySpec);
							InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, AbilitySpec.Handle, AbilitySpec.ActivationInfo.GetActivationPredictionKey());
						}
						else
						{
							if (bSendServerEvents)
							{
								ServerSetInputReleased(AbilitySpec.Handle);
							}

							AbilitySpecInputReleased(AbilitySpec);
							InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased, AbilitySpec.Handle, AbilitySpec.ActivationInfo.GetActivationPredictionKey());
						}
					}
				}
			}
		}
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "DAbilitySet.h"

#include <AbilitySystemComponent.h>
#include <Abilities/GameplayAbility.h>

DEFINE_LOG_CATEGORY(LogDAbilitySystem);

void UDAbilitySet::GiveToAbilitySystem(UAbilitySystemComponent* AbilitySystem, UObject* SourceObject) const
{
	// We are just building a standalone game, so this isn't required
	// if (!abilitySystem->IsOwnerActorAuthoritative())
	// {
	// 	return;
	// }

	// Grant the attribute sets.
	for (int32 SetIndex = 0; SetIndex < GrantedAttributes.Num(); ++SetIndex)
	{
		const FAttributeDefaults& SetToGrant = GrantedAttributes[SetIndex];

		if (!IsValid(SetToGrant.Attributes))
		{
			UE_LOG(LogDAbilitySystem, Error, TEXT("GrantedAttributeSet[%d] on ability set [%s] is not valid"), SetIndex, *GetNameSafe(this));
			continue;
		}

		if (!SetToGrant.DefaultStartingTable)
		{
			UE_LOG(LogDAbilitySystem, Error, TEXT("DefaultStartingTable for GrantedAttributes[%d] on ability set [%s] is not valid"), SetIndex, *GetNameSafe(this));
			continue;
		}

		UAttributeSet* NewSet = NewObject<UAttributeSet>(AbilitySystem->GetOwner(), SetToGrant.Attributes);
		NewSet->InitFromMetaDataTable(SetToGrant.DefaultStartingTable);
		AbilitySystem->AddSpawnedAttribute(NewSet);
	}

	// Grant the gameplay abilities.
	for (int32 AbilityIndex = 0; AbilityIndex < GrantedGameplayAbilities.Num(); ++AbilityIndex)
	{
		const FDGameplayAbility_GameplayAbility& AbilityToGrant = GrantedGameplayAbilities[AbilityIndex];

		if (!IsValid(AbilityToGrant.Ability))
		{
			UE_LOG(LogDAbilitySystem, Error, TEXT("GrantedGameplayAbilities[%d] on ability set [%s] is not valid."), AbilityIndex, *GetNameSafe(this));
			continue;
		}

		UGameplayAbility* AbilityCDO = AbilityToGrant.Ability->GetDefaultObject<UGameplayAbility>();

		FGameplayAbilitySpec AbilitySpec(AbilityCDO, AbilityToGrant.AbilityLevel);
		AbilitySpec.SourceObject = SourceObject;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilityToGrant.InputTag);

		FGameplayAbilitySpecHandle AbilitySpecHandle = AbilitySystem->GiveAbility(AbilitySpec);
	}
}

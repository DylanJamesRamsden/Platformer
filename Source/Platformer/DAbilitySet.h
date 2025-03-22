// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <Engine/DataAsset.h>
#include <GameplayTags.h>

#include "DAbilitySet.generated.h"

class UAbilitySystemComponent;
class UGameplayAbility;
class UAttributeSet;
class UGameplayEffect;
struct FAttributeDefaults;

DECLARE_LOG_CATEGORY_EXTERN(LogDAbilitySystem, Log, All);

USTRUCT(BlueprintType)
struct FDGameplayAbility_GameplayAbility
{
	GENERATED_BODY()

public:
	// Gameplay ability to grant.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayAbility> Ability = nullptr;

	// Level of ability to grant.
	UPROPERTY(EditDefaultsOnly)
	int32 AbilityLevel = 1;

	// Tag used to process input for the ability.
	UPROPERTY(EditDefaultsOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
};

USTRUCT(BlueprintType)
struct FDGameplayEffect_GameplayEffect
{
	GENERATED_BODY()

public:
	// Gameplay effect to grant.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> GameplayEffect = nullptr;

	// Level of gameplay effect to grant.
	UPROPERTY(EditDefaultsOnly)
	float EffectLevel = 1.0f;
};

/**
 * 
 */
UCLASS()
class PLATFORMER_API UDAbilitySet : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	void GiveToAbilitySystem(UAbilitySystemComponent* AbilitySystem, UObject* SourceObject = nullptr) const;
	
protected:
	// Gameplay abilities to grant when this ability set is granted.
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities", meta = (TitleProperty = Ability))
	TArray<FDGameplayAbility_GameplayAbility> GrantedGameplayAbilities;

	// Attribute sets to grant when this ability set is granted.
	UPROPERTY(EditDefaultsOnly, Category = "Attribute Sets")
	TArray<FAttributeDefaults> GrantedAttributes;
};

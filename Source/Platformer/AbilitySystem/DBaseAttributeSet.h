// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <AbilitySystemComponent.h>
#include <AttributeSet.h>

#include "DBaseAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class PLATFORMER_API UDBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxJumpCharges)
	FGameplayAttributeData MaxJumpCharges;
	ATTRIBUTE_ACCESSORS(UDBaseAttributeSet, MaxJumpCharges);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_JumpCharges)
	FGameplayAttributeData JumpCharges;
	ATTRIBUTE_ACCESSORS(UDBaseAttributeSet, JumpCharges);

protected:

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	UFUNCTION()
	virtual void OnRep_MaxJumpCharges(const FGameplayAttributeData& OldMaxJumpCharges);
	
	UFUNCTION()
	virtual void OnRep_JumpCharges(const FGameplayAttributeData& OldJumpCharges);
	
};

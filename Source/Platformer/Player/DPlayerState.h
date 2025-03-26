// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <GameFramework/PlayerState.h>
#include <AbilitySystemInterface.h>

#include "Platformer/AbilitySystem/DAbilitySystemComponent.h"

#include "DPlayerState.generated.h"

class UDAbilitySet;

DECLARE_LOG_CATEGORY_EXTERN(LogDPlayerState, Log, All);

/**
 * 
 */
UCLASS()
class PLATFORMER_API ADPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "AbilityComponent")
	UDAbilitySystemComponent* AbilitySystemComp;

	UPROPERTY(EditDefaultsOnly, Category = "AbilityComponent")
	const UDAbilitySet* AbilitySet = nullptr;

public:

	ADPlayerState();

protected:

	virtual void BeginPlay() override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComp; }
	
};

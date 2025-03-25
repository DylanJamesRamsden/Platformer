// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <GameFramework/Character.h>

#include "DHumanoidCharacter.generated.h"

class UDHeroComponent;

UCLASS()
class PLATFORMER_API ADHumanoidCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDHeroComponent* HeroComp;

public:
	// Sets default values for this character's properties
	ADHumanoidCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};

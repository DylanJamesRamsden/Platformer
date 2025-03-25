// Fill out your copyright notice in the Description page of Project Settings.


#include "DHumanoidCharacter.h"

#include "DHeroComponent.h"

// Sets default values
ADHumanoidCharacter::ADHumanoidCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	HeroComp = CreateDefaultSubobject<UDHeroComponent>("HeroComponent");
}

// Called when the game starts or when spawned
void ADHumanoidCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


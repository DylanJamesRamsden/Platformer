// Fill out your copyright notice in the Description page of Project Settings.


#include "DHumanoidCharacter.h"

#include <AbilitySystemGlobals.h>
#include <EnhancedInputSubsystems.h>
#include <GameFramework/CharacterMovementComponent.h>

#include "Platformer/AbilitySystem/DAbilitySystemComponent.h"
#include "Platformer/Input/DEnhancedInputComponent.h"
#include "Platformer/Input/DInputData.h"
#include "Platformer/Utility/DGameplayTags.h"

DEFINE_LOG_CATEGORY(LogDHumanoidCharacter);

ADHumanoidCharacter::ADHumanoidCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	OverrideInputComponentClass = UDEnhancedInputComponent::StaticClass();
	
}

void ADHumanoidCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UDEnhancedInputComponent* enhancedInputComp = Cast<UDEnhancedInputComponent>(PlayerInputComponent);
	if (!enhancedInputComp)
	{
		UE_LOG(LogDHumanoidCharacter, Error, TEXT("%s: %s failed to initialize Input Data because Humanoid Character is not using a DEnhancedInputComponent.")
			, ANSI_TO_TCHAR(__FUNCTION__), *this->GetName());
	}

	if (InputData)
	{
		APlayerController* playerController = Cast<APlayerController>(GetController());
		if (playerController)
		{
			UEnhancedInputLocalPlayerSubsystem* newLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());
			if (newLocalPlayerSubsystem)
			{
				newLocalPlayerSubsystem->AddMappingContext(InputData->GetMappingContext(), 1);

				enhancedInputComp->BindActionByTag(InputData->GetInputConfig(), Input_Native_Move, ETriggerEvent::Triggered, this, &ThisClass::Move);
				
				enhancedInputComp->BindAbilityByTag(InputData->GetInputConfig(), this, &ThisClass::AbilityInputTrigger);

				UE_LOG(LogDHumanoidCharacter, Log, TEXT("EnhancedInputComponent initialized on %s."), *this->GetName());
			}
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, GetName() + " has no assigned DInputData!");
		
		UE_LOG(LogDHumanoidCharacter, Error, TEXT("%s: %s failed to initialize Input Data because there is no assigned DInputData.")
			, ANSI_TO_TCHAR(__FUNCTION__), *this->GetName());
	}
}

// Called when the game starts or when spawned
void ADHumanoidCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADHumanoidCharacter::AbilityInputTrigger(const FGameplayTag InputTag, const bool bValue)
{
	if (const auto abilitySystemComponent = Cast<UDAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(this)))
	{
		abilitySystemComponent->AbilityInputTagTrigger(InputTag, bValue);
	}
}

void ADHumanoidCharacter::Move(const FInputActionValue& inputActionValue)
{
#if WITH_EDITOR
	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Yellow, "Movement Velocity: " + GetCharacterMovement()->Velocity.ToString());
#endif
	
	AddMovementInput(FVector::ForwardVector, inputActionValue.Get<float>());
}


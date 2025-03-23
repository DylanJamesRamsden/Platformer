// Fill out your copyright notice in the Description page of Project Settings.


#include "DHeroComponent.h"

#include <GameplayTagContainer.h>
#include <EnhancedInputSubsystems.h>
#include <AbilitySystemGlobals.h>

#include "DAbilitySystemComponent.h"
#include "DEnhancedInputComponent.h"
#include "DInputData.h"

DEFINE_LOG_CATEGORY(LogDHeroComponent);

// Sets default values for this component's properties
UDHeroComponent::UDHeroComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	bAutoActivate = true;

	InputData = nullptr;	
	OwningPawn = nullptr;
	OwningController = nullptr;	
	bNeedsInputUpdate = false;
}

void UDHeroComponent::OnRegister()
{
	Super::OnRegister();

	Super::OnRegister();

	if (!GetOuter())
	{
		UE_LOG(LogDHeroComponent, Error, TEXT("%s: %s failed to register because component Outer is invalid."), ANSI_TO_TCHAR(__FUNCTION__), *this->GetName());
	}

	OwningPawn = CastChecked<APawn>(GetOuter());
	if (OwningPawn)
	{
		// In the case of the component being added in runtime at a point the pawn was already possessed.
		if (OwningPawn->GetController())
		{
			OnOwnerControllerChanged(OwningPawn, OwningPawn->GetController(), nullptr);
		}

		OwningPawn->ReceiveControllerChangedDelegate.AddUniqueDynamic(this, &ThisClass::OnOwnerControllerChanged);

		OwningPawn->OnEndPlay.AddUniqueDynamic(this, &ThisClass::OwnerEndPlay);
	}
	else
	{
		UE_LOG(LogDHeroComponent, Error, TEXT("%s: %s failed to register because owner is not a Pawn."), ANSI_TO_TCHAR(__FUNCTION__), *this->GetName());
	}
}


// Called when the game starts
void UDHeroComponent::BeginPlay()
{
	Super::BeginPlay();

	if (InputData->IsValidLowLevelFast() && bNeedsInputUpdate && OwningController.IsValid())
	{
		UpdatePlayerInput(nullptr, Cast<APlayerController>(OwningController.Get()));
	}
}

void UDHeroComponent::OwnerEndPlay(AActor* Actor, EEndPlayReason::Type EndPlayReason)
{
}

void UDHeroComponent::OnOwnerControllerChanged(APawn* Pawn, AController* OldController, AController* NewController)
{
	if (OldController)
	{
		bNeedsInputUpdate = true;
	}

	if (NewController)
	{
		OwningController = NewController;
		bNeedsInputUpdate = true;
	}
	else if (OwningController.IsValid())
	{
		OwningController.Reset();
	}

	APlayerController* oldPlayerController = Cast<APlayerController>(OldController);
	if (!oldPlayerController)
	{
		UE_LOG(LogDHeroComponent, Error, TEXT("%s: %s failed to update player input, OldController is not a PlayerController."), ANSI_TO_TCHAR(__FUNCTION__), *this->GetName());
		return;
	}
	
	APlayerController* newPlayerController = Cast<APlayerController>(NewController);
	if (!newPlayerController)
	{
		UE_LOG(LogDHeroComponent, Error, TEXT("%s: %s failed to update player input, NewController is not a PlayerController."), ANSI_TO_TCHAR(__FUNCTION__), *this->GetName());
		return;
	}

	if (bNeedsInputUpdate)
	{
		UpdatePlayerInput(oldPlayerController, newPlayerController);
		bNeedsInputUpdate = false;
	}
}

void UDHeroComponent::UpdatePlayerInput(APlayerController* OldPlayerController, APlayerController* NewPlayerController)
{
	UEnhancedInputLocalPlayerSubsystem* oldLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(OldPlayerController->GetLocalPlayer());
	if (!oldLocalPlayerSubsystem)
	{
		UE_LOG(LogDHeroComponent, Error, TEXT("%s: %s failed to update player input, failed to get LocalPlayerSubsystem from OldPlayerController."), ANSI_TO_TCHAR(__FUNCTION__), *this->GetName());
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* newLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(NewPlayerController->GetLocalPlayer());
	if (!newLocalPlayerSubsystem)
	{
		UE_LOG(LogDHeroComponent, Error, TEXT("%s: %s failed to update player input, failed to get LocalPlayerSubsystem from NewPlayerController."), ANSI_TO_TCHAR(__FUNCTION__), *this->GetName());
		return;
	}

	RegisterMappingContext(oldLocalPlayerSubsystem, newLocalPlayerSubsystem);
	RegisterInputActions(OldPlayerController, NewPlayerController);
}

void UDHeroComponent::RegisterMappingContext(UEnhancedInputLocalPlayerSubsystem* OldLocalPlayerSubsystem,
	UEnhancedInputLocalPlayerSubsystem* NewLocalPlayerSubsystem) const
{
	if (const UInputMappingContext* InputMappingContext = InputData->GetMappingContext())
	{
		if (OldLocalPlayerSubsystem)
		{
			OldLocalPlayerSubsystem->RemoveMappingContext(InputMappingContext);
		}

		if (NewLocalPlayerSubsystem)
		{
			NewLocalPlayerSubsystem->AddMappingContext(InputMappingContext, 1);
		}
	}
}

void UDHeroComponent::RegisterInputActions(APlayerController* OldPlayerController,
	APlayerController* NewPlayerController)
{
	if (OldPlayerController)
	{
		UnbindInputActions(Cast<UDEnhancedInputComponent>(OldPlayerController->InputComponent));
	}

	if (NewPlayerController)
	{
		BindInputActions(Cast<UDEnhancedInputComponent>(NewPlayerController->InputComponent));
	}
}

void UDHeroComponent::BindInputActions(UDEnhancedInputComponent* InputComponent)
{
	InputComponent->BindAbilityByTag(InputData->GetInputConfig(), this, &ThisClass::AbilityInputTrigger);
}

void UDHeroComponent::UnbindInputActions(UDEnhancedInputComponent* InputComponent) const
{
	if (InputComponent)
	{
		if (InputData && InputData->GetInputConfig())
		{
			InputComponent->UnbindAllActions(InputData->GetInputConfig());
		}
	}
}

void UDHeroComponent::AbilityInputTrigger(const FGameplayTag InputTag, const bool bValue)
{
	if (OwningPawn)
	{
		if (const auto abilitySystemComponent = Cast<UDAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OwningPawn)))
		{
			abilitySystemComponent->AbilityInputTagTrigger(InputTag, bValue);
		}
	}
}


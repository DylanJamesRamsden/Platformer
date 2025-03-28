// Fill out your copyright notice in the Description page of Project Settings.


#include "DHumanoidCharacter.h"

#include <AbilitySystemGlobals.h>
#include <EnhancedInputSubsystems.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>

#include "DPlayerState.h"
#include "Kismet/KismetMathLibrary.h"
#include "Platformer/AbilitySystem/DAbilitySystemComponent.h"
#include "Platformer/Input/DEnhancedInputComponent.h"
#include "Platformer/Input/DInputData.h"
#include "Platformer/Utility/DGameplayTags.h"

DEFINE_LOG_CATEGORY(LogDHumanoidCharacter);

ADHumanoidCharacter::ADHumanoidCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	OverrideInputComponentClass = UDEnhancedInputComponent::StaticClass();

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComponent");

	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp->SetupAttachment(SpringArmComp);

	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->CameraLagSpeed = 5.0f;
	SpringArmComp->SetRelativeRotation(FRotator(-10.0f, -90.0f, 0.0f));
	SpringArmComp->TargetArmLength = 1500.0f;
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

void ADHumanoidCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	Turn(DeltaSeconds);
}

void ADHumanoidCharacter::AbilityInputTrigger(const FGameplayTag InputTag, const bool bValue)
{
	// @TODO To be honest, we should just attach the ASC to the pawn rather than the PlayerState
	if (ADPlayerState* playerState = GetPlayerState<ADPlayerState>())
	{
		if (const auto abilitySystemComponent = Cast<UDAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(playerState)))
		{
			abilitySystemComponent->AbilityInputTagTrigger(InputTag, bValue);
		}
	}
}

void ADHumanoidCharacter::Move(const FInputActionValue& inputActionValue)
{
#if WITH_EDITOR
	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Yellow, "Movement Velocity: " + GetCharacterMovement()->Velocity.ToString());
#endif
	
	AddMovementInput(FVector::ForwardVector, inputActionValue.Get<float>());

	bIsTurning = true;
	TurnDirection = inputActionValue.Get<float>() > 0 ? ETurnDirection::Right : ETurnDirection::Left;
}

void ADHumanoidCharacter::Turn(float DeltaSeconds)
{
	if (bIsTurning)
	{
		FRotator meshRelativeRotation = GetMesh()->GetRelativeRotation();
		FRotator targetRotation = FRotator::ZeroRotator;

		switch (TurnDirection)
		{
			case Right:
				targetRotation = FRotator(meshRelativeRotation.Pitch, -90.0f, meshRelativeRotation.Roll);
				meshRelativeRotation = UKismetMathLibrary::RInterpTo(meshRelativeRotation, targetRotation, DeltaSeconds, 10.0f);

				GetMesh()->SetRelativeRotation(meshRelativeRotation);
				if (FMath::IsNearlyEqual(meshRelativeRotation.Yaw, -90.0f, .001f))
				{
					bIsTurning = false;
					TurnDirection = ETurnDirection::None;
				}
				break;
			case Left:
				targetRotation = FRotator(meshRelativeRotation.Pitch, 90.0f, meshRelativeRotation.Roll);
				meshRelativeRotation = UKismetMathLibrary::RInterpTo(meshRelativeRotation, targetRotation, DeltaSeconds, 10.0f);

				GetMesh()->SetRelativeRotation(meshRelativeRotation);
				if (FMath::IsNearlyEqual(meshRelativeRotation.Yaw, 90.0f, .001f))
				{
					bIsTurning = false;
					TurnDirection = ETurnDirection::None;
				}
				break;
		}
	}
}


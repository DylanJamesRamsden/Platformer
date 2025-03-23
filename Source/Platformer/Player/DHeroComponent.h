// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <Components/ActorComponent.h>

#include "DHeroComponent.generated.h"

class UEnhancedInputLocalPlayerSubsystem;
class UDInputData;
class UDEnhancedInputComponent;
class ACharacter;
class UAbilitySet;
class UAbilitySystemComponent;
struct FInputActionValue;
struct FGameplayTag;

DECLARE_LOG_CATEGORY_EXTERN(LogDHeroComponent, Log, All);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLATFORMER_API UDHeroComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	/** The Pawn that owns this component. */
	TObjectPtr<APawn> OwningPawn;

	/** The Controller of the owning Pawn. */
	TWeakObjectPtr<AController> OwningController;

	/** */
	uint8 bNeedsInputUpdate:1;

protected:

	/** Sets default values. */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	const UDInputData* InputData;

public:	
	// Sets default values for this component's properties
	UDHeroComponent();

protected:
	
	//~Begin UActorComponent implementation.
	virtual void OnRegister() override;
	virtual void BeginPlay() override;
	//~End UActorComponent implementation.

	UFUNCTION()
	void OwnerEndPlay(AActor* Actor, EEndPlayReason::Type EndPlayReason);

	/**
	 * Binded to ReceiveControllerChangedDelegate on the owning Pawn and it is called when the owning Pawn's controller changes.
	 * @param Pawn The Pawn whose Controller changed, this should be the same as the owning Pawn.
	 * @param OldController The Controller previously possessing the owning Pawn.
	 * @param NewController The new Controller possessing the owning Pawn.
	 */
	UFUNCTION()
	void OnOwnerControllerChanged(APawn* Pawn, AController* OldController, AController* NewController);

	/**
	 * Updates Player Input by registering inputs to a new controller and unregistering from a old controller.
	 * @param OldPlayerController The Player Controller that will have its inputs unregistered.
	 * @param NewPlayerController The Player Controller that will have its inputs registered.
	 */
	void UpdatePlayerInput(APlayerController* OldPlayerController, APlayerController* NewPlayerController);

	/**
	 * Updates Player Input by registering inputs to a new controller and unregistering from a old controller.
	 * @param OldLocalPlayerSubsystem The Player Controller that will have its inputs unregistered.
	 * @param NewLocalPlayerSubsystem The Player Controller that will have its inputs registered.
	 */
	void RegisterMappingContext(UEnhancedInputLocalPlayerSubsystem* OldLocalPlayerSubsystem, UEnhancedInputLocalPlayerSubsystem* NewLocalPlayerSubsystem) const;

	/** */
	void RegisterInputActions(APlayerController* OldPlayerController, APlayerController* NewPlayerController);

	/** */
	virtual void BindInputActions(UDEnhancedInputComponent* InputComponent);

	/** */
	void UnbindInputActions(UDEnhancedInputComponent* InputComponent) const;
	
	/** */
	void AbilityInputTrigger(const FGameplayTag InputTag, const bool bValue);
		
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <GameFramework/Character.h>

#include "DHumanoidCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UDInputData;

DECLARE_LOG_CATEGORY_EXTERN(LogDHumanoidCharacter, Log, All);

UCLASS()
class PLATFORMER_API ADHumanoidCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	const UDInputData* InputData = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;

public:
	// Sets default values for this character's properties
	ADHumanoidCharacter();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void AbilityInputTrigger(const FGameplayTag InputTag, const bool bValue);

	UFUNCTION()
	void Move(const FInputActionValue& inputActionValue);

};

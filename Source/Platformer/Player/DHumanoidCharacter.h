// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <GameFramework/Character.h>

#include "DHumanoidCharacter.generated.h"

UENUM()
enum ETurnDirection
{
	None,
	Right,
	Left
};

class UCameraComponent;
class USpringArmComponent;
class UDInputData;

DECLARE_LOG_CATEGORY_EXTERN(LogDHumanoidCharacter, Log, All);

UCLASS()
class PLATFORMER_API ADHumanoidCharacter : public ACharacter
{
	GENERATED_BODY()

private:

	// Turning
	bool bIsTurning = false;
	ETurnDirection TurnDirection = ETurnDirection::None;

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

	virtual void Tick(float DeltaSeconds) override;

private:

	UFUNCTION()
	void AbilityInputTrigger(const FGameplayTag InputTag, const bool bValue);

	UFUNCTION()
	void Move(const FInputActionValue& inputActionValue);

	// Interpolates the Character's Skeletal Mesh Relative Rotation to a rotation based on the direction of movement (TurnDirection)
	void Turn(float DeltaSeconds);

};

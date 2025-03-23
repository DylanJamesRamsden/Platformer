// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <Engine/DataAsset.h>

#include "DInputData.generated.h"

class UInputMappingContext;
class UDInputConfig;

/**
 * 
 */
UCLASS(Const)
class PLATFORMER_API UDInputData : public UPrimaryDataAsset
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMapping;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UDInputConfig> InputConfig;

public:
	// Returns the InputMapping
	const TObjectPtr<UInputMappingContext> GetMappingContext() const { return InputMapping; }

	// Returns the InputConfig
	const TObjectPtr<UDInputConfig> GetInputConfig() const { return InputConfig; }
};

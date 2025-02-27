// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TacticToolFunction.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class TACTIC_API UTacticToolFunction : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintPure,Category = "Screen")
	static void CalculateMouseAngleToCenter(FVector2D MousePos, FVector2D ScreenSize,float& Angle);

};

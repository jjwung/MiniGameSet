// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MePlayerController.generated.h"

/**
 * 玩家控制器
 */
UCLASS()
class TACTIC_API AMePlayerController : public APlayerController
{
	GENERATED_BODY()
	
	void BeginPlay() override;
	
};

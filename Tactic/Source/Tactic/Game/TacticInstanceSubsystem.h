// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TacticInstanceSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class TACTIC_API UTacticInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	TArray<APawn*> EnemyPawns;

public:
	/**
	 * 注册敌方NPC
	 * @param Pawn 要注册的敌方Pawn
	 */
	UFUNCTION(BlueprintCallable)
	void RegisterEnemyPawn(APawn* Pawn);

	/**
	 * 移除注册的NPC
	 * @param Pawn 要移除的敌方Pawn
	 */
	UFUNCTION(BlueprintCallable)
	void RemoveEnemyPawn(APawn* Pawn);

	/**
	 * 清空注册的敌方NPC
	 */
	UFUNCTION(BlueprintCallable)
	void ClearRegisterEnemyPawn();
};



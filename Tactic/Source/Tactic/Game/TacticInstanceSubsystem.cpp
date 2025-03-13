// Fill out your copyright notice in the Description page of Project Settings.


#include "TacticInstanceSubsystem.h"

void UTacticInstanceSubsystem::RegisterEnemyPawn(APawn* Pawn)
{
	EnemyPawns.Add(Pawn);
}

void UTacticInstanceSubsystem::RemoveEnemyPawn(APawn* Pawn)
{
	EnemyPawns.Remove(Pawn);
}

void UTacticInstanceSubsystem::ClearRegisterEnemyPawn()
{
	EnemyPawns.Empty();
}


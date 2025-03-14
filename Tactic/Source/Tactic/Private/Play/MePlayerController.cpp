// Fill out your copyright notice in the Description page of Project Settings.


#include "Tactic/Public/Play/MePlayerController.h"

#include "Blueprint/WidgetLayoutLibrary.h"

void AMePlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 设置游戏模式InputModeGameAndUI
	FInputModeGameAndUI InputModeData;
	InputModeData.SetWidgetToFocus(nullptr); // InWidgetToFocus不传
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); // InMouseLockMode为不锁定
	InputModeData.SetHideCursorDuringCapture(false); // hideCursorDuringCapture为false
	this->SetInputMode(InputModeData);
	this->bShowMouseCursor = true;
}



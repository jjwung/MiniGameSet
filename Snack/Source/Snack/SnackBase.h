// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SnackBase.generated.h"

UCLASS(Blueprintable)
class SNACK_API ASnackBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASnackBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	//UPROPERTY(BlueprintReadWrite)
	TQueue<FTransform> SnackBodyTransform;

	TLinkedList<FTransform>* FirstTransformNode;
	
	TLinkedList<FTransform>* CurrentTransformNode;
	
public:
	UFUNCTION(BlueprintCallable)
	FTransform NextNode();
	UFUNCTION(BlueprintCallable)
	FTransform NextNode2();
	UFUNCTION(BlueprintCallable)
	FTransform NextNode3();

	UFUNCTION(BlueprintCallable)
	void AddNode(FTransform Transform);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FTransform FindBodyTransform(ASnackBodyBase* SnackBodyBase);
	
	UFUNCTION(BlueprintCallable)
	void InitTransformNode();

	UFUNCTION(BlueprintCallable)
	FTransform GetFirstTransform();
	
	void RemoveLinkNode(ASnackBodyBase* SnackBodyBase);
	
};

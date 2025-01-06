// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SnackBase.generated.h"

class ContainerType;

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

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Speed = 1.f;
	
public:
	TLinkedList<FTransform>* NextNode(TLinkedList<FTransform>* Node);
	
	UFUNCTION(BlueprintCallable)
	FTransform NextNodeTransform();

	/** 第几个节点 */
	UFUNCTION(BlueprintCallable)
	FTransform CallNextNodeMutiSt(int Times, bool& Success);
	
	UFUNCTION(BlueprintCallable)
	void AddNode(FTransform Transform);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FTransform FindBodyTransform(ASnackBodyBase* SnackBodyBase, bool& Success);
	
	UFUNCTION(BlueprintCallable)
	void InitTransformNode();

	UFUNCTION(BlueprintCallable)
	FTransform GetFirstTransform();
	
	void RemoveLinkNode(ASnackBodyBase* SnackBodyBase);
	
};

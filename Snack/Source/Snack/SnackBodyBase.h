// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnackBodyBase.generated.h"

class ASnackBase;

UCLASS()
class SNACK_API ASnackBodyBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASnackBodyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	TDoubleLinkedList<FTransform>::TDoubleLinkedListNode* TransformNode;

	UPROPERTY(BlueprintReadWrite)
	ASnackBase* SnackBase;
	
public:
	UFUNCTION(BlueprintCallable)
	void InsideNext(bool& bSuccess);

	UFUNCTION(BlueprintCallable)
	void SetHeadNode(ASnackBodyBase* SnackBodyBase);

	UFUNCTION(BlueprintCallable)
	FTransform GetNodeTransform();
};


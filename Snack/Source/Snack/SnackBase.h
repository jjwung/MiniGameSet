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
	TDoubleLinkedList<FTransform>* DoubleLinkedList = new TDoubleLinkedList<FTransform>();
	
	TDoubleLinkedList<FTransform>::TDoubleLinkedListNode* FirstTransformNode;

	TDoubleLinkedList<FTransform>::TDoubleLinkedListNode* CurrentTransformNode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NodeSize;

public:
	TDoubleLinkedList<FTransform>::TDoubleLinkedListNode* NextNode(TDoubleLinkedList<FTransform>::TDoubleLinkedListNode* Node);
	TDoubleLinkedList<FTransform>::TDoubleLinkedListNode* PrevNode(TDoubleLinkedList<FTransform>::TDoubleLinkedListNode* Node);

	UFUNCTION(BlueprintCallable)
	FTransform NextNodeTransform(bool& Success);

	/** 获取从当前节点开始后的第N个节点的变换 */
	UFUNCTION(BlueprintCallable)
	FTransform SetNextTimesNode(int Times, ASnackBodyBase* SnackBodyBase, bool& Success);

	/** 获取从当前节点开始前的第N个节点的变换 */
	UFUNCTION(BlueprintCallable)
	bool SetPrevTimesNode(int Times, ASnackBodyBase* SnackBody);

	UFUNCTION(BlueprintCallable)
	void AddNode(FTransform Transform);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FTransform FindBodyTransform(ASnackBodyBase* SnackBodyBase, bool& Success);

	UFUNCTION(BlueprintCallable)
	void InitTransformNode();

	UFUNCTION(BlueprintCallable)
	FTransform GetFirstTransform();

	/**
	 * 截断链表，删除指定节点及其后面的节点
	 * @param Node 节点
	 * @param next 是：下一个节点，否：上一个节点
	 */
	void TruncateLinkedNode(TDoubleLinkedList<FTransform>::TDoubleLinkedListNode* Node, bool next = true);
};

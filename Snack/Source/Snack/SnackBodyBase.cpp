// Fill out your copyright notice in the Description page of Project Settings.


#include "SnackBodyBase.h"
#include "SnackBase.h"

// Sets default values
ASnackBodyBase::ASnackBodyBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASnackBodyBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASnackBodyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASnackBodyBase::InsideNext(bool& bSuccess)
{
	if (TransformNode)
	{
		TDoubleLinkedList<FTransform>::TDoubleLinkedListNode* TransformNodeNext = TransformNode->GetNextNode();
		if (TransformNodeNext)
		{
			TransformNode = TransformNodeNext;
			bSuccess = true;
			TDoubleLinkedList<FTransform>::TDoubleLinkedListNode* TransformNodePrev = TransformNodeNext->GetPrevNode();
			return;
		}
	}
	bSuccess = false;
}

void ASnackBodyBase::SetHeadNode(ASnackBodyBase* SnackBodyBase)
{
	if (SnackBodyBase)
	{
		TransformNode = SnackBodyBase->TransformNode;
	}
	else
	{
		TransformNode = SnackBase->CurrentTransformNode;
	}
}

FTransform ASnackBodyBase::GetNodeTransform()
{
	if (TransformNode)
	return TransformNode->GetValue();
	return FTransform();
}

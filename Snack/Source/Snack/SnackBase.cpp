// Fill out your copyright notice in the Description page of Project Settings.


#include "SnackBase.h"
#include "SnackBodyBase.h"

// Sets default values
ASnackBase::ASnackBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASnackBase::BeginPlay()
{
	Super::BeginPlay();

	InitTransformNode();
}

// Called every frame
void ASnackBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASnackBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

TLinkedList<FTransform>* ASnackBase::NextNode(TLinkedList<FTransform>* Node)
{
	if (Node && Node->GetNextLink())
	{
		return Node->GetNextLink();
	}
	return nullptr;
}

FTransform ASnackBase::NextNodeTransform()
{
	TLinkedList<FTransform>* NextNodePtr = NextNode(FirstTransformNode);
	if (NextNodePtr)
		return NextNodePtr->operator*();
	return FTransform();
}

FTransform ASnackBase::CallNextNodeMutiSt(int Times, bool& Success)
{
	TLinkedList<FTransform>* NextNodePtr = NextNode(FirstTransformNode);
	if (NextNodePtr)
	{
		for (int i = 0; i < Times - 1; i++)
		{
			NextNodePtr = this->NextNode(NextNodePtr);
			if (!NextNodePtr)
			{
				Success = false;
				return FTransform();
			}
		}
	}
	else
	{
		Success = false;
		return FTransform();
	}
	if (!NextNodePtr)
	{
		Success = false;
		return FTransform();
	}
	Success = true;
	return NextNodePtr->operator*();
}

void ASnackBase::AddNode(FTransform Transform)
{
	if (CurrentTransformNode)
	{
		TLinkedList<FTransform>* NextTransformNode = new TLinkedList(Transform);
		if (CurrentTransformNode && NextTransformNode)
		{
			CurrentTransformNode->LinkBefore(NextTransformNode);
			CurrentTransformNode = NextTransformNode;
		}
	}
}

FTransform ASnackBase::FindBodyTransform(ASnackBodyBase* SnackBodyBase, bool& Success)
{
	FTransform CurrentBodyTransform;
	TLinkedList<FTransform>* _List = SnackBodyBase->TransformNode;
	if (_List)
	{
		CurrentBodyTransform = _List->operator*();
		Success = true;
	}
	Success = false;
	return CurrentBodyTransform;
}

void ASnackBase::InitTransformNode()
{
	FirstTransformNode = new TLinkedList(GetActorTransform());
	CurrentTransformNode = FirstTransformNode;
}

FTransform ASnackBase::GetFirstTransform()
{
	return FirstTransformNode->operator*();
}

void ASnackBase::RemoveLinkNode(ASnackBodyBase* SnackBodyBase)
{
	TLinkedList<FTransform>* _TransformNode = SnackBodyBase->TransformNode;
	if (_TransformNode)
	{
		_TransformNode->Unlink();
	}
}

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

	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Orange,
	                                 FString::Printf(TEXT("Transform Nodes Size is: %d"), DoubleLinkedList->Num()));
	
}

// Called to bind functionality to input
void ASnackBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

TDoubleLinkedList<FTransform>::TDoubleLinkedListNode* ASnackBase::GetNextNode(
	TDoubleLinkedList<FTransform>::TDoubleLinkedListNode* Node)
{
	if (Node && Node->GetNextNode())
	{
		return Node->GetNextNode();
	}
	return nullptr;
}

TDoubleLinkedList<FTransform>::TDoubleLinkedListNode* ASnackBase::GetPrevNode(
	TDoubleLinkedList<FTransform>::TDoubleLinkedListNode* Node)
{
	if (Node && Node->GetPrevNode())
	{
		return Node->GetPrevNode();
	}
	return nullptr;
}

FTransform ASnackBase::NextNodeTransform(bool& Success)
{
	TDoubleLinkedList<FTransform>::TDoubleLinkedListNode* NextNodePtr = GetNextNode(FirstTransformNode);
	if (NextNodePtr)
	{
		Success = true;
		return NextNodePtr->GetValue();
	}
	Success = false;
	return FTransform();
}

FTransform ASnackBase::SetNextTimesNode(int Times, ASnackBodyBase* SnackBody, bool& Success)
{
	TDoubleLinkedList<FTransform>::TDoubleLinkedListNode* NextNodePtr = GetNextNode(SnackBody->TransformNode);
	if (NextNodePtr)
	{
		for (int i = 0; i < Times - 1; i++)
		{
			NextNodePtr = this->GetNextNode(NextNodePtr);
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
	SnackBody->TransformNode = NextNodePtr;
	return NextNodePtr->GetValue();
}

bool ASnackBase::SetPrevTimesNode(int Times, ASnackBodyBase* SnackBody)
{
	TDoubleLinkedList<FTransform>::TDoubleLinkedListNode* PrevNodePtr = GetPrevNode(SnackBody->TransformNode);
	if (PrevNodePtr)
	{
		for (int i = 0; i < Times - 1; i++)
		{
			PrevNodePtr = this->GetPrevNode(PrevNodePtr);
			if (!PrevNodePtr)
			{
				return false;
			}
		}
	}
	else
	{
		return false;
	}
	if (!PrevNodePtr)
	{
		return false;
	}
	SnackBody->TransformNode = PrevNodePtr;
	return true;
}

void ASnackBase::AddNode(FTransform Transform)
{
	if (DoubleLinkedList)
	{
		TDoubleLinkedList<FTransform>::TDoubleLinkedListNode* NextTransformNode = new TDoubleLinkedList<
			FTransform>::TDoubleLinkedListNode(Transform);
		if (CurrentTransformNode && NextTransformNode)
		{
			DoubleLinkedList->AddTail(NextTransformNode);
			CurrentTransformNode = NextTransformNode;
			NodeSize++;
		}
	}
}

FTransform ASnackBase::FindBodyTransform(ASnackBodyBase* SnackBodyBase, bool& Success)
{
	FTransform CurrentBodyTransform;
	TDoubleLinkedList<FTransform>::TDoubleLinkedListNode* _List = SnackBodyBase->TransformNode;
	if (_List)
	{
		CurrentBodyTransform = _List->GetValue();
		Success = true;
		return CurrentBodyTransform;
	}
	Success = false;
	return CurrentBodyTransform;
}

void ASnackBase::InitTransformNode()
{
	FirstTransformNode = new TDoubleLinkedList<FTransform>::TDoubleLinkedListNode(GetActorTransform());
	CurrentTransformNode = FirstTransformNode;
}

FTransform ASnackBase::GetFirstTransform()
{
	return FirstTransformNode->GetValue();
}

void ASnackBase::TruncateLinkedNode(TDoubleLinkedList<FTransform>::TDoubleLinkedListNode* TruncateNode, int Times)
{
	if (TruncateNode)
	{
		TDoubleLinkedList<FTransform>::TDoubleLinkedListNode* PrevNode = GetPrevNode(TruncateNode);
		// _TransformNode->Unlink();
		bool bIsTruncated = true; // 是否要截断链表
		// 截断链表逻辑
		for (int i = 0; i < Times; i++)
		{
			if (PrevNode)
			{
				PrevNode = PrevNode->GetPrevNode();
			}
			else
			{
				bIsTruncated = false;
				break;
			}
		}
		if (PrevNode && bIsTruncated)
		{
			TDoubleLinkedList<FTransform>::TDoubleLinkedListNode* HeadNode = DoubleLinkedList->GetHead();
			int RemoveCount = 0;
			while (true)
			{
				HeadNode = DoubleLinkedList->GetHead();
				if (HeadNode)
				{
					if (HeadNode == PrevNode)
					{
						break;
					}
					DoubleLinkedList->RemoveNode(HeadNode);
					RemoveCount++;
				}
			}
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue,
			                                 FString::Printf(TEXT("Remove Node Count = %d "), RemoveCount));
		}
	}
}

void ASnackBase::TruncateLinkedNode(int Times, bool& Success)
{
	if (SnackBodies.Num() > 0)
	{
		ASnackBodyBase* SnackBodyBase = SnackBodies[SnackBodies.Num() - 1];
		if (SnackBodyBase)
		{
			TruncateLinkedNode(SnackBodyBase->TransformNode, Times);
			Success = true;
			return;
		}
	}
	Success = false;
}

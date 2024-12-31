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

void ASnackBodyBase::InsideNext()
{
	if (TransformNode)
	{
		TransformNode = TransformNode->Next();
	}
}

void ASnackBodyBase::SetHeadNode()
{
	if (SnackBase)
	{
		TransformNode = SnackBase->FirstTransformNode;
	}
}

FTransform ASnackBodyBase::GetNodeTransform()
{
	if (TransformNode)
	return TransformNode->operator*();
	return FTransform();
}

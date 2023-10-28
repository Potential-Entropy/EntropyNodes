// Fill out your copyright notice in the Description page of Project Settings.


#include "EntropyNodesDebugActor.h"
#include "EntropyNodes.h"

// Sets default values
AEntropyNodesDebugActor::AEntropyNodesDebugActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEntropyNodesDebugActor::BeginPlay()
{
	Super::BeginPlay();

	static auto Handle = FMultiGateHandle{[]{}, []{}}.Execute();
	Handle.Execute();
}

// Called every frame
void AEntropyNodesDebugActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


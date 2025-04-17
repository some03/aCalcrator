// Fill out your copyright notice in the Description page of Project Settings.


#include "Network.h"

// Sets default values
ANetwork::ANetwork()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANetwork::BeginPlay()
{
	Super::BeginPlay();
	if (NeuronClass)
	{
		FVector SpawnLocation(0.0f, 0.0f, 200.0f);
		FRotator SpawnRotation = FRotator::ZeroRotator;

		// ニューロンをスポーン
		GetWorld()->SpawnActor<ANeurons>(NeuronClass, SpawnLocation, SpawnRotation);
	}
	
}

// Called every frame
void ANetwork::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


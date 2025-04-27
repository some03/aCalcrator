// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Neurons.h"
#include "Synapse.h"
#include "vector"
#include "string"
#include "Math/UnrealMathUtility.h"
#include "Math/IntPoint.h"
#include "Network.generated.h"


UCLASS()
class ACALCPROJECT_API ANetwork : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANetwork();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform) override;

	int32_t Rows = 8;
	int32_t Cols = 8;

	UPROPERTY(EditAnywhere, Category = "Neuron")
	TSubclassOf<class ANeurons> NeuronClass;

	UPROPERTY()
	TArray<ANeurons*> SpawnedNeurons;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, Category = "Synapse")
	TSubclassOf<class ASynapse> SynapseClass;

	//UPROPERTY()
	//TArray<ASynapse*> SpawnedSynapses;
	//std::map<std::pair<int, int>, ASynapse*> SynapseMap;
	TMap<FIntPoint, ASynapse*>SynapseMap;

	TArray<TArray<int>> createBitmap(int note, int gridSize);
	void stdpUpdate(int i);

	int dt = 0;
	int time = 1;
	double s_in_basal = 0;
	double s_in_apical = 0;
	TArray<TArray<int>>input;
	TArray<TArray<int>>sensor;
	bool feedback = false;


};

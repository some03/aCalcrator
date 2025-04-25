// Fill out your copyright notice in the Description page of Project Settings.


#include "Network.h"

// Sets default values
ANetwork::ANetwork()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Fix for E0415 and E0300 errors
void ANetwork::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < SpawnedNeurons.Num(); i++) {
		for (int j = i + 1; j < SpawnedNeurons.Num(); j++) {

			float dist = FVector::Dist(SpawnedNeurons[i]->GetActorLocation(), SpawnedNeurons[j]->GetActorLocation());
			if (dist < 200.f) {
				// 近いニューロン同士を結ぶ処理

				FVector start = SpawnedNeurons[i]->GetActorLocation();
				FVector end = SpawnedNeurons[j]->GetActorLocation();

				ASynapse* Synapse = GetWorld()->SpawnActor<ASynapse>(ASynapse::StaticClass(), start, FRotator::ZeroRotator);
				SynapseMap.Add(FIntPoint(i, j), Synapse);
				if (dist < 100.f)Synapse->SynapseLineInit(start, end, true);
				else Synapse->SynapseLineInit(start, end, false);





			}
		
		}
	}
}

// Called every frame
void ANetwork::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	int dt = 1;
	int time = 20;

	for (int i = 0;i < time;i += dt) {
	}



}
void ANetwork::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	double tau = 2.0, tau_a = 2.0, tau_b = 2.0;
	double gB = 1.0, gL = 1.0;
	double W_b = 0.8, W_hb = 0.5, W_a = 0.7, W_ha = 0.5, W_s = 0.9;
	double beta = 1.0, V_th = 1.0;

	int32 Index = 0;
	// ニューロンのスポーン
	if (NeuronClass)
	{
		for (int32_t i = 0; i < Rows; ++i)
		{
			for (int32_t j = 0; j < Cols; ++j)
			{
				FVector SpawnLocation(0.0f,i * 100.0f, j * 100.0f);
				FRotator SpawnRotation = FRotator::ZeroRotator;
				ANeurons* Neuron= GetWorld()->SpawnActor<ANeurons>(NeuronClass, SpawnLocation, SpawnRotation);

				if (Neuron)
				{
					//Neuron->NeuronID = Index;
					//Neuron->GridPosition = FVector(Row, Col, 0);
					Neuron->Initialize(FVector(0,i*100,j*100), tau, tau_a, tau_b,
						gB, gL,
						W_b, W_hb,
						W_a, W_ha,
						W_s, beta, V_th);

					SpawnedNeurons.Add(Neuron);
					++Index;
				}
			}
		}

		for (int32_t i = 0; i < Rows; ++i)
		{
			for (int32_t j = 0; j < Cols; ++j)
			{
				FVector SpawnLocation(700.0f,i * 100.0f, j * 100.0f);
				FRotator SpawnRotation = FRotator::ZeroRotator;
				ANeurons* Neuron= GetWorld()->SpawnActor<ANeurons>(NeuronClass, SpawnLocation, SpawnRotation);

				if (Neuron)
				{
					//Neuron->NeuronID = Index;
					//Neuron->GridPosition = FVector(Row, Col, 0);
					Neuron->Initialize(FVector(700.0f,i*100,j*100), tau, tau_a, tau_b,
						gB, gL,
						W_b, W_hb,
						W_a, W_ha,
						W_s, beta, V_th);

					SpawnedNeurons.Add(Neuron);
					++Index;
				}
			}
		}

		for (int32_t i = 0; i < Rows; ++i)
		{
			for (int32_t j = 0; j < Cols; ++j)
			{
				FVector SpawnLocation(i*100.0f,j * 100.0f, -100.0f);
				FRotator SpawnRotation = FRotator::ZeroRotator;
				ANeurons* Neuron= GetWorld()->SpawnActor<ANeurons>(NeuronClass, SpawnLocation, SpawnRotation);

				if (Neuron)
				{
					//Neuron->NeuronID = Index;
					//Neuron->GridPosition = FVector(Row, Col, 0);
					Neuron->Initialize(FVector(700.0f,i*100,j*100), tau, tau_a, tau_b,
						gB, gL,
						W_b, W_hb,
						W_a, W_ha,
						W_s, beta, V_th);

					SpawnedNeurons.Add(Neuron);
					++Index;
				}
			}
		}

		for (int32_t i = 0; i < Rows; ++i)
		{
			for (int32_t j = 0; j < Cols; ++j)
			{
				FVector SpawnLocation(i*100.0f,j * 100.0f, 800.0f);
				FRotator SpawnRotation = FRotator::ZeroRotator;
				ANeurons* Neuron= GetWorld()->SpawnActor<ANeurons>(NeuronClass, SpawnLocation, SpawnRotation);

				if (Neuron)
				{
					//Neuron->NeuronID = Index;
					//Neuron->GridPosition = FVector(Row, Col, 0);
					Neuron->Initialize(FVector(700.0f,i*100,j*100), tau, tau_a, tau_b,
						gB, gL,
						W_b, W_hb,
						W_a, W_ha,
						W_s, beta, V_th);

					SpawnedNeurons.Add(Neuron);
					++Index;
				}
			}
		}
	}
}
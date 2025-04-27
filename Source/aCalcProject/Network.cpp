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
	dt = 0;

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

	double tau = 2.0, tau_a = 2.0, tau_b = 2.0;
	double gB = 1.0, gL = 1.0;
	double W_b = 0.8, W_hb = 0.5, W_a = 0.7, W_ha = 0.5, W_s = 0.9;
	double beta = 1.0, V_th = 1.0;

	input = createBitmap(120, 8);

	if (input.Num() == 0 || input[0].Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("input bitmap generation failed!"));
		return; // クラッシュ防止にここで抜ける
	}
	sensor.SetNum(8);
	for (int i = 0; i < 8; ++i)
	{
		sensor[i].Init(0, 8);
	}

	while(dt<time) {

		int ioneuron = SpawnedNeurons.Num();
		int rec = 0;

		if (!feedback) {
			for (int i = 0;i < ioneuron;i++) {
				if ((SpawnedNeurons[i]->x <= 200) && (SpawnedNeurons[i]->z <= 700) && ((SpawnedNeurons[i]->z >= 0))) {
					int yId = SpawnedNeurons[i]->y / 100;
					int zId = SpawnedNeurons[i]->z / 100;

					s_in_apical = input[yId][zId];
					if (SpawnedNeurons[i]->x == 0)s_in_basal = input[yId][zId];
					if (s_in_apical || s_in_basal) {
						SpawnedNeurons[i]->UpdateVisuals(1);
						UE_LOG(LogTemp, Log, TEXT("fire"));

					}
				}
				else if ((SpawnedNeurons[i]->z == 800)) {
					s_in_basal = 1;
					s_in_apical = 1;

				}
				for (int j = 0;j < ioneuron;j++) {
					if (i == j)continue;

					ASynapse** SynapsePtr = SynapseMap.Find(FIntPoint(i, j));
					if (SynapsePtr && *SynapsePtr)
					{
						if (!SpawnedNeurons[i]->sensor)SynapseMap[{i, j}]->w *= 1.5;
						rec += (*SynapsePtr)->w * SpawnedNeurons[j]->S_h;
					}
					else rec +=0;

				}
				SpawnedNeurons[i]->Update(s_in_basal, s_in_apical, rec, dt);
				if (SpawnedNeurons[i]->S_h == 1) {
					stdpUpdate(i);
					SpawnedNeurons[i]->sensor = 1;
					if (SpawnedNeurons[i]->z == 0) {

						int yId = SpawnedNeurons[i]->y / 100;
						int zId = SpawnedNeurons[i]->z / 100;
						sensor[yId][zId] = 1;


					}

				}


			}
		}
		else {
			for (int i = 0;i < SpawnedNeurons.Num();i++) {

				if ((SpawnedNeurons[i]->x >= 600) && (SpawnedNeurons[i]->z <= 700) && ((SpawnedNeurons[i]->z >= 0))) {

					int yId = SpawnedNeurons[i]->y / 100;
					int zId = SpawnedNeurons[i]->z / 100;

					s_in_basal = sensor[yId][zId];

					if (SpawnedNeurons[i]->x == 800)s_in_basal = input[yId][zId];
				}
				for (int j = 0;j < ioneuron;j++) {
					if (i == j)continue;
					ASynapse** SynapsePtr = SynapseMap.Find(FIntPoint(i, j));
					if (SynapsePtr && *SynapsePtr)
					{
						if (!SpawnedNeurons[i]->sensor)SynapseMap[{i, j}]->w *= 1.5;
						rec += (*SynapsePtr)->w * SpawnedNeurons[j]->S_h;
					}
					else rec +=0;

				}
				SpawnedNeurons[i]->Update(s_in_basal, s_in_apical, rec, dt);
				if (SpawnedNeurons[i]->S_h == 1) {
					stdpUpdate(i);

				}
			}
			sensor.Empty();

		}
		if (SpawnedNeurons.Num() < 500) {
			if (feedback) {
				for (int y = 0;y < Rows;y++) {
					for (int z = 0;z < Cols;z++) {
						if (sensor[y][z] == 1) {
							int32 randomy = FMath::RandRange(100 * y - 100, 100 * y);
							int32 randomz = FMath::RandRange(100 * z - 100, 100 * z);
							int32 randomx = FMath::RandRange(100, 600);

							FVector SpawnLocation(randomx, randomy, randomz);
							FRotator SpawnRotation = FRotator::ZeroRotator;
							ANeurons* Neuron = GetWorld()->SpawnActor<ANeurons>(NeuronClass, SpawnLocation, SpawnRotation);

							if (Neuron)
							{
								//Neuron->NeuronID = Index;
								//Neuron->GridPosition = FVector(Row, Col, 0);
								Neuron->Initialize(FVector(randomx, randomy, randomz), tau, tau_a, tau_b,
									gB, gL,
									W_b, W_hb,
									W_a, W_ha,
									W_s, beta, V_th);

								SpawnedNeurons.Add(Neuron);
							}
						}

					}
				}

				for (int i = 0; i < ioneuron; i++) {
					for (int j = ioneuron; j < SpawnedNeurons.Num(); j++) {

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

		}
		feedback = !feedback;
		dt++;

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
				}
			}
		}
	}
}
TArray<TArray<int>> ANetwork::createBitmap(int note, int gridSize) {
	if (note < 0 || note > 127) {
		UE_LOG(LogTemp, Warning, TEXT("Invalid note value: %d"), note);
		return TArray<TArray<int>>();
	}

	// MIDIノートを7ビットの2進数に変換
	FString bitstream = "";
	for (int i = 6; i >= 0; --i) {
		bitstream += ((note >> i) & 1) ? '1' : '0';
	}

	// ビットストリームの長さを gridSize^2 に合わせる
	int totalBits = gridSize * gridSize;
	if (bitstream.Len() < totalBits) {
		// Replace the problematic line with the following code:
		bitstream.Append(FString::ChrN(totalBits - bitstream.Len(), '0'));
	}
	else if (bitstream.Len() > totalBits) {
		bitstream = bitstream.Mid(0, totalBits);
	}

	// 2次元グリッドに変換
	TArray<TArray<int>> grid;
	grid.SetNum(gridSize);
	for (int i = 0; i < gridSize; ++i)
	{
		grid[i].SetNum(gridSize);
	}
	for (int i = 0; i < totalBits; ++i) {
		int row = i / gridSize;
		int col = i % gridSize;
		grid[row][col] = bitstream[i] - '0';
	}

	return grid;
}
void ANetwork::stdpUpdate(int i) {
	// STDPの更新ルールに基づいてシナプスの重みを更新
	double delta_t = 0.1; // 時間差
	double A_plus = 0.005; // 増加の学習率
	double A_minus = 0.005; // 減少の学習率
	double tau_plus = 20.0; // 増加の時間定数
	double tau_minus = 20.0; // 減少の時間定数
	double limit = 5; // シナプスの重みの上限

	for (int j = 0;j < SpawnedNeurons.Num();j++) {
		delta_t = SpawnedNeurons[i]->stdptime - SpawnedNeurons[j]->stdptime;
		if (delta_t > 0) {
			SynapseMap[{i, j}]->w += A_plus * exp(-delta_t / tau_plus);
		}
		else {
			SynapseMap[{i, j}]->w -= A_minus * exp(delta_t / tau_minus);
		}
		if (SynapseMap[{i, j}]->w > limit) {
			SynapseMap[{i, j}]->w = limit;
		}
		else if (SynapseMap[{i, j}]->w < 0) {
			SynapseMap[{i, j}]->w = 0;
		}


	}
}
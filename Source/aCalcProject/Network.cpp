// Fill out your copyright notice in the Description page of Project Settings.


#include "Network.h"
#include "DigitsDataLoader.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFilemanager.h"

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
	feedback = false;

	DigitsDataLoader DataLoader;
	if (DataLoader.LoadOptDigits(TEXT("Data/optdigits.txt")))
	{
		UE_LOG(LogTemp, Log, TEXT("Loaded %d samples"), DataLoader.Samples.Num());
		DataLoader.GeneratePoissonSpikes(100, 1);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load samples"));
		return;
	}

/*
	// Content フォルダへの絶対パスを組み立て
	FString FilePath = FPaths::ProjectContentDir() / TEXT("Data/optdigits.txt");


	// まずファイルの存在チェック
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath))
	{
		UE_LOG(LogTemp, Error, TEXT("File not found: %s"), *FilePath);
		return;
	}

	// 行ごとに読み込む
	TArray<FString> Lines;
	if (FFileHelper::LoadFileToStringArray(Lines, *FilePath))
	{
		UE_LOG(LogTemp, Log, TEXT("Loaded %d lines from %s"), Lines.Num(), *FilePath);
		for (const FString& Line : Lines)
		{
			// カンマで分割
			TArray<FString> Cells;
			Line.ParseIntoArray(Cells, TEXT(","), true);

			// 0〜63 が画素値、64 がラベル
			TArray<float> Pixels;
			Pixels.Reserve(64);
			for (int32 i = 0; i < 64; ++i)
			{
				float v = FCString::Atof(*Cells[i]) / 16.0f;  // 正規化
				Pixels.Add(v);
			}
			int32 Label = FCString::Atoi(*Cells[64]);
			// ここでPixels, LabelをPoissonエンコード→SNNへ渡す
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load file: %s"), *FilePath);
	}
*/

	

	for (int i = 0;i < Cols * Rows;i++) {

		int index = Cols * Rows*2;
		int midindex = Cols * Rows;
		if (!(SpawnedNeurons.IsValidIndex(i + index) && SpawnedNeurons.IsValidIndex(i + midindex)))break;


		FVector start = SpawnedNeurons[i]->GetActorLocation();
		FVector end = SpawnedNeurons[i+index]->GetActorLocation();
		FVector midpoint_1 = (start + end) * 0.5f + FVector(0, 0, 200);
		FVector midpoint_2 = (start + end) * 0.5f + FVector(0, 0, -200);

		ASynapse* Synapse_1 = GetWorld()->SpawnActor<ASynapse>(ASynapse::StaticClass(), start, FRotator::ZeroRotator);
		ASynapse* Synapse_2 = GetWorld()->SpawnActor<ASynapse>(ASynapse::StaticClass(), start, FRotator::ZeroRotator);
		if (Synapse_1&&Synapse_2)
		{
			Synapse_1->CurveLineInit(start, end, midpoint_1);
			Synapse_2->CurveLineInit(start, end, midpoint_2);
			SynapseMap.Add(FIntPoint(i, i + index), Synapse_1);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to spawn synapse1,2"));
		}


		start = SpawnedNeurons[i]->GetActorLocation();
		end = SpawnedNeurons[i+midindex]->GetActorLocation();
		ASynapse* Synapse_3 = GetWorld()->SpawnActor<ASynapse>(ASynapse::StaticClass(), start, FRotator::ZeroRotator);

		if (Synapse_3) {

			SynapseMap.Add(FIntPoint(i,i+midindex), Synapse_3);
			Synapse_3->SynapseLineInit(start, end, true);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to spawn synapse3"));

		}

		start = SpawnedNeurons[i+index]->GetActorLocation();
		end = SpawnedNeurons[i+midindex]->GetActorLocation();
		ASynapse* Synapse_4 = GetWorld()->SpawnActor<ASynapse>(ASynapse::StaticClass(), start, FRotator::ZeroRotator);

		if (Synapse_4) {

			SynapseMap.Add(FIntPoint(i+index, i+midindex), Synapse_4);
			Synapse_4->SynapseLineInit(start, end, true);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to spawn synapse4"));

		}


		for (int j = Cols * Rows * 3;j < SpawnedNeurons.Num();j++) {

			start = SpawnedNeurons[i+midindex]->GetActorLocation();
			end = SpawnedNeurons[j]->GetActorLocation();

			ASynapse* Synapse_5 = GetWorld()->SpawnActor<ASynapse>(ASynapse::StaticClass(), start, FRotator::ZeroRotator);

		if (Synapse_5) {

			SynapseMap.Add(FIntPoint(i+midindex, j), Synapse_5);
			Synapse_5->SynapseLineInit(start, end, true);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to spawn synapse5"));

		}

		}



	}
}

// Called every frame
void ANetwork::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);




}
void ANetwork::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	double tau = 2.0, tau_a = 2.0, tau_b = 2.0;
	double gB = 1.0, gL = 1.0;
	double W_b = 0.8, W_hb = 0.5, W_a = 0.7, W_ha = 0.5, W_s = 0.9;
	double beta = 1.0, V_th = 1.0;

	if (NeuronClass)
	{
		// 面ごとに設定を持つ
		struct FSurfaceSetting
		{
			FVector BaseOffset;
			FVector XStep;
			FVector YStep;
		};

		// 左面・右面・底面・天面の設定
		TArray<FSurfaceSetting> SurfaceSettings = {
			{ FVector(0.0f, 0.0f, 0.0f),    FVector(0.0f, 200.0f, 0.0f), FVector(0.0f, 0.0f, 200.0f) }, // 左面
			{ FVector(800.0f, 0.0f, 0.0f), FVector(0.0f, 200.0f, 0.0f), FVector(0.0f, 0.0f, 200.0f) }, // 中央面
			{ FVector(1600.0f, 0.0f, 0.0f),  FVector(0.0f, 200.0f, 0.0f), FVector(0.0f, 0.0f, 200.0f) }, // 右面
			{ FVector(0.0f, 0.0f, -200.0f), FVector(200.0f, 0.0f, 0.0f), FVector(0.0f, 200.0f, 0.0f) }, // 底面

			//{ FVector(0.0f, 0.0f, 800.0f),  FVector(100.0f, 0.0f, 0.0f), FVector(0.0f, 100.0f, 0.0f) }, // 天面
		};

		for (const FSurfaceSetting& Surface : SurfaceSettings)
		{
			for (int32 i = 0; i < Rows; ++i)
			{
				for (int32 j = 0; j < Cols; ++j)
				{
					FVector SpawnLocation = Surface.BaseOffset + Surface.XStep * i + Surface.YStep * j;
					FRotator SpawnRotation = FRotator::ZeroRotator;
					ANeurons* Neuron = GetWorld()->SpawnActor<ANeurons>(NeuronClass, SpawnLocation, SpawnRotation);

					if (Neuron)
					{

						Neuron->Initialize(tau, tau_a, tau_b,
							gB, gL,
							W_b, W_hb,
							W_a, W_ha,
							W_s, beta, V_th,0);

						SpawnedNeurons.Add(Neuron);
					}
				}
			}
		}

	}
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
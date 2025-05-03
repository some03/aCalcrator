// Fill out your copyright notice in the Description page of Project Settings.


#include "DigitsDataLoader.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFilemanager.h"

DigitsDataLoader::DigitsDataLoader()
{
    Rng.Initialize(FDateTime::Now().GetMillisecond());
}

DigitsDataLoader::~DigitsDataLoader()
{
}
bool DigitsDataLoader::LoadOptDigits(const FString& RelativePath)
{
	// Content フォルダへの絶対パスを組み立て
	FString FilePath = FPaths::ProjectContentDir() / RelativePath;
	// まずファイルの存在チェック
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath))
	{
		UE_LOG(LogTemp, Error, TEXT("File not found: %s"), *FilePath);
		return false;
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
			FDigitSample Sample;
			Sample.Pixels = Pixels;
			Sample.Label = Label;
			Samples.Add(Sample);
		}
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load file: %s"), *FilePath);
		return false;
	}
}
void DigitsDataLoader::GeneratePoissonSpikes(int32 Tms, int32 dtms)
{
	const int32 TimeSteps = Tms / dtms;

	for (FDigitSample& Sample : Samples)
	{
		Sample.SpikeTrain.SetNum(TimeSteps);
		for (int32 t = 0; t < TimeSteps; ++t)
		{
			Sample.SpikeTrain[t].SetNum(64);
			for (int32 i = 0; i < 64; ++i)
			{
				float Rate = Sample.Pixels[i];
				float P = Rate * (dtms / 1000.0f);
				float R = Rng.FRand();
				Sample.SpikeTrain[t][i] = (R < P) ? 1 : 0;
			}
		}
	}

	UE_LOG(LogTemp, Log, TEXT("Generated Poisson spikes: T=%d ms, dt=%d ms"), Tms, dtms);
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DigitSample.h"

/**
 * 
 */
class ACALCPROJECT_API DigitsDataLoader
{
public:
	DigitsDataLoader();
	~DigitsDataLoader();
	TArray<FDigitSample> Samples;
	bool LoadOptDigits(const FString& RelativePath);
	void GeneratePoissonSpikes(int32 Tms, int32 dtms);
private:
	/** ÄŒ»«‚ ‚è^‚È‚µ‚ğØ‚è‘Ö‚¦‚ç‚ê‚é UE —”ƒXƒgƒŠ[ƒ€ */
	FRandomStream Rng;

};

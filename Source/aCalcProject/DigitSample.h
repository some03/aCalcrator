// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
 /**
  * 1サンプル分のデータ構造
  * - Pixels: 正規化済み (0.0–1.0) の 64 要素
  * - Label: 0–9 の整数
  * - SpikeTrain: Poisson 符号化後 [TimeSteps][64]
  */
struct FDigitSample
{
    TArray<float> Pixels;
    int32       Label;
    TArray<TArray<uint8>> SpikeTrain;
};

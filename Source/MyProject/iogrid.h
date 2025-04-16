// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#ifndef UPDOWGRID_H
#define UPDOWGRID_H

#include "CoreMinimal.h"

/**
 * 
 */

#include <iostream>
#include <vector>
#include <ctime>

class MYPROJECT_API IoGrid {
public:
    // コンストラクタ
    IoGrid(int gridRows, int gridCols);
    // デストラクタ
    ~IoGrid();
    void recordSpike(int row, int col);
    int getSpikeCounts();

private:
    // グリッドセルごとの MIDI ノート番号のマッピング（0～127 の範囲）
    std::vector<std::vector<int>> midiMapping;
    // グリッドセルごとのスパイクカウント
    std::vector<std::vector<int>> spikeCounts;
    int gridRows; // グリッドの行数
    int gridCols; // グリッドの列数
};
#endif // UPDOWGRID_H
/*
class MYPROJECT_API Iogrid
{
public:
	Iogrid();
	~Iogrid();
};
*/
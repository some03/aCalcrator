// Fill out your copyright notice in the Description page of Project Settings.


#include "iogrid.h"
#include <limits>


IoGrid::IoGrid(int gridRows, int gridCols) : midiMapping(gridRows, std::vector<int>(gridCols, 0)), spikeCounts(gridRows, std::vector<int>(gridCols, 0)) {
    this->gridRows = gridRows; // グリッドの行数を保存
    this->gridCols = gridCols; // グリッドの列数を保存
    midiMapping.resize(gridRows, std::vector<int>(gridCols, 0)); // グリッドセルごとの MIDI ノート番号のマッピング
    // MIDIノート番号のマッピングを初期化
    for (int i = 0; i < gridRows; ++i) {
        for (int j = 0; j < gridCols; ++j) {
            midiMapping[i][j] = (i * gridCols + j) % 128; // 0～127 の範囲でマッピング
        }
    }
}

IoGrid::~IoGrid() {
    ;
}

void IoGrid::recordSpike(int row, int col) {
    if (row >= 0 && row < midiMapping.size() && col >= 0 && col < midiMapping[0].size()) {
        spikeCounts[row][col]++;
    }
}

int IoGrid::getSpikeCounts() {
    int maxCount = std::numeric_limits<int>::min();
    /**/int maxX = -1, maxY = -1;
    for (int i = 0; i < gridRows; ++i) {
        for (int j = 0; j < gridCols; ++j) {
            if (spikeCounts[i][j] > maxCount) {
                maxCount = spikeCounts[i][j];
                maxX = i;
                maxY = j;
            }
        }
    }
    // 最大のスパイクカウントを持つセルが見つかった場合、そのセルに割り当てられた MIDI ノート番号を返します。
    if (maxX != -1 && maxY != -1) {
        return midiMapping[maxX][maxY];
    }
    // もしセルが見つからなかった場合は、適宜エラーコード（ここでは -1）を返す
    return -1;
}
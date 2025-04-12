#ifndef UPDOWGRID_H
#define UPDOWGRID_H

#include <iostream>
#include <vector>
#include <ctime>

class IoGrid {
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
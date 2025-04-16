// Fill out your copyright notice in the Description page of Project Settings.


#include "sensorgrid.h"

// コンストラクタ: グリッドサイズを設定
SensorGrid::SensorGrid(int gridSize) : gridSize_(gridSize) {
    if (gridSize_ <= 0) {
        throw std::invalid_argument("gridSize must be positive.");
    }
}

// デストラクタ
SensorGrid::~SensorGrid() {
    // 特に動的確保したリソースがなければ、何もしません
}

// 整数 value を、指定された bits 桁の2進数文字列に変換する
std::string SensorGrid::toBinary(int value, int bits) const {
    std::string binary = "";
    int i;
    for (i = bits - 1; i >= 0; i--) {
        if (((value >> i) & 1) == 1) {
            binary.push_back('1');
        }
        else {
            binary.push_back('0');
        }
    }
    return binary;
}

// 1 つの MIDIノートから連結したビットストリームを生成する
// 入力値 (note) は 0～127 である必要があります。7 ビットの2進数表現を返します。
std::string SensorGrid::generateBitstream(int note) const {
    if (note < 0 || note > 127) {
        throw std::invalid_argument("MIDI note must be in the range 0 to 127.");
    }
    return toBinary(note, 7);
}

// ビットストリームの長さを、グリッドの総ピクセル数 (totalBits) に合わせて調整する
std::string SensorGrid::adjustBitstream(const std::string& bitstream, int totalBits) const {
    std::string adjusted = bitstream;
    int currentSize = static_cast<int>(adjusted.size());
    if (currentSize < totalBits) {
        adjusted.append(totalBits - currentSize, '0');
    }
    else if (currentSize > totalBits) {
        adjusted = adjusted.substr(0, totalBits);
    }
    return adjusted;
}

// 調整済みのビットストリームから N×N のグリッドを生成する
std::vector<std::vector<int> > SensorGrid::generateGrid(const std::string& bitstream) const {
    int totalPixels = gridSize_ * gridSize_;
    std::vector<std::vector<int> > grid;
    int i;
    grid.resize(gridSize_);
    for (i = 0; i < gridSize_; i++) {
        grid[i].resize(gridSize_);
    }
   
    for (i = 0; i < totalPixels; i++) {
        int row = i / gridSize_;
        int col = i % gridSize_;
        grid[row][col] = bitstream[i] - '0'; // 文字 '0' または '1' を整数値に変換
    }
    return grid;
}

// 1 つの MIDIノートをもとに、N×N のビットマップを生成するパブリックメソッド
std::vector<std::vector<int> > SensorGrid::createBitmap(int note) const {
    std::string bitstream = generateBitstream(note);
    int totalPixels = gridSize_ * gridSize_;
    bitstream = adjustBitstream(bitstream, totalPixels);
    return generateGrid(bitstream);
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#ifndef SENSORGRID_H
#define SENSORGRID_H

#include "CoreMinimal.h"

#include <vector>
#include <string>
#include <stdexcept>

class MYPROJECT_API SensorGrid {
public:
    // gridSize: 作成する N×N グリッドの一辺の長さ（例：8なら8×8のグリッド）
    explicit SensorGrid(int gridSize);

    ~SensorGrid();

    // サンプルデータとして 1 つの MIDIノート（0～127 の整数値）を受け取り、
    // N×N のビットマップを生成する
    // ここでは、MIDIノートを 7 ビットの2進数に変換し、そのビット列を連結後、
    // グリッドの総ピクセル数に満たない場合は '0' でパディング、余る場合は切り捨てます。
    std::vector<std::vector<int> > createBitmap(int note) const;

private:
    int gridSize_;

    // 整数 value を、指定された bits 桁の2進数文字列に変換するヘルパーメソッド
    std::string toBinary(int value, int bits) const;

    // 1 つの MIDIノートからビットストリームを生成する
    std::string generateBitstream(int note) const;

    // 生成したビットストリームの長さを、グリッドの総ピクセル数 (gridSize_×gridSize_) に合わせて
    // パディングまたは切り詰めする
    std::string adjustBitstream(const std::string& bitstream, int totalBits) const;

    // 調整済みビットストリームから N×N のグリッド（2次元ベクター）を生成する
    std::vector<std::vector<int> > generateGrid(const std::string& bitstream) const;
};

#endif // SENSORGRID_HPP
/**
 * 
 
class MYPROJECT_API sensorgrid
{
public:
	sensorgrid();
	~sensorgrid();
};
*/
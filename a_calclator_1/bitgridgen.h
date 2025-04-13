#ifndef BITGRIDGENERATOR_H
#define BITGRIDGENERATOR_H

#include <vector>
#include <string>

class SensorGrid {
public:
    // コンストラクタ
    // gridSize: 作成する NxN のグリッドの N
    explicit SensorGrid(int gridSize);

    // デストラクタ
    ~SensorGrid();

    // サンプルデータ（MIDIノート）のベクターを受け取り、NxN のビットグリッドを生成する
    // 各サンプルは MIDI ノート（0～127）として前提し、7 ビットで符号化して連結したビットストリームからグリッドを作成します。
    // 生成されたグリッドは、各要素が 0 または 1 の 2 次元の整数ベクターとなります。
    std::vector<std::vector<int>> createBitGrid(const std::vector<int>& samples) const;

private:
    int gridSize_;


    // 整数 value を固定ビット数(bits)の二進数文字列に変換する
    std::string toBinary(int value, int bits) const;

    // サンプルデータからビットストリームを生成する
    // 各サンプルについて、MIDIノートを 7 ビットで符号化して連結する
    std::string generateBitstream(const std::vector<int>& samples) const;

    // ビットストリームの長さを、グリッドの総ピクセル数(totalPixels)に合わせて
    // パディングまたは切り詰めする
    std::string adjustBitstream(std::string bitstream, int totalPixels) const;

    // 調整済みのビットストリームから NxN のグリッドを生成する
    std::vector<std::vector<int>> generateGrid(const std::string &bitstream) const;
};

#endif // BITGRIDGENERATOR_HPP

#include "bitgridgen.h"
#include <stdexcept>

// コンストラクタ：グリッドサイズの設定
SensorGrid::SensorGrid(int gridSize) : gridSize_(gridSize) {
    if (gridSize_ <= 0) {
        throw std::invalid_argument("gridSize must be positive.");
    }
}

// デストラクタ
SensorGrid::~SensorGrid() {
    // 動的確保したリソースがなければ、特に処理は不要
}

// 整数 value を、指定された bits 桁の二進数文字列に変換する
std::string SensorGrid::toBinary(int value, int bits) const {
    std::string binary;
    for (int i = bits - 1; i >= 0; --i) {
        binary.push_back(((value >> i) & 1) ? '1' : '0');
    }
    return binary;
}

// サンプルデータからビットストリームを生成する
// 各サンプル（MIDIノート）を 7 ビットの二進数文字列に変換し、連結する
std::string SensorGrid::generateBitstream(const std::vector<int>& samples) const {
    std::string bitstream;
    for (const auto &midiNote : samples) {
        // 入力値チェック（MIDIノートは 0～127 であること）
        if (midiNote < 0 || midiNote > 127) {
            throw std::invalid_argument("MIDI note must be in the range 0 to 127.");
        }
        bitstream += toBinary(midiNote, 7);
    }
    return bitstream;
}

// ビットストリームをグリッドの総ピクセル数(totalPixels)に合わせて調整する
std::string SensorGrid::adjustBitstream(std::string bitstream, int totalPixels) const {
    if (static_cast<int>(bitstream.size()) < totalPixels) {
        // 足りない場合、末尾に '0' を追加
        bitstream.append(totalPixels - bitstream.size(), '0');
    }
    else if (static_cast<int>(bitstream.size()) > totalPixels) {
        // 多すぎる場合は、先頭から totalPixels 分だけ切り出す
        bitstream = bitstream.substr(0, totalPixels);
    }
    return bitstream;
}

// 調整済みのビットストリームから NxN のグリッドを生成する
std::vector<std::vector<int>> SensorGrid::generateGrid(const std::string &bitstream) const {
    std::vector<std::vector<int>> grid(gridSize_, std::vector<int>(gridSize_, 0));
    int totalPixels = gridSize_ * gridSize_;
    for (int i = 0; i < totalPixels; ++i) {
        int row = i / gridSize_;
        int col = i % gridSize_;
        grid[row][col] = bitstream[i] - '0'; // '0' または '1' を整数に変換
    }
    return grid;
}

// サンプルデータをもとに、NxN のビットグリッドを生成するパブリックメソッド
std::vector<std::vector<int>> SensorGrid::createBitGrid(const std::vector<int>& samples) const {
    std::string bitstream = generateBitstream(samples);
    int totalPixels = gridSize_ * gridSize_;
    bitstream = adjustBitstream(bitstream, totalPixels);
    return generateGrid(bitstream);
}

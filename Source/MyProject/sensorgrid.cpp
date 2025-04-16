// Fill out your copyright notice in the Description page of Project Settings.


#include "sensorgrid.h"

// �R���X�g���N�^: �O���b�h�T�C�Y��ݒ�
SensorGrid::SensorGrid(int gridSize) : gridSize_(gridSize) {
    if (gridSize_ <= 0) {
        throw std::invalid_argument("gridSize must be positive.");
    }
}

// �f�X�g���N�^
SensorGrid::~SensorGrid() {
    // ���ɓ��I�m�ۂ������\�[�X���Ȃ���΁A�������܂���
}

// ���� value ���A�w�肳�ꂽ bits ����2�i��������ɕϊ�����
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

// 1 �� MIDI�m�[�g����A�������r�b�g�X�g���[���𐶐�����
// ���͒l (note) �� 0�`127 �ł���K�v������܂��B7 �r�b�g��2�i���\����Ԃ��܂��B
std::string SensorGrid::generateBitstream(int note) const {
    if (note < 0 || note > 127) {
        throw std::invalid_argument("MIDI note must be in the range 0 to 127.");
    }
    return toBinary(note, 7);
}

// �r�b�g�X�g���[���̒������A�O���b�h�̑��s�N�Z���� (totalBits) �ɍ��킹�Ē�������
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

// �����ς݂̃r�b�g�X�g���[������ N�~N �̃O���b�h�𐶐�����
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
        grid[row][col] = bitstream[i] - '0'; // ���� '0' �܂��� '1' �𐮐��l�ɕϊ�
    }
    return grid;
}

// 1 �� MIDI�m�[�g�����ƂɁAN�~N �̃r�b�g�}�b�v�𐶐�����p�u���b�N���\�b�h
std::vector<std::vector<int> > SensorGrid::createBitmap(int note) const {
    std::string bitstream = generateBitstream(note);
    int totalPixels = gridSize_ * gridSize_;
    bitstream = adjustBitstream(bitstream, totalPixels);
    return generateGrid(bitstream);
}

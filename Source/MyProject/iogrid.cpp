// Fill out your copyright notice in the Description page of Project Settings.


#include "iogrid.h"
#include <limits>


IoGrid::IoGrid(int gridRows, int gridCols) : midiMapping(gridRows, std::vector<int>(gridCols, 0)), spikeCounts(gridRows, std::vector<int>(gridCols, 0)) {
    this->gridRows = gridRows; // �O���b�h�̍s����ۑ�
    this->gridCols = gridCols; // �O���b�h�̗񐔂�ۑ�
    midiMapping.resize(gridRows, std::vector<int>(gridCols, 0)); // �O���b�h�Z�����Ƃ� MIDI �m�[�g�ԍ��̃}�b�s���O
    // MIDI�m�[�g�ԍ��̃}�b�s���O��������
    for (int i = 0; i < gridRows; ++i) {
        for (int j = 0; j < gridCols; ++j) {
            midiMapping[i][j] = (i * gridCols + j) % 128; // 0�`127 �͈̔͂Ń}�b�s���O
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
    // �ő�̃X�p�C�N�J�E���g�����Z�������������ꍇ�A���̃Z���Ɋ��蓖�Ă�ꂽ MIDI �m�[�g�ԍ���Ԃ��܂��B
    if (maxX != -1 && maxY != -1) {
        return midiMapping[maxX][maxY];
    }
    // �����Z����������Ȃ������ꍇ�́A�K�X�G���[�R�[�h�i�����ł� -1�j��Ԃ�
    return -1;
}
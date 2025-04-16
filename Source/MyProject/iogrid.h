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
    // �R���X�g���N�^
    IoGrid(int gridRows, int gridCols);
    // �f�X�g���N�^
    ~IoGrid();
    void recordSpike(int row, int col);
    int getSpikeCounts();

private:
    // �O���b�h�Z�����Ƃ� MIDI �m�[�g�ԍ��̃}�b�s���O�i0�`127 �͈̔́j
    std::vector<std::vector<int>> midiMapping;
    // �O���b�h�Z�����Ƃ̃X�p�C�N�J�E���g
    std::vector<std::vector<int>> spikeCounts;
    int gridRows; // �O���b�h�̍s��
    int gridCols; // �O���b�h�̗�
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
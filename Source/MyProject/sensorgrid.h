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
    // gridSize: �쐬���� N�~N �O���b�h�̈�ӂ̒����i��F8�Ȃ�8�~8�̃O���b�h�j
    explicit SensorGrid(int gridSize);

    ~SensorGrid();

    // �T���v���f�[�^�Ƃ��� 1 �� MIDI�m�[�g�i0�`127 �̐����l�j���󂯎��A
    // N�~N �̃r�b�g�}�b�v�𐶐�����
    // �����ł́AMIDI�m�[�g�� 7 �r�b�g��2�i���ɕϊ����A���̃r�b�g���A����A
    // �O���b�h�̑��s�N�Z�����ɖ����Ȃ��ꍇ�� '0' �Ńp�f�B���O�A�]��ꍇ�͐؂�̂Ă܂��B
    std::vector<std::vector<int> > createBitmap(int note) const;

private:
    int gridSize_;

    // ���� value ���A�w�肳�ꂽ bits ����2�i��������ɕϊ�����w���p�[���\�b�h
    std::string toBinary(int value, int bits) const;

    // 1 �� MIDI�m�[�g����r�b�g�X�g���[���𐶐�����
    std::string generateBitstream(int note) const;

    // ���������r�b�g�X�g���[���̒������A�O���b�h�̑��s�N�Z���� (gridSize_�~gridSize_) �ɍ��킹��
    // �p�f�B���O�܂��͐؂�l�߂���
    std::string adjustBitstream(const std::string& bitstream, int totalBits) const;

    // �����ς݃r�b�g�X�g���[������ N�~N �̃O���b�h�i2�����x�N�^�[�j�𐶐�����
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
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#ifndef NEURON_H
#define NEURON_H

#include "CoreMinimal.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>

class MYPROJECT_API MCNNeuron
{
public:
    // �j���[�����̈ʒu
    double x, y, z;

    //basal dendrite ������ˋN�̖��d��
    double V_b; // ������ˋN�̖��d��
    double tau_b; // ������ˋN�̎��萔
    double W_b;   // ��ꑤ�O�����͂̏d��
    double W_hb;  // ��ꑤ�j���[�������͂̏d��

    //apical dendrite ��������ˋN�̖��d�� 
    double V_a; // ��������ˋN�̖��d��
    double tau_a; // ��������ˋN�̎��萔
    double W_a;   // �������O�����͂̏d��
    double W_ha;  // �������ċA���͂̏d��

    //soma �זE�̖̂��d��
    double U;   // �זE�̖̂��d��
    double tau;   // �זE�̂̎��萔
    double gB;    // ���R���_�N�^���X
    double gL;    // �R��R���_�N�^���X
    double W_s;   // �זE�̊O�����͂̏d��

    double beta;  // �V�O���C�h�̉s��
    double V_th;  // �X�p�C�N臒l
    int S_h;    // �X�p�C�N�o�́i0�܂���1�j
    double stdptime = 0;

    MCNNeuron(double posX, double posY, double posZ, double tau_, double tau_a_, double tau_b_, double gB_, double gL_,
        double W_b_, double W_hb_, double W_a_, double W_ha_, double W_s_, double beta_, double V_th_);

    void update(double S_in_basal, double S_in_apical, double rec, double dt);
    int heaviside(double r, double threshold);
    double sigmoid(double o, double beta);


};
#endif

/**
 * 
 */
/*
class MYPROJECT_API neuron
{
public:
	neuron();
	~neuron();
};
*/

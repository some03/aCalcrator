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
    // ニューロンの位置
    double x, y, z;

    //basal dendrite 基底樹状突起の膜電位
    double V_b; // 基底樹状突起の膜電位
    double tau_b; // 基底樹状突起の時定数
    double W_b;   // 基底側外部入力の重み
    double W_hb;  // 基底側ニューロン入力の重み

    //apical dendrite 頂部樹状突起の膜電位 
    double V_a; // 頂部樹状突起の膜電位
    double tau_a; // 頂部樹状突起の時定数
    double W_a;   // 頂部側外部入力の重み
    double W_ha;  // 頂部側再帰入力の重み

    //soma 細胞体の膜電位
    double U;   // 細胞体の膜電位
    double tau;   // 細胞体の時定数
    double gB;    // 基底コンダクタンス
    double gL;    // 漏れコンダクタンス
    double W_s;   // 細胞体外部入力の重み

    double beta;  // シグモイドの鋭さ
    double V_th;  // スパイク閾値
    int S_h;    // スパイク出力（0または1）
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

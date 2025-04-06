#ifndef LIF_H
#define LIF_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>

// (LIF) ニューロンをシミュレーションする関数
void lif_simulation(
    int    steps,    // シミュレーションのステップ数
    float  dt,       // タイムステップ [ms]
    float  tau,      // 時定数 (τ) [ms]
    float  v_rest,   // 静止膜電位 [mV]
    float  v_reset,  // リセット電位 [mV]
    float  theta,    // 発火閾値 [mV]
    float  R_m,      // 膜抵抗 [MΩ]
    float  I_ext     // 外部電流注入量 [nA]
)
{
    // 初期膜電位を静止膜電位に設定
    float v = v_rest;

    for (int32_t nt = 0; nt < steps; nt++) {
        float t = dt * nt;

        // 電位を出力（ここでは標準出力に時刻 t と電位 v を書き込み）
        printf("%f %f\n", t, v);

        // オイラー法で次ステップの膜電位を計算
        v += dt * ( -(v - v_rest) + R_m * I_ext ) / tau;

        // 閾値を超えるかどうかを判定
        bool spiked = (v > theta);

        // スパイクが起こったら、スパイクイベントを出力
        // （スパイク発火時刻として t + dt を出力し、膜電位を 0 で縦線を描画）
        if (spiked) {
            printf("%f %f\n%f %f\n", t + dt, v, t + dt, 0.0f);
        }

        // 発火した場合はリセット電位へ、そうでなければ計算した電位を維持
        v = spiked ? v_reset : v;
    }
}
#endif // LIF_H
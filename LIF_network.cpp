//randomkit is a C library that implements a number of random number generators.
//distributions is probability distributions.

#include <iostream>
#include<stdlib.h>
#include<math.h>
#include<stdint.h>
#include<stdbool.h>
#include"LIF.h"

#define TAU     (   20.0 ) // ms : ニューロンの膜時定数 (membrane time constant)
#define V_REST  (  -65.0 ) // mV : 静止膜電位 (resting potential)
#define V_RESET (  -65.0 ) // mV : 発火後にリセットされる電位 (reset potential)
#define THETA   (  -55.0 ) // mV : 発火閾値 (threshold)
#define R_M     (    1.0 ) // MOhm: 膜抵抗 (membrane resistance)
#define DT      (    1.0 ) // ms : オイラー法の刻み幅 (time step)
#define T       ( 1000.0 ) // ms : シミュレーション時間(今回は未使用)
#define NT      ( 1000   ) // T / DT : シミュレーションステップ数
#define I_EXT   (   12.0 ) // nA : 外部から与える定電流 (external input current)
#define N       (    2   ) // ニューロンの数
#define TAU_SYN (    5.0 ) // ms : シナプス電流の時定数
#define R_SYN   (    1.0 ) // MOhm: シナプスからの入力に対する抵抗/係数
#define W       (    2.0 ) // シナプス結合の重み (connection weight)

int main(void){


    float v[N] = {V_REST, V_REST-15.}; // 膜電位 (membrane potential)
    float i_sync[N] = {0., 0.}; // シナプス電流 (synaptic current)
    bool spiked[N] = {false, false}; // 発火状態 (spike state)

    for(int nt=0;nt<NT;nt++){
        float t=DT*nt;
        printf("%f %f %f\n", t, v[0], v[1]);

        for(int32_t i=0;i<N;i++){
            i_sync[i] += exp(-DT/TAU_SYN) * i_sync[i]+W*spiked[(i+1)%2];
        }
        for(int32_t i=0;i<N;i++){
            v[i]+=DT*(-(v[i]-V_REST)+R_SYN*i_sync[i]+R_M*I_EXT)/TAU;
            spiked[i] = (v[i] > THETA);
        }

        // Pretty-print spikes on membrane potentials. Note that spike time is not t but t + DT
        if (spiked[0])
        {
            printf("%f %f %f\n%f %f %f\n", t + DT, v[0], v[1], t + DT, 0., v[1]);
        }
        if (spiked[1])
        {
            printf("%f %f %f\n%f %f %f\n", t + DT, v[0], v[1], t + DT, v[0], 0.);
        }

        for(int32_t i=0;i<N;i++){
            v[i]=spiked[i]*V_RESET+(!spiked[i])*v[i];
        }
    }
}

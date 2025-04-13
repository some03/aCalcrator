#include "neuron.h"

MCNNeuron::MCNNeuron(double posX, double posY, double posZ,
                     double tau_, double tau_a_, double tau_b_,
                     double gB_, double gL_,
                     double W_b_, double W_hb_,
                     double W_a_, double W_ha_,
                     double W_s_, double beta_, double V_th_)
    : x(posX), y(posY), z(posZ),
      tau(tau_), tau_a(tau_a_), tau_b(tau_b_),
      gB(gB_), gL(gL_),
      W_b(W_b_), W_hb(W_hb_),
      W_a(W_a_), W_ha(W_ha_),
      W_s(W_s_), beta(beta_), V_th(V_th_),
      V_b(0.0), V_a(0.0), U(0.0), S_h(0)
{}

int MCNNeuron::heaviside(double x, double threshold) {
    return (x >= threshold) ? 1 : 0;
}

double MCNNeuron::sigmoid(double x, double beta) {
    return 1.0 / (1.0 + exp(-beta * x));
}

void MCNNeuron::update(double S_in_basal, double S_in_apical, double rec,double dt) {

    // basal更新
    //vb[t] = vb[t-1] + (W_b * S_in_basal + W_hb * rec_basal - vb[t-1]) / tau_b;
    V_b += (W_b * S_in_basal + W_hb * rec - V_b) / tau_b;

    // apritical更新
    //va[t] = va[t-1] + (W_a * S_in_apical + W_ha * rec_apical - va[t-1]) / tau_a;
    V_a += (W_a * S_in_apical + W_ha * rec - V_a) / tau_a;
    
    // 頂部突起からのゲーティング信号
    double z_signal = sigmoid(V_a, beta);
    
    // soma更新：基底側の入力を主に用いる（W_s * S_in_basal）とする
    double h = (gB / gL) * (V_b - U) + W_s * S_in_basal;
    U += (z_signal * h - U) / tau;
    
    // スパイク出力
    S_h = heaviside(U, V_th);
    if(S_h == 1) {
        stdptime = dt;
    }
}
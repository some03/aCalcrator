#include "neuron.h"
#include "sensorgrid.h"
#include "iogrid.h"
#include <random>
#include <map>
#include <cmath>
#include <iostream>

// シナプスを一意に識別するための構造体
struct Synapse {
    int preNeuronIndex;   // プレシナプスニューロンのインデックス
    int postNeuronIndex;  // ポストシナプスニューロンのインデックス
    bool operator<(const Synapse& other) const {
        if (preNeuronIndex != other.preNeuronIndex)
            return preNeuronIndex < other.preNeuronIndex;
        return postNeuronIndex < other.postNeuronIndex;
    }
};

// 2点間のユークリッド距離を計算
double neuronDistance(int x1, int y1, int z1, int x2, int y2, int z2) {
    return std::sqrt((x1 - x2)*(x1 - x2) +
                     (y1 - y2)*(y1 - y2) +
                     (z1 - z2)*(z1 - z2));
}

// Basal入力を計算（センサーマップの座標は明示的にint型に変換）
double getExternalInputBasal(const MCNNeuron &neuron, uint8_t up, uint8_t leftside, uint8_t rightside,
                             const std::vector<std::vector<int>> &sensorMap,bool isFeedback) {
    int yIdx = static_cast<int>(neuron.y);
    int zIdx = static_cast<int>(neuron.z);

    if (isFeedback)
    {

        if ((neuron.x / 1) == leftside )
        {
            if (sensorMap[yIdx][zIdx] == 1)return 1.0;
            else return 0.0;
        }
        else{
            return 0.0;
        }

    }

    else
    {
        if ((neuron.y / 1) == up - 1)
            return 1.0;
        else if ((neuron.x / 1) == rightside - 1)
        {
            if (sensorMap[yIdx][zIdx] == 1)return 1.0;
            else return 0.0;
        }
        else{
            return 0.0;
        }
    }
}

// Apical入力を計算
double getExternalInputApical(const MCNNeuron &neuron, uint8_t up, uint8_t leftside, uint8_t rightside,
                              const std::vector<std::vector<int>> &sensorMap,bool isFeedback) {
    int yIdx = static_cast<int>(neuron.y);
    int zIdx = static_cast<int>(neuron.z);
    
    
    
    if (isFeedback)
    {

        if ((neuron.x / 1) <= leftside +1)
        {
            if (sensorMap[yIdx][zIdx] == 1)return 1.0;
            else return 0.0;
        }
        else{
            return 0.0;
        }

    }

    else
    {
        if ((neuron.y / 1) >= up - 2)
            return 1.0;
        else if ((neuron.x/1)>=rightside-2&&(neuron.x / 1) <= rightside - 1)
        {
            if (sensorMap[yIdx][zIdx] == 1)return 1.0;
            else return 0.0;
        }
        else{
            return 0.0;
        }
    }
    
}

// 再帰的入力（再帰結合）の計算  
// 現在のニューロンのインデックス(currentIndex)を明示的に渡すことで、自身の入力を無視する
double getRecInput(int currentIndex, const std::vector<MCNNeuron> &neurons,
                   const std::map<Synapse, int> &synapses) {
    double rec = 0.0;
    for (size_t i = 0; i < neurons.size(); i++) {
        if (static_cast<int>(i) == currentIndex)
            continue;
        // シナプスキーは {currentIndex, i} として検索
        Synapse key{currentIndex, static_cast<int>(i)};
        auto it = synapses.find(key);
        if (it != synapses.end()) {
            rec += it->second * neurons[i].S_h;
        }
    }
    return rec;
}

// センサーマップに基づいて、該当領域内のニューロン数を数える
int countNeuronsInRegion(const std::vector<MCNNeuron> &neurons,
                         const std::vector<std::vector<int>> &sensorMap) {
    int count = 0;
    for (const MCNNeuron &neuron : neurons) {
        int yIdx = static_cast<int>(neuron.y);
        int zIdx = static_cast<int>(neuron.z);
        if (sensorMap[yIdx][zIdx] == 1)count++;
    }
    return count;
}

// STDPの更新ルールに基づいてシナプスの重みを更新
void stdpUpdate(std::map<Synapse, int> &synapses, const std::vector<MCNNeuron> &neurons) {
    double A_plus = 0.005;   // 増加の学習率
    double A_minus = 0.005;  // 減少の学習率
    double tau_plus = 20.0;  // 増加の時間定数
    double tau_minus = 20.0; // 減少の時間定数
    double limit = 5;        // シナプス重み上限

    for (auto &item : synapses) {
        int preIndex = item.first.preNeuronIndex;
        int postIndex = item.first.postNeuronIndex;

        double delta_t = neurons[postIndex].stdptime - neurons[preIndex].stdptime;
        if (delta_t > 0)
            item.second += static_cast<int>(A_plus * std::exp(-delta_t / tau_plus));
        else
            item.second -= static_cast<int>(A_minus * std::exp(delta_t / tau_minus));

        if (item.second > limit)
            item.second = limit;
        else if (item.second < 0)
            item.second = 0;
    }
}

int main() {

    // 立方体のサイズ
    const int zyN = 8;
    const int xN = 8;
    std::vector<MCNNeuron> neurons;
    std::map<Synapse, int> synapses;
    int neuron_limit = 100;  // 指定領域内のニューロン数の上限
    const int time_steps = 50;
    const int dt = 1;  // dt=1なら時間変数はintで問題なし
    int count = 0;

    double tau = 2.0, tau_a = 2.0, tau_b = 2.0;
    double gB = 1.0, gL = 1.0;
    double W_b = 0.8, W_hb = 0.5, W_a = 0.7, W_ha = 0.5, W_s = 0.9;
    double beta = 1.0, V_th = 1.0;

    int midinote = 120;
    SensorGrid sensorGrid(zyN);
    SensorGrid feedbackGrid(zyN);
    std::vector<std::vector<int>> inputsensor = sensorGrid.createBitmap(midinote);
    std::vector<std::vector<int>> feedbacksensor; // 初期状態では空、後で更新

    IoGrid ioGrid(zyN, xN);

    int sensorNeuronNum = 0;
    int ioNeuronNum = 0;
    int oldNeuronNum = 0;

    // センサーニューロンの配置（x位置が0とxNに配置）
    for (double y = 0; y < zyN; y += 0.4) {
        for (double z = 0; z < zyN; z += 0.4) {
            neurons.emplace_back(0, y, z, tau, tau_a, tau_b,
                                 gB, gL, W_b, W_hb, W_a, W_ha, W_s, beta, V_th);
            neurons.emplace_back(xN-1, y, z, tau, tau_a, tau_b,
                                 gB, gL, W_b, W_hb, W_a, W_ha, W_s, beta, V_th);
        }
    }
    sensorNeuronNum = static_cast<int>(neurons.size());

    // 入出力ニューロンの配置（y=0とy=zyN）
    for (double x = 0; x < xN; x += 0.4) {
        for (double z = 0; z < zyN; z += 0.4) {
            neurons.emplace_back(x, 0, z, tau, tau_a, tau_b,
                                 gB, gL, W_b, W_hb, W_a, W_ha, W_s, beta, V_th);
            neurons.emplace_back(x, zyN-1, z, tau, tau_a, tau_b,
                                 gB, gL, W_b, W_hb, W_a, W_ha, W_s, beta, V_th);
        }
    }
    ioNeuronNum = static_cast<int>(neurons.size()) - sensorNeuronNum;

    // シナプスの初期化：全ニューロンのペアについて距離に基づき初期重みを設定
    for (size_t i = 0; i < neurons.size() - 1; i++) {
        for (size_t j = i + 1; j < neurons.size(); j++) {
            double d = neuronDistance(static_cast<int>(neurons[i].x), static_cast<int>(neurons[i].y),
                                      static_cast<int>(neurons[i].z),
                                      static_cast<int>(neurons[j].x), static_cast<int>(neurons[j].y),
                                      static_cast<int>(neurons[j].z));
            Synapse key{ static_cast<int>(i), static_cast<int>(j) };
            if (d <= 1 || (d >= 2.0 && d <= 3.0))
                synapses[key] = 1;
            else
                synapses[key] = 0;
        }
    }
    oldNeuronNum = static_cast<int>(neurons.size());

    bool isFeedback = false;

    // 時間ステップのループ
    for (int t = 0; t < time_steps; t += dt) {
        std::vector<double> s_in_basal(sensorNeuronNum, 0.0);
        std::vector<double> s_in_apical(sensorNeuronNum, 0.0);

        //std::cout << "count: " << count << std::endl;
       

        // センサーマップの更新と入力値の取得
        if (isFeedback) {
            feedbacksensor = feedbackGrid.createBitmap(ioGrid.getSpikeCounts());
            count = countNeuronsInRegion(neurons, feedbacksensor);
            for (size_t i = 0; i < neurons.size(); i++) {
                s_in_basal[i % sensorNeuronNum] = getExternalInputBasal(neurons[i], zyN, 0, xN, feedbacksensor, isFeedback);
                s_in_apical[i % sensorNeuronNum] = getExternalInputApical(neurons[i], zyN, 0, xN, feedbacksensor,isFeedback);
            }
            isFeedback = false;
        }
        else {
            count = countNeuronsInRegion(neurons, inputsensor);
            for (size_t i = 0; i < neurons.size(); i++) {
                s_in_basal[i % sensorNeuronNum] = getExternalInputBasal(neurons[i], zyN, 0, xN, inputsensor, isFeedback);
                s_in_apical[i % sensorNeuronNum] = getExternalInputApical(neurons[i], zyN, 0, xN, inputsensor,isFeedback);
            }
            std::cout<<"s_in_basal: "<<s_in_basal[0]<<" s_in_apical: "<<s_in_apical[0]<<std::endl;
            //isFeedback = true;
        }
        /*

        // ニューロンの更新と再帰入力の計算
        for (size_t i = 0; i < neurons.size(); i++) {
            double rec = getRecInput(static_cast<int>(i), neurons, synapses);
            neurons[i].update(s_in_basal[i % sensorNeuronNum], s_in_apical[i % sensorNeuronNum], rec, dt);
            // 出力ニューロンのスパイクを記録（例：y==0 のニューロン）
            if (neurons[i].S_h == 1 && neurons[i].y == 0) {
                ioGrid.recordSpike(static_cast<int>(neurons[i].y), static_cast<int>(neurons[i].x));
            }
        }
        // STDPによるシナプスの更新
        stdpUpdate(synapses, neurons);

        // 一定数（指定領域内）を超えた場合、新規ニューロンの追加
        if (count > neuron_limit) {
            std::vector<MCNNeuron> newNeurons;
            // ループ変数名の衝突を避けるため別名を使用
            for (int r = 0; r < 5; r++) {
                if (isFeedback) {
                    for (size_t row = 0; row < feedbacksensor.size(); row++) {
                        for (size_t col = 0; col < feedbacksensor[row].size(); col++) {
                            if (feedbacksensor[row][col] == 1) {
                                std::random_device rd;
                                std::mt19937 mt(rd());
                                std::uniform_real_distribution<double> disty(row - 1, row);
                                std::uniform_real_distribution<double> distz(col - 1, col);
                                std::uniform_real_distribution<double> distx(0, xN);
                                newNeurons.emplace_back(distx(mt), disty(mt), distz(mt),
                                                         tau, tau_a, tau_b,
                                                         gB, gL, W_b, W_hb, W_a, W_ha, W_s, beta, V_th);
                            }
                        }
                    }
                }
                else {
                    for (size_t row = 0; row < inputsensor.size(); row++) {
                        for (size_t col = 0; col < inputsensor[row].size(); col++) {
                            if (inputsensor[row][col] == 1) {
                                std::random_device rd;
                                std::mt19937 mt(rd());
                                std::uniform_real_distribution<double> disty(row - 1, row);
                                std::uniform_real_distribution<double> distz(col - 1, col);
                                std::uniform_real_distribution<double> distx(0, xN);
                                newNeurons.emplace_back(distx(mt), disty(mt), distz(mt),
                                                         tau, tau_a, tau_b,
                                                         gB, gL, W_b, W_hb, W_a, W_ha, W_s, beta, V_th);
                            }
                        }
                    }
                }
            }
            // 追加したニューロンを全体に統合
            neurons.insert(neurons.end(), newNeurons.begin(), newNeurons.end());

            // 新規接続の生成：既存ニューロンと新規ニューロンの間にシナプスを生成
            for (size_t i = 0; i < neurons.size() - 1; i++) {
                for (size_t j = oldNeuronNum; j < neurons.size(); j++) {
                    double d = neuronDistance(static_cast<int>(neurons[i].x), static_cast<int>(neurons[i].y),
                                              static_cast<int>(neurons[i].z),
                                              static_cast<int>(neurons[j].x), static_cast<int>(neurons[j].y),
                                              static_cast<int>(neurons[j].z));
                    Synapse key{ static_cast<int>(i), static_cast<int>(j) };
                    if (d <= 1 || (d >= 2.0 && d <= 3.0))
                        synapses[key] = 1;
                    else
                        synapses[key] = 0;
                }
            }
            oldNeuronNum = static_cast<int>(neurons.size());
        }
            */
    }
        

    return 0;
}

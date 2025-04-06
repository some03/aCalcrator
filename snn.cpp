#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>

// ==================== パラメータ ====================
static const int NUM_INPUT_NEURONS = 5;   // 入力層のニューロン数
static const int NUM_HIDDEN_NEURONS = 5; // 中間層のニューロン数

static const double DT = 0.1;         // タイムステップ幅[msなど]
static const int TOTAL_TIME_STEPS = 100; // シミュレーションを行うステップ数

// LIFニューロンモデルのパラメータ
static const double TAU = 20.0;          // 膜時定数
static const double V_REST = -65.0;      // 静止電位
static const double V_RESET = -65.0;     // リセット電位
static const double V_THRESHOLD = -50.0; // 閾値

// 入力ニューロンが自発的にスパイクを出す確率(1ステップあたり)
static const double INPUT_SPIKE_PROB = 0.2;

// シナプス重みの最大値（ランダム生成の上限）
static const double MAX_WEIGHT = 5.0;


// ==================== ニューロンクラス ====================
class LIFNeuron {
private:
    double membranePotential_; // 膜電位
    bool spiked_;             // このステップでスパイクが発生したか

public:
    LIFNeuron() {
        membranePotential_ = V_REST;
        spiked_ = false;
    }

    // 膜電位を返す
    double getPotential() const {
        return membranePotential_;
    }

    // スパイクしているかを返す
    bool hasSpiked() const {
        return spiked_;
    }

    // 外部からの入力電流 I_in を与えて膜電位を更新
    void update(double I_in) {
        // 前回のスパイクフラグをリセット
        spiked_ = false;

        // LIFの近似更新式
        // dV/dt = (-(V - V_rest) + I_in) / tau
        // V(t+dt) = V(t) + dt * dV/dt
        double dV = (-(membranePotential_ - V_REST) + I_in) / TAU;
        membranePotential_ += dV * DT;

        // 閾値チェック
        if (membranePotential_ >= V_THRESHOLD) {
            // スパイク発火
            spiked_ = true;
            // 膜電位リセット
            membranePotential_ = V_RESET;
        }
    }
};


// ==================== ネットワーククラス ====================
class TwoLayerSNN {
private:
    // 層ごとにニューロンを保持
    std::vector<LIFNeuron> inputLayer_;
    std::vector<LIFNeuron> hiddenLayer_;

    // シナプス重み (input -> hidden)
    // weights_[i][j] は i番目の入力ニューロンから j番目の中間ニューロンへの重み
    std::vector<std::vector<double>> weights_;

public:
    TwoLayerSNN() {
        // 入力層ニューロンの確保
        inputLayer_.resize(NUM_INPUT_NEURONS);
        // 中間層ニューロンの確保
        hiddenLayer_.resize(NUM_HIDDEN_NEURONS);

        // シナプス重みの初期化（ランダム）
        weights_.resize(NUM_INPUT_NEURONS, std::vector<double>(NUM_HIDDEN_NEURONS));
        initializeRandomWeights();
    }

    // シナプス重みをランダムに初期化する
    void initializeRandomWeights() {
        std::mt19937 rng(std::time(nullptr));
        std::uniform_real_distribution<double> dist(0.0, MAX_WEIGHT);

        for(int i = 0; i < NUM_INPUT_NEURONS; i++){
            for(int j = 0; j < NUM_HIDDEN_NEURONS; j++){
                weights_[i][j] = dist(rng);
            }
        }
    }

    // 入力層への擬似スパイク（外部刺激）を生成
    void generateInputSpikes() {
        static std::mt19937 rng(std::time(nullptr));
        static std::uniform_real_distribution<double> dist(0.0, 1.0);

        for(int i = 0; i < NUM_INPUT_NEURONS; i++) {
            // 入力層のニューロンに、確率 INPUT_SPIKE_PROB でスパイクを発火させる
            // 実際には無理やり膜電位を閾値を超える形にしてスパイクさせても良いが、
            // ここでは update() を使って発火フラグが立つようにする。
            double randVal = dist(rng);
            if (randVal < INPUT_SPIKE_PROB) {
                // 大きな入力電流を与えてスパイクを誘発
                inputLayer_[i].update(100.0);  
            } else {
                // 入力がない場合は I_in = 0
                inputLayer_[i].update(0.0);
            }
        }
    }

    // ネットワーク全体の1ステップ更新
    void updateNetwork() {
        // 1) 入力層を更新（すでに generateInputSpikes() で更新済みの場合はスキップ可）
        // 今回は外部入力を別途与えないのでここは空でも良い

        // 2) 入力層のスパイクに基づいて中間層への入力電流を計算
        std::vector<double> hiddenInput(NUM_HIDDEN_NEURONS, 0.0);
        for(int i = 0; i < NUM_INPUT_NEURONS; i++){
            if(inputLayer_[i].hasSpiked()){
                for(int j = 0; j < NUM_HIDDEN_NEURONS; j++){
                    hiddenInput[j] += weights_[i][j];
                }
            }
        }

        // 3) 中間層ニューロンを更新
        for(int j = 0; j < NUM_HIDDEN_NEURONS; j++){
            hiddenLayer_[j].update(hiddenInput[j]);
        }
    }

    // デバッグ用：各ステップでのスパイク状況を表示
    void printSpikes(int step) const {
        // 入力層
        std::cout << "Step " << step << " | Input spiked: [ ";
        for(int i = 0; i < NUM_INPUT_NEURONS; i++){
            std::cout << (inputLayer_[i].hasSpiked() ? "1 " : "0 ");
        }
        std::cout << "]  | Hidden spiked: [ ";
        for(int j = 0; j < NUM_HIDDEN_NEURONS; j++){
            std::cout << (hiddenLayer_[j].hasSpiked() ? "1 " : "0 ");
        }
        std::cout << "]" << std::endl;
    }
};


// ==================== メイン関数 ====================
int main() {
    // ネットワーク生成
    TwoLayerSNN snn;

    // シミュレーションループ
    for(int t = 0; t < TOTAL_TIME_STEPS; t++){
        // 1) 入力層のスパイク生成（外部入力の疑似）
        snn.generateInputSpikes();

        // 2) ネットワーク全体を1ステップ更新
        snn.updateNetwork();

        // 3) スパイク状況を出力
        snn.printSpikes(t);
    }

    return 0;
}

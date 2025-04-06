#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>

// ユークリッド距離を計算する関数
double distance3D(int x1, int y1, int z1, int x2, int y2, int z2) {
    return std::sqrt((x1 - x2)*(x1 - x2) +
                     (y1 - y2)*(y1 - y2) +
                     (z1 - z2)*(z1 - z2));
}

// マンハッタン距離を計算する関数
int manhattanDistance(int x1, int y1, int z1, int x2, int y2, int z2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2) + std::abs(z1 - z2);
}

// Heaviside関数：入力が閾値以上なら1、未満なら0
int heaviside(double x, double threshold = 1.0) {
    return (x >= threshold) ? 1 : 0;
}

// Sigmoid関数：ゲーティング信号用
double sigmoid(double x, double beta) {
    return 1.0 / (1.0 + std::exp(-beta * x));
}

// マルチコンパートメントニューロン（MCN）クラス
class MCNNeuron {
public:
    // 位置情報（立方体内の座標）
    int x, y, z;

    // パラメータ
    double tau;    // ソーマの減衰定数
    double tau_a;  // 頂部樹状突起の減衰定数
    double tau_b;  // 基底樹状突起の減衰定数
    double gB;     // 基底伝導
    double gL;     // 漏れ伝導
    double W_b;    // 基底側外部入力の重み
    double W_hb;   // 基底側再帰入力の重み
    double W_a;    // 頂部側外部入力の重み
    double W_ha;   // 頂部側再帰入力の重み
    double W_s;    // ソーマ側外部入力の重み（通常基底側入力を用いる）
    double beta;   // シグモイドの鋭さ
    double V_th;   // スパイク閾値

    // 状態変数
    double V_b;    // 基底樹状突起の膜電位
    double V_a;    // 頂部樹状突起の膜電位
    double U;      // ソーマの膜電位
    int S_h;       // スパイク出力（0または1）

    // コンストラクタ：位置情報とパラメータを初期化
    MCNNeuron(int posX, int posY, int posZ,
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
          V_b(0.0), V_a(0.0), U(0.0), S_h(0) {}

    // 1ステップの更新関数
    // S_in_basal：基底側の外部入力
    // S_in_apical：頂部側の外部入力（例：面からの電流）
    // rec_basal：基底側（近傍）からの再帰入力
    // rec_apical：頂部側（遠方）からの再帰入力
    void update(double S_in_basal, double S_in_apical, double rec_basal, double rec_apical) {
        // 基底突起更新
        double new_V_b = V_b + (W_b * S_in_basal + W_hb * rec_basal - V_b) / tau_b;
        // 頂部突起更新
        double new_V_a = V_a + (W_a * S_in_apical + W_ha * rec_apical - V_a) / tau_a;
        
        // 頂部突起からのゲーティング信号
        double z_signal = sigmoid(new_V_a, beta);
        
        // ソーマ更新：基底側の入力を主に用いる（W_s * S_in_basal）とする
        double h = (gB / gL) * (new_V_b - U) + W_s * S_in_basal;
        double new_U = U + (z_signal * h - U) / tau;
        
        // スパイク出力
        int new_S_h = heaviside(new_U, V_th);
        
        // 状態更新
        V_b = new_V_b;
        V_a = new_V_a;
        U = new_U;
        S_h = new_S_h;
    }

    // 状態を表示する関数
    void printState(int t) const {
        std::cout << "Neuron (" << x << "," << y << "," << z << ") "
                  << "Time " << t << ": U = " << U
                  << ", S_h = " << S_h << std::endl;
    }
};

int main() {
    // 立方体のサイズ（例：3x3x3）
    const int N = 3;
    
    // ニューロンパラメータ（例として任意の値）
    double tau = 2.0, tau_a = 2.0, tau_b = 2.0;
    double gB = 1.0, gL = 1.0;
    double W_b = 0.8, W_hb = 0.5, W_a = 0.7, W_ha = 0.5, W_s = 0.9;
    double beta = 1.0, V_th = 1.0;
    
    // 立方体内にニューロン群を配置
    std::vector<MCNNeuron> neurons;
    for (int x = 0; x < N; ++x) {
        for (int y = 0; y < N; ++y) {
            for (int z = 0; z < N; ++z) {
                neurons.emplace_back(x, y, z, tau, tau_a, tau_b,
                                     gB, gL, W_b, W_hb, W_a, W_ha, W_s, beta, V_th);
            }
        }
    }
    
    // シミュレーションステップ数
    const int T = 20;
    
    // 外部入力の条件設定：
    // 基底側外部入力 S_in_basal：底面 (z==0) のみ受け取る
    // 頂部側外部入力 S_in_apical：上面 (z==N-1) または x==N-1 の面にあるニューロンが受け取る
    auto getExternalInputBasal = [&](const MCNNeuron &neuron) -> double {
        if (neuron.z == 0) return 1.0;
        return 0.0;
    };
    auto getExternalInputApical = [&](const MCNNeuron &neuron) -> double {
        if (neuron.z == N - 1 || neuron.x == N - 1) return 1.0;
        return 0.0;
    };
    
    // 再帰入力の条件設定：
    // 基底側再帰入力 rec_basal：近傍（マンハッタン距離が1以内）のニューロンからのスパイク出力の和
    // 頂部側再帰入力 rec_apical：遠方（ユークリッド距離が2以上）のニューロンからのスパイク出力の和
    auto getBasalRecInput = [&](const MCNNeuron &current) -> double {
        double rec_basal = 0.0;
        for (const auto &other : neurons)
        {
            if (current.x == other.x && current.y == other.y && current.z == other.z)
                continue;
            if (manhattanDistance(current.x, current.y, current.z, other.x, other.y, other.z) <= 1)
                rec_basal += other.S_h;
        }
        return rec_basal;
    };
    auto getApicalRecInput = [&](const MCNNeuron &current) -> double {
        double rec_apical = 0.0;
        for (const auto &other : neurons) {
            if (current.x == other.x && current.y == other.y && current.z == other.z)
                continue;
            double d = distance3D(current.x, current.y, current.z, other.x, other.y, other.z);
            if (d >= 2.0)
                rec_apical += other.S_h;
        }
        return rec_apical;
    };
    
    // シミュレーションループ
    for (int t = 0; t < T; ++t) {
        // 各ニューロンごとに再帰入力を計算（更新前の状態を用いる）
        std::vector<double> basalRec(neurons.size(), 0.0);
        std::vector<double> apicalRec(neurons.size(), 0.0);
        for (size_t i = 0; i < neurons.size(); ++i) {
            basalRec[i] = getBasalRecInput(neurons[i]);
            apicalRec[i] = getApicalRecInput(neurons[i]);
        }
        
        // 各ニューロンを更新：外部入力は位置により分割
        for (size_t i = 0; i < neurons.size(); ++i) {
            double S_in_basal = getExternalInputBasal(neurons[i]);
            double S_in_apical = getExternalInputApical(neurons[i]);
            neurons[i].update(S_in_basal, S_in_apical, basalRec[i], apicalRec[i]);
        }
        
        // 状態を表示
        std::cout << "Time step " << t << std::endl;
        for (const auto &neuron : neurons) {
            neuron.printState(t);
        }
        std::cout << "--------------------------" << std::endl;
    }
    
    return 0;
}

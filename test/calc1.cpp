#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

#define MAX_NEURONS 1000    // ニューロンの上限
#define MAX_SLOTS   4       // 各ニューロンの最大入力/出力スロット数

// 近傍距離 (R以内なら接続を検討)
#define R         5.0f

// LIFパラメータ (単純化)
#define V_INIT    -60.0f
#define V_REST    -65.0f
#define V_RESET   -65.0f
#define V_THRESH  -50.0f
#define TAU_M     20.0f
#define DT        1.0f      // タイムステップ 1ms

// -----------------------
// ニューロン構造体
// -----------------------
typedef struct {
    float x, y, z;                  // 座標
    int   inCount,  outCount;       // 入/出力スロットが埋まっている数
    int   inIDs[MAX_SLOTS];         // 入力元ニューロンID
    int   outIDs[MAX_SLOTS];        // 出力先ニューロンID

    float v;                        // LIF膜電位
    bool  spike;                    // このステップでスパイクしたか
} LIFNeuron3D;

static LIFNeuron3D neurons[MAX_NEURONS]; // ニューロン配列
static int neuronCount = 0;             // 現在のニューロン数

float distance3D(float x1, float y1, float z1, float x2, float y2, float z2)
{
    float dx = x1 - x2;
    float dy = y1 - y2;
    float dz = z1 - z2;
    return sqrtf(dx*dx + dy*dy + dz*dz);
}

void addNeuronAndConnect(void)
{
    if(neuronCount >= MAX_NEURONS){
        printf("ERROR: neuronCount exceeds MAX_NEURONS\n");
        return;
    }
    // -------------------------------
    // 1) 新ニューロンをランダム配置
    // -------------------------------
    LIFNeuron3D newN;
    newN.x = (float)(rand() % 100); // 0〜99の範囲でランダム
    newN.y = (float)(rand() % 100);
    newN.z = (float)(rand() % 100);

    newN.inCount  = 0;
    newN.outCount = 0;

    // LIF初期化
    newN.v     = V_INIT;
    newN.spike = false;

    // -------------------------------
    // 2) 既存ニューロンと近傍接続
    // -------------------------------
    for(int i = 0; i < neuronCount; i++){
        float dist = distance3D(newN.x, newN.y, newN.z,
                                neurons[i].x, neurons[i].y, neurons[i].z);
        if(dist <= R){
            // newN -> i (空きスロットチェック)
            if(newN.outCount < MAX_SLOTS && neurons[i].inCount < MAX_SLOTS){
                // 接続
                newN.outIDs[newN.outCount] = i;
                neurons[i].inIDs[neurons[i].inCount] = neuronCount; 
                newN.outCount++;
                neurons[i].inCount++;
            }
            // i -> newN
            if(neurons[i].outCount < MAX_SLOTS && newN.inCount < MAX_SLOTS){
                neurons[i].outIDs[neurons[i].outCount] = neuronCount;
                newN.inIDs[newN.inCount] = i;
                neurons[i].outCount++;
                newN.inCount++;
            }
        }
    }

    // -------------------------------
    // 3) グローバル配列に登録
    // -------------------------------
    neurons[neuronCount] = newN;
    neuronCount++;
}

void propagateSpikes(float *inputCurrent)
{
    // まずゼロクリア
    for(int i=0; i<neuronCount; i++){
        inputCurrent[i] = 0.0f;
    }

    // 各ニューロン j がスパイクしていたら、その outIDs に電流を注入
    for(int j=0; j<neuronCount; j++){
        if(neurons[j].spike){
            // j の outスロットをたどる
            for(int k=0; k<neurons[j].outCount; k++){
                int postID = neurons[j].outIDs[k];
                // postID の入力電流を1加算
                // (重みがあるなら weight を加算する)
                inputCurrent[postID] += 1.0f;
            }
        }
    }
}

void updateLIFNeurons(const float *inputCurrent)
{
    for(int i=0; i<neuronCount; i++){
        // まずスパイクフラグをクリア
        neurons[i].spike = false;

        // dv/dt = - (v - V_REST)/TAU_M + (inputCurrent[i]) / TAU_M
        float dv = ( - (neurons[i].v - V_REST) + inputCurrent[i] )
                   / TAU_M;
        neurons[i].v += DT * dv;

        // 閾値判定
        if(neurons[i].v >= V_THRESH){
            neurons[i].spike = true;
            neurons[i].v = V_RESET; 
        }
    }
}
int main(void)
{
    srand((unsigned)time(NULL));

    // 全ニューロン初期化
    neuronCount = 0;
    for(int i=0; i<MAX_NEURONS; i++){
        neurons[i].inCount  = 0;
        neurons[i].outCount = 0;
        neurons[i].v        = V_INIT;
        neurons[i].spike    = false;
    }

    // -----------------------------
    // 1) まず30個のニューロンを生成
    // -----------------------------
    int initialNum = 30;
    for(int n=0; n < initialNum; n++){
        addNeuronAndConnect();
    }
    printf("%d neurons created.\n", neuronCount);

    // -----------------------------
    // 2) シミュレーションループ
    //    途中でニューロンを追加し続ける例
    // -----------------------------
    float inputCurrent[MAX_NEURONS];
    int totalSteps = 100;
    for(int t=0; t < totalSteps; t++){
        // (例) 20ステップごとに新しいニューロンを追加
        if((t % 20 == 0) && (neuronCount < MAX_NEURONS)){
            addNeuronAndConnect();
            printf("Step %d: Added one neuron, total=%d\n", t, neuronCount);
        }

        // スパイク伝搬
        propagateSpikes(inputCurrent);

        // LIF更新
        updateLIFNeurons(inputCurrent);

        // 観測・ログ出力(例)
        // スパイク数を数える
        int spikeCount=0;
        for(int i=0; i<neuronCount; i++){
            if(neurons[i].spike) spikeCount++;
        }
        printf("Step %d: spikeCount=%d\n", t, spikeCount);
    }

    // -----------------------------
    // 3) 終了時に状況を表示
    // -----------------------------
    printf("Final neuronCount = %d\n", neuronCount);
    for(int i=0; i<neuronCount; i++){
        printf("Neuron %d: pos(%.1f,%.1f,%.1f), in=%d, out=%d, v=%.2f\n",
               i, neurons[i].x, neurons[i].y, neurons[i].z,
               neurons[i].inCount, neurons[i].outCount,
               neurons[i].v);
    }

    return 0;
}




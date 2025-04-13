#include "neuron.h"
#include<random>
#include<map>


struct Synapse {
    int preNeuronIndex; // プレシナプスニューロンのインデックス
    int postNeuronIndex; // ポストシナプスニューロンのインデックス
};

double  neuronDistance(int x1, int y1, int z1, int x2, int y2, int z2) {
    return std::sqrt((x1 - x2)*(x1 - x2) +(y1 - y2)*(y1 - y2) +(z1 - z2)*(z1 - z2));
}

double getExternalInputBasal(const MCNNeuron &neuron,uint8_t up,uint8_t leftside,uint8_t rightside,uint8_t min[2],uint8_t max[2]) {
    if (neuron.y == up) return 1.0;
    else if(neuron.x==leftside||neuron.x==rightside) {
        if (neuron.y >= min[0] && neuron.y <= max[0] && neuron.z >= min[1] && neuron.z <= max[1])return 1.0;
        return 0.0;
    }
    return 0.0;
}
double getExternalInputApical(const MCNNeuron &neuron,uint8_t up,uint8_t leftside,uint8_t rightside,uint8_t min[2],uint8_t max[2]) {
    if (neuron.y >= up-1)return 1.0;
    else if(neuron.x<=leftside+1||neuron.x>=rightside-1) {
        if(neuron.y >= min[0] && neuron.y <= max[0] && neuron.z >= min[1] && neuron.z <= max[1])return 1.0;
        return 0.0;
    }
    return 0.0;
}

double getRecInput(const MCNNeuron &current, const std::vector<MCNNeuron> &neurons,std::map<Synapse, int> &synapses) {
    double rec = 0.0;

    for (const auto &other : neurons) {

        if (current.x == current.x && current.y == other.y && current.z == other.z)continue;
        rec += synapses[{current.index,other.index}]*other.S_h;

    }
    return rec;
}

int countNeuronsInRegion(const std::vector<MCNNeuron> &neurons, int8_t min[2], int8_t max[2]) {
    int count = 0;
    for (const auto &neuron : neurons) {
        if (neuron.y >= min[1] && neuron.y <= max[1] &&neuron.z >= min[0] && neuron.z <= max[0] )
        {
            count++;
        }
    }
    return count;
}

void stdpUpdate(std::map<Synapse, int> &synapses, const std::vector<MCNNeuron> &neurons) {
    // STDPの更新ルールに基づいてシナプスの重みを更新
    double delta_t = 0.1; // 時間差
    double A_plus = 0.005; // 増加の学習率
    double A_minus = 0.005; // 減少の学習率
    double tau_plus = 20.0; // 増加の時間定数
    double tau_minus = 20.0; // 減少の時間定数
    double limit = 5; // シナプスの重みの上限

    for(const auto &synapse : synapses) {
        int preIndex = synapse.first.preNeuronIndex;
        int postIndex = synapse.first.postNeuronIndex;

        delta_t = neurons[postIndex].stdptime - neurons[preIndex].stdptime;
        if (delta_t > 0) {
            synapses[{preIndex,postIndex}] += A_plus * exp(-delta_t / tau_plus);
        } else {
            synapses[{preIndex,postIndex}] -= A_minus * exp(delta_t / tau_minus);
        }
        
        // シナプスの重みを制限
        if (synapses[{preIndex,postIndex}] > limit) {
            synapses[{preIndex,postIndex}] = limit;
        } else if (synapses[{preIndex,postIndex}] < 0) {
            synapses[{preIndex,postIndex}] = 0;
        }

    }

}

int main(){

    //立方体のサイズ 
    const int zyN = 8;
    const int xN = 32;
    std::vector<MCNNeuron> neurons;
    std::map<Synapse, int> synapses;
    int neuron_rimit = 100;
    const int time_steps = 20;
    const int dt = 0.1;
    int count = 0;
    int index = 0;

    double tau = 2.0, tau_a = 2.0, tau_b = 2.0;
    double gB = 1.0, gL = 1.0;
    double W_b = 0.8, W_hb = 0.5, W_a = 0.7, W_ha = 0.5, W_s = 0.9;
    double beta = 1.0, V_th = 1.0;
    
    //立方体の上面、左側面、右側面に初期ニューロンを配置
    for (int x = 0; x < xN; 0.1) {
        for (int y = 0; y < zyN; 0.1) {
            for (int z = 0; z < zyN; 0.1) {
                neurons.emplace_back(x, y, z, tau, tau_a, tau_b,
                                     gB, gL, W_b, W_hb, W_a, W_ha, W_s, beta, V_th,index);
                index++;
            }
        }
    }


    for (int i = 0; i < neurons.size()-1; i++)
    {
        for (int j=1;j<neurons.size();j++)
        {
            double d = neuronDistance(neurons[i].x, neurons[i].y, neurons[i].z, neurons[j].x, neurons[j].y, neurons[j].z);
            if (d<=1||(d >= 2.0 && d <= 3.0))synapses[{i,j}] = 1; // シナプスの重みを1に設定
            else synapses[{i,j}] = 0; // シナプスの重みを1に設定
        }
    }

    

    for (int t = 0; t < time_steps; dt)
    {

        //generate patarn
        int8_t min[2] = {0,0};//tentative value
        int8_t max[2] = {zyN-1,zyN-1};//tentative value

        
        
        
        
        //last process 
        count = countNeuronsInRegion(neurons, min, max);
        if (count > neuron_rimit)
        {

            std::vector<MCNNeuron> newneurons;
            for (int i = 0; i < 5; i++)
            {

                std::random_device rd;
                std::mt19937 mt(rd());
                std::uniform_real_distribution<double> disty(min[0], max[0]);
                std::uniform_real_distribution<double> distz(min[1], max[1]);
                std::uniform_real_distribution<double> distx(0, xN);

                newneurons.emplace_back(distx, disty, distz, tau, tau_a, tau_b,
                                        gB, gL, W_b, W_hb, W_a, W_ha, W_s, beta, V_th);
            }
            neurons.insert(neurons.end(), newneurons.begin(), newneurons.end());
        }
    }

    return 0;

}
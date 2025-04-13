#include "neuron.h"
#include "sensorgrid.h"
#include "iogrid.h"
#include<random>
#include<map>


struct Synapse {
    int preNeuronIndex; // プレシナプスニューロンのインデックス
    int postNeuronIndex; // ポストシナプスニューロンのインデックス
    bool operator<(const Synapse& other) const {
        if (preNeuronIndex != other.preNeuronIndex) {
            return preNeuronIndex < other.preNeuronIndex;
        }
        return postNeuronIndex < other.postNeuronIndex;
    }
};

double  neuronDistance(int x1, int y1, int z1, int x2, int y2, int z2) {
    return std::sqrt((x1 - x2)*(x1 - x2) +(y1 - y2)*(y1 - y2) +(z1 - z2)*(z1 - z2));
}

double getExternalInputBasal(const MCNNeuron &neuron,uint8_t up,uint8_t leftside,uint8_t rightside,std::vector<std::vector<int>> &inputsensor) {
    if (neuron.y == up) return 1.0;
    else if(neuron.x==leftside||neuron.x==rightside) {
        if(inputsensor[neuron.y/1][neuron.z/1] == 1) return 1.0;
        else return 0.0;
    }
    else return 0.0;
}
double getExternalInputApical(const MCNNeuron &neuron,uint8_t up,uint8_t leftside,uint8_t rightside,std::vector<std::vector<int>> &inputsensor) {
    if (neuron.y >= up-1)return 1.0;
    else if(neuron.x<=leftside+1||neuron.x>=rightside-1) {
        if(inputsensor[neuron.y/1][neuron.z/1] == 1) return 1.0;
        else return 0.0;
    }
    else return 0.0;
}

double getRecInput(const MCNNeuron &current, const std::vector<MCNNeuron> &neurons,std::map<Synapse, int> &synapses) {
    double rec = 0.0;
    int j=0;

    for(int i=0;i<neurons.size();i++){
        if (current.x == neurons[i].x && current.y == neurons[i].y && current.z == neurons[i].z){
            j=i;
            continue;
        }
        rec += synapses[{j,i}]*neurons[i].S_h;
    }

    return rec;
}

int countNeuronsInRegion(const std::vector<MCNNeuron> &neurons, int8_t min[2], int8_t max[2]) {
    int count = 0;
    for (const MCNNeuron &neuron : neurons) {
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

    int midinote =120;
    SensorGrid sensorGrid(zyN);
    SensorGrid feedbackGrid(zyN);
    std::vector<std::vector<int>> inputsensor;
    std::vector<std::vector<int>> feedbacksensor;

    IoGrid ioGrid(zyN, xN);
   
    int sennsornum=0;
    int ionum=0;
    int oldnuronnum=0;
    
    //sensorのニューロンを配置
    for(double y=0;y<=zyN;0.4){
        for(double z=0;z<=zyN;0.4){
            neurons.emplace_back(0, y, z, tau, tau_a, tau_b,
                                 gB, gL, W_b, W_hb, W_a, W_ha, W_s, beta, V_th);

            neurons.emplace_back(xN, y, z, tau, tau_a, tau_b,
                                 gB, gL, W_b, W_hb, W_a, W_ha, W_s, beta, V_th);
        }
    }
    sennsornum=neurons.size();

    //input,outputのニューロンを配置
    for(double x=0;x<=xN;0.4){
        for(double z=0;z<=zyN;0.4){
            neurons.emplace_back(x, 0, z, tau, tau_a, tau_b,
                                 gB, gL, W_b, W_hb, W_a, W_ha, W_s, beta, V_th);

            neurons.emplace_back(x, zyN, z, tau, tau_a, tau_b,
                                 gB, gL, W_b, W_hb, W_a, W_ha, W_s, beta, V_th);
        }
    }
    ionum=neurons.size()-sennsornum;

    //x 20
    //y 20
    //z 10

    for (int i = 0; i < neurons.size()-1; i++)
    {
        for (int j=1;j<neurons.size();j++)
        {
            double d = neuronDistance(neurons[i].x, neurons[i].y, neurons[i].z, neurons[j].x, neurons[j].y, neurons[j].z);
            if (d<=1||(d >= 2.0 && d <= 3.0))synapses[{i,j}] = 1; // シナプスの重みを1に設定
            else synapses[{i,j}] = 0; // シナプスの重みを1に設定
        }
    }
    oldnuronnum=neurons.size();

   
    inputsensor=(sensorGrid.createBitmap(midinote));
    bool isfeedback = false;

    for (int t = 0; t < time_steps; dt)
    {
        std::vector<double> s_in_basal(sennsornum, 0.0);
        std::vector<double> s_in_apical(sennsornum, 0.0);


        //generate patarn
        int8_t min[2] = {0,0};//tentative value
        int8_t max[2] = {zyN-1,zyN-1};//tentative value

        if (isfeedback){

            for (size_t i = 0; i < neurons.size(); i++)
            {
                int note=ioGrid.getSpikeCounts();
                feedbacksensor=(feedbackGrid.createBitmap(note));
                s_in_basal[i] = getExternalInputBasal(neurons[i], zyN, 0, xN,feedbacksensor);
                s_in_apical[i] = getExternalInputApical(neurons[i], zyN, 0, xN, feedbacksensor);
            }
            isfeedback = false;

        }
        else
        {
            for (size_t i = 0; i < neurons.size(); i++)
            {
                s_in_basal[i] = getExternalInputBasal(neurons[i], zyN, 0, xN, inputsensor);
                s_in_apical[i] = getExternalInputApical(neurons[i], zyN, 0, xN, inputsensor);
            }
            isfeedback = true;
        }

        for(size_t i=0;i< neurons.size(); i++)
        {
            double rec = getRecInput(neurons[i], neurons, synapses);
            neurons[i].update(s_in_basal[i], s_in_apical[i], rec, dt);

            //record output
            if(neurons[i].S_h == 1&&neurons[i].y==0) {
                ioGrid.recordSpike(neurons[i].y, neurons[i].x); 
            }
        }
        //stdp update
        stdpUpdate(synapses, neurons);
        
        
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
                newneurons.emplace_back(static_cast<double>(distx(mt)),
                                        static_cast<double>(disty(mt)),
                                        static_cast<double>(distz(mt)),
                                        tau, tau_a, tau_b,
                                        gB, gL, W_b, W_hb, W_a, W_ha, W_s, beta, V_th);
            }
            neurons.insert(neurons.end(), newneurons.begin(), newneurons.end());

            // create new synapse
            for (int i = 0; i < neurons.size() - 1; i++)
            {
                for (int j = oldnuronnum; j < neurons.size(); j++)
                {
                    double d = neuronDistance(neurons[i].x, neurons[i].y, neurons[i].z, neurons[j].x, neurons[j].y, neurons[j].z);
                    if (d <= 1 || (d >= 2.0 && d <= 3.0))
                        synapses[{i, j}] = 1; // シナプスの重みを1に設定
                    else
                        synapses[{i, j}] = 0; // シナプスの重みを1に設定
                }
            }
            oldnuronnum = neurons.size();
        }

    }

    return 0;

}
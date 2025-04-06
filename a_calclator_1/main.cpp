#include "neuron.h"

double  neuronDistance(int x1, int y1, int z1, int x2, int y2, int z2) {
    return std::sqrt((x1 - x2)*(x1 - x2) +(y1 - y2)*(y1 - y2) +(z1 - z2)*(z1 - z2));
}

double getExternalInputBasal(const MCNNeuron &neuron,uint8_t up,uint8_t leftside,uint8_t rightside) {
    if (neuron.z == up||neuron.x==leftside||neuron.x==rightside) return 1.0;
    return 0.0;
}
double getExternalInputApical(const MCNNeuron &neuron,uint8_t up,uint8_t leftside,uint8_t rightside) {
    if (neuron.z >= up-1||neuron.x<=leftside+1||neuron.x>=rightside-1) return 1.0;
    return 0.0;
}

double getBasalRecInput(const MCNNeuron &current, const std::vector<MCNNeuron> &neurons) {
    double rec_basal = 0.0;
    for (const auto &other : neurons) {
        if (current.x == other.x && current.y == other.y && current.z == other.z)
            continue;
        if (neuronDistance(current.x, current.y, current.z, other.x, other.y, other.z) <= 1)
            rec_basal += other.S_h;
    }
    return rec_basal;
}

double getApicalRecInput(const MCNNeuron &current, const std::vector<MCNNeuron> &neurons) {
    double rec_apical = 0.0;
    for (const auto &other : neurons) {
        if (current.x == other.x && current.y == other.y && current.z == other.z)
            continue;
        double d = neuronDistance(current.x, current.y, current.z, other.x, other.y, other.z);
        if (d >= 2.0)
            rec_apical += other.S_h;
    }
    return rec_apical;
}

int main(){

    return 0;

}
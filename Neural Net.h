//
// Created by Guaberx on 10/18/2016.
//

#ifndef HANDWRITERECOGNITION_NEURAL_NET_H
#define HANDWRITERECOGNITION_NEURAL_NET_H

#include <vector>
#include "Graph/Graph.h"
using namespace std;

class Neuron;

typedef vector<Neuron> Layer;

class Net{
public:
    Net(const vector<unsigned> &topology);
    void feedForward(const vector<double> &inputVals);
    void backPropagation(const vector<double> &targetVals);
    void getResult(vector<double> &resultVals) const ;
private:
    vector<Layer> m_layers;//m_layers[layerNum][NeuronNum]

};

int nmain(void){
    vector<unsigned> topology;
    Net mynet(topology);

    vector<double> inputVals;
    mynet.feedForward(inputVals);

    vector<double> targetVals;
    mynet.backPropagation(targetVals);

    vector<double> resultVals;
    mynet.getResult(resultVals);
}

#endif //HANDWRITERECOGNITION_NEURAL_NET_H

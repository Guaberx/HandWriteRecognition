//
// Created by Guaberx on 10/18/2016.
//

#ifndef HANDWRITERECOGNITION_NEURAL_NET_H
#define HANDWRITERECOGNITION_NEURAL_NET_H

#include <vector>
#include "Graph/Graph.h"
#include <cmath>

using std::exp;

class Neuron{
public:
    Neuron(){}
    Neuron(double newData):data(newData){}
    //x es el peso por el input  + el limite
    void sigmoidEquation(int32_t x){
        data =  1/(1+exp(x));
    }
    void sigmoidDerivatedFunction(int32_t x){
        data = 1/(1+exp(1 - x));
    }
private:
    double data;
};//Almacena la informacion y hace las operaciones para eso

template <typename T>
class Topology{
public:
    Topology(vector<vector<T>>& _inputLayers, uint32_t _nHiddenLayers)
            :inputLayers(_inputLayers),nHiddenLayers(_nHiddenLayers){}
    vector<vector<T>>& getInputLayer()const{ return inputLayers;}
    uint32_t getNHiddenLayers()const{return nHiddenLayers;}
private:
    vector<vector<T>> inputLayers;
    uint32_t nHiddenLayers;
};//Contiene la informacion para crear la red neuronal

class Net{
public:
    //La data del graph cambia, los pesos varian en el backpropagation, en el forward es la data
    //ResultLayers contiene lo del resultado.
    Net(Graph<Neuron,double>* _graph,uint32_t hiddenLayers,uint32_t resultLayers);
    void feedForward(const vector<double> &inputVals);
    void backPropagation(const vector<double> &targetVals);
    void getResult(vector<double> &resultVals) const ;
private:
    Graph<Neuron,float> connections;//m_layers[layerNum][NeuronNum]
};


#endif //HANDWRITERECOGNITION_NEURAL_NET_H

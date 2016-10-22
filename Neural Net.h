//
// Created by Guaberx on 10/18/2016.
//

#ifndef HANDWRITERECOGNITION_NEURAL_NET_H
#define HANDWRITERECOGNITION_NEURAL_NET_H

#include <vector>
#include "Graph/Graph.h"
#include <cmath>
#include <random>

using std::exp;
using std::rand;

template <typename T>
class Neuron{
public:
    Neuron(){}
    Neuron(T newData):data(newData){}
    //x es el peso por el input  + el limite
    void sigmoidEquation(int32_t x){
        data =  1/(1+exp(x));
    }
    void sigmoidDerivatedFunction(int32_t x){
        data = 1/(1+exp(1 - x));
    }
    void understand(vector<T> incomingData){}
    T getData()const{return data;}
    void setData(double newData){data = newData;}
private:
    T data;
};//Almacena la informacion y hace las operaciones para eso

template <typename T>//TODO Refinar
class Topology{
public:
    Topology(vector<T>& _inputLayers, uint32_t _nHiddenLayers, uint32_t _nResultLayers)
            :inputLayers(_inputLayers),nHiddenLayers(_nHiddenLayers),nResultLayers(_nResultLayers){}
    vector<T>& getInputLayer(){ return inputLayers;}
    uint32_t getNHiddenLayers()const{return nHiddenLayers;}
    uint32_t getNResultLayers()const{return nResultLayers;}
private:
    vector<T> inputLayers;
    uint32_t nHiddenLayers;
    uint32_t nResultLayers;
};//Contiene la informacion para crear la red neuronal

template <typename T, typename RESULTTYPE>
class Net{
public:
    //La data del graph cambia, los pesos varian en el backpropagation, en el forward es la data
    //ResultLayers contiene lo del resultado.
    Net(Topology<T> topology, bool setRandomWeights);//TODO REVISAR
    uint32_t getUsableDataSize()const{return connections.getDataSize();}
    void feedForward(const vector<double> &inputVals);
    void backPropagation(const vector<double> &targetVals);
    void getResult(vector<double> &resultVals) const ;
    void printNeurons(){connections.printData();}
    void printConnections(){connections.printMatrix();}
private:
    Graph<T,double> connections;//m_layers[layerNum][NeuronNum]
};

template <typename T, typename RESULTTYPE>
Net<T,RESULTTYPE>::Net(Topology<T> topology, bool setRandomWeights) {
    connections = Graph<T,double>(topology.getInputLayer(),(topology.getNHiddenLayers()+topology.getNResultLayers()));
    if(setRandomWeights){
        double randomNumber;
        //Primero hacemos las conexiones de la primera capa con la escondida
        for (int i = 0; i < topology.getInputLayer().size() ; ++i) {
            for (int j = topology.getInputLayer().size(); j < topology.getInputLayer().size()+topology.getNHiddenLayers() ; ++j) {
                randomNumber = (rand()%1000)/1000;
                connections.setArco(i,j,randomNumber);
            }
        }
        //Luego las conexiones de la capa escondida con la resultante
        for (int i = topology.getInputLayer().size(); i < topology.getInputLayer().size()+topology.getNHiddenLayers() ; ++i) {
            for (int j = topology.getInputLayer().size()+topology.getNHiddenLayers(); j < topology.getInputLayer().size()+topology.getNHiddenLayers()+topology.getNResultLayers() ; ++j) {
                randomNumber = (rand()%1000)/1000;
                connections.setArco(i,j,randomNumber);
            }
        }
    }
}

#endif //HANDWRITERECOGNITION_NEURAL_NET_H

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
    //x es la sumatoria de los pesos por su respectivo arco  + el limite
    void sigmoidEquation(int32_t x){
        data =  1/(1+exp(x));
    }
    void sigmoidDerivatedFunction(int32_t x){
        data = (1/(1+exp(x)))*(1-(1/(1+exp(x))));
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

    T SumPredArc(uint32_t i);

    vector<T> feedForward(const vector<T> &inputVals);
    void backPropagation(const vector<T> &targetVals);
    void getResult(vector<T> &resultVals) const ;
    void printNeurons(){connections.printData();}
    void printConnections(){connections.printMatrix();}
private:
    Graph<T,double> connections;//m_layers[layerNum][NeuronNum]
    uint32_t dataOffset;
    uint32_t dataAndHiddenOffset;
};

template <typename T, typename RESULTTYPE>
Net<T,RESULTTYPE>::Net(Topology<T> topology, bool setRandomWeights) {
    connections = Graph<T,double>(topology.getInputLayer(),(topology.getNHiddenLayers()+topology.getNResultLayers()));
    if(setRandomWeights){
        double randomNumber;
        //Primero hacemos las conexiones de la primera capa con la escondida
        for (int i = 0; i < topology.getInputLayer().size() ; ++i) {
            for (int j = topology.getInputLayer().size(); j < topology.getInputLayer().size()+topology.getNHiddenLayers() ; ++j) {
                randomNumber = (double)(rand()%(int)pow(10,4) + 0)/pow(10,4);;
                connections.setArco(i,j,randomNumber);
            }
        }
        //Luego las conexiones de la capa escondida con la resultante
        for (int i = topology.getInputLayer().size(); i < topology.getInputLayer().size()+topology.getNHiddenLayers() ; ++i) {
            for (int j = topology.getInputLayer().size()+topology.getNHiddenLayers(); j < topology.getInputLayer().size()+topology.getNHiddenLayers()+topology.getNResultLayers() ; ++j) {
                randomNumber = (double)(rand()%(int)pow(10,4) + 0)/pow(10,4);;
                connections.setArco(i,j,randomNumber);
            }
        }
    }
    dataOffset = topology.getInputLayer().size();
    dataAndHiddenOffset = dataOffset + topology.getNHiddenLayers();
}

template <typename T, typename RESULTTYPE>
T Net<T,RESULTTYPE>::SumPredArc(uint32_t i){
    T result = 0;
    vector<uint32_t> predecesores;
    predecesores = connections.predecesores(i);
    for_each(predecesores.begin(),predecesores.end(),[&result,&i,this](uint32_t k){
        result += connections.costoArco(k,i)*connections.infoVertice(k);
    });
    return result;
}

template <typename T, typename RESULTTYPE>
vector<T> Net<T,RESULTTYPE>::feedForward(const vector<T> &inputVals) {
    //Bad parameter checking
    if(inputVals.size() != dataOffset){
        cout << "El vector proporcionado no corresponde en tamano a la primera capa de la red" << endl;
        return vector<T>();//TODO SHOULD THE PROGRAM END HERE??
    }
    //Primero reemplazamos el nuevo vector dentro  de connections
    for (uint32_t j = 0; j < dataOffset; ++j) {
        connections.setVertix(j,inputVals[j]);
    }
    //Hacemos las operaciones para la capa oculta
    for (uint32_t i = dataOffset; i < connections.getDataSize(); ++i) {
        connections.setVertix(i,1/(1+exp(-SumPredArc(i))));//TODO VOLVER UNA FUNCION APARTE SIGMOID
    }
    //Llenamos el vector resultado para retornar
    vector<T> result;//TODO CHECK EL CICLO
    for (int k = dataAndHiddenOffset; k < connections.getRowSize(); ++k) {
        result.push_back(connections.getData(k));
    }
    return result;
}

template <typename T, typename RESULTTYPE>
void Net<T,RESULTTYPE>::backPropagation(const vector<T> &targetVals) {

}

#endif //HANDWRITERECOGNITION_NEURAL_NET_H

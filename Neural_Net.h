//
// Created by Guaberx on 10/24/2016.
//

#ifndef HANDWRITERECOGNITION_NEURAL_NET_CLEANUP_H
#define HANDWRITERECOGNITION_NEURAL_NET_CLEANUP_H
#include <vector>
#include "Graph/Graph.h"
#include <cmath>
#include <random>
#include <cassert>

using std::exp;
using std::rand;
using std::sqrt;

double sigmoidEquation(double x){
    return  1/(1+exp(-x));
}
double sigmoidDerivatedFunction(double x){
    return sigmoidEquation(x)*sigmoidEquation(1-x);
}

class Neuron{
public:
    Neuron():transfered(-1),graphReference(NULL){}
    Neuron(Graph<Neuron,double> * _graphReference):graphReference(_graphReference){}
    Neuron(Graph<Neuron,double> * _graphReference,double newData):graphReference(_graphReference),transfered(newData){}

    void setGraphReference(Graph<Neuron,double> *_graphReference){graphReference = _graphReference;}
    void setIndex(uint32_t i){inGraphIndex = i;}
    void setPredecessors(vector<uint32_t> i){predecessors = i;}
    void setSuccessors(vector<uint32_t> i){succesors = i;}

    double getOSumOfProducts()const{return sumOfProducts;}
    double getTransfered()const{return transfered;}
    double getTransferedPrime()const{return transferedPrime;}

    void setOutputVal(double newData){transfered = newData;}

    virtual void SumProdToData(){
        assert(graphReference != NULL);
        double _sumOfProducts = 0;
        uint32_t tempIndex;
        for (int i = 0; i < predecessors.size(); ++i) {
            tempIndex = predecessors.at(i);
            _sumOfProducts += graphReference->infoVertice(tempIndex).transfered * graphReference->costoArco(tempIndex,inGraphIndex);
        }
        sumOfProducts = _sumOfProducts;
    }
    void transferFunction(){transfered = sigmoidEquation(sumOfProducts);}
    void transferFunctionDerivated(){transferedPrime = sigmoidDerivatedFunction(sumOfProducts);}
    void feedForward(){SumProdToData();transferFunction();}

    uint32_t getIndex(){return inGraphIndex;}

    void calcOutputGradients(){}
    void calcHiddenGradients(){}

    void updateInputWeights(){}
    virtual void algo()=0;

    friend std::ostream &operator <<(std::ostream &output, const Neuron &n){output << n.transfered; return output;}

protected:
    double sumOfProducts;//La suma de las neuronas que se conectan a esta multiplicada por su respectivo arco
    double transfered;//transfer function
    double transferedPrime;//la derivada de transfer function
    uint32_t inGraphIndex;//El index de la neurona en el grafo
    vector<uint32_t> predecessors;
    vector<uint32_t> succesors;//TODO HACER
    Graph<Neuron,double> * graphReference;
};//Almacena la informacion y hace las operaciones para eso

class InputNeuron : public Neuron{
    void SumProdToData(){}
    void algo(){}
};
class HiddenNeuron : public Neuron{
    void algo(){
        double expected;
        double result;
        double bm = result*(1-result);//El error de esa neurona
        double am;//La sumatoria de ci(de la neurona siguiente)* el arco a la neurona siguiente  -  El error de esa neurona
        double miu;
        double arco;
        double valorNeuronaInputAnterior;
        double um = arco + miu * valorNeuronaInputAnterior * am*bm;//El nuevo valor del arco que la conecta
    }

};
class OutputNeuron : public Neuron{
    void algo(){
        double expected;
        double result;
        double ci = (expected - result)*result*(1-result);//El error de esa neurona
        double arco;
        double miu;
        double um = arco + miu*ci*result;//El nuevo valor del arco que la conecta
    }

};

class Topology{
public:
    Topology(vector<double>& _inputLayers, uint32_t _nHiddenLayers, uint32_t _nResultLayers)
            :inputLayers(_inputLayers),nInputLayers(_inputLayers.size()),nHiddenLayers(_nHiddenLayers),nResultLayers(_nResultLayers){}
    Topology(uint32_t _nInputLayers, uint32_t _nHiddenLayers, uint32_t _nResultLayers)
            :inputLayers(vector<double>(_nInputLayers)),nInputLayers(_nInputLayers),nHiddenLayers(_nHiddenLayers),nResultLayers(_nResultLayers){}

    vector<double>& getInputLayer(){ return inputLayers;}
    uint32_t getNInputLayers()const{ return nInputLayers;}
    uint32_t getNHiddenLayers()const{ return nHiddenLayers;}
    uint32_t getNResultLayers()const{ return nResultLayers;}
private:
    vector<double> inputLayers;
    uint32_t nInputLayers;
    uint32_t nHiddenLayers;
    uint32_t nResultLayers;
};//Contiene la informacion para crear la red neuronal

class Net{
public:
    //La data del graph cambia, los pesos varian en el backpropagation, en el forward es la data
    //ResultLayers contiene lo del resultado.
    Net(Topology topology);

    void train(const vector<double> &inputVals, const vector<double> &wantedVal);

    void feedForward(const vector<double> &inputVals);
    void backPropagation(const vector<double> &targetVals);//Calculate the error for each output neuron
    vector<double> getResult(vector<double> &inputVals) const ;
    void printNeurons(){connections.printData();}
    void printConnections(){connections.printMatrix();}

    double getTest(){return connections.getData(4).getOSumOfProducts();}
private:
    Graph<Neuron,double> connections;
    uint32_t nInputLayers;
    uint32_t nHiddenLayers;
    uint32_t nResultLayers;
    uint32_t totalNeurons;
};

Net::Net(Topology topology)
        :nInputLayers(topology.getNInputLayers()),nHiddenLayers(topology.getNHiddenLayers()),nResultLayers(topology.getNResultLayers())
{
    totalNeurons = topology.getNInputLayers()+topology.getNHiddenLayers()+topology.getNResultLayers();
    //Create the Graph
    //connections = Graph<Neuron,double>(totalNeurons);
    /////////////////////////////
    //anadimos los tipos de neuronas correspondientes a cada capa
    connections.addElements(InputNeuron(),nInputLayers);
    connections.addElements(HiddenNeuron(),nHiddenLayers);
    connections.addElements(OutputNeuron(),nResultLayers);
    ////////////////////////////
    double temp;
    //Set the Graph reference of the neurones
    for (int i = 0; i < connections.getDataSize(); ++i) {
        connections.getData(i).setGraphReference(&connections);
    }
    //Set The correct data to the input neurons
    for (int j = 0; j < nInputLayers; ++j) {
        temp = topology.getInputLayer().at(j);
        connections.getData(j).setOutputVal(temp);
    }
    //Set Connections from input layer to hiddelLayer
    for (int j = nInputLayers; j < nInputLayers+nHiddenLayers; ++j) {
        for (int i = 0; i < nInputLayers; ++i) {
            connections.setArco(i,j,rand()/double(RAND_MAX));
        }
    }
    //Set Connections from Hidden layer to Result Layer
    for (int j = nInputLayers+nHiddenLayers; j < totalNeurons; ++j) {
        for (int i = nHiddenLayers; i < nInputLayers+nHiddenLayers; ++i) {
            connections.setArco(i,j,rand()/double(RAND_MAX));
        }
    }
    //Predecesores, succesores y el index en el grafo de cada neurona
    vector<uint32_t> tempPredecesores;
    vector<uint32_t> tempSucesores;
    //El index de la neurona en el grafo
    //predecessors de cada neurona
    for (int k = 0; k < totalNeurons; ++k) {
        connections.getData(k).setIndex(k);
        tempPredecesores = connections.predecessors(k);
        tempSucesores = connections.successors(k);
        connections.getData(k).setPredecessors(tempPredecesores);
        connections.getData(k).setSuccessors(tempSucesores);
    }
}

void Net::feedForward(const vector<double> &inputVals) {
    //Asserts
    assert(nInputLayers == inputVals.size());
    double tempData;
    for (int j = 0; j < nInputLayers; ++j) {
        tempData = inputVals.at(j);
        connections.getData(j).setOutputVal(tempData);
    }
    for (int i = nInputLayers; i < totalNeurons; ++i) {
        connections.getData(i).feedForward();
    }
}

void Net::backPropagation(const vector<double> &targetVals) {
    //The error for a neuron is: the sumatory of the derivative of the transfer function (i), i is the neuron that the actual neuron connects to * the weight

}

#endif //HANDWRITERECOGNITION_NEURAL_NET_CLEANUP_H

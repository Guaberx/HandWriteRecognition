//
// Created by Guaberx on 11/4/2016.
//
#include "Neural_Net.h"

Net::Net(Topology topology)
        :nInputLayers(topology.getNInputLayers()),
         nHiddenLayers(topology.getNHiddenLayers()),
         nResultLayers(topology.getNResultLayers()),
         nBiasLayers(2),
         connections(Graph<Neuron, double>())

{
    totalNeurons = 2 + topology.getNInputLayers()+topology.getNHiddenLayers()+topology.getNResultLayers();
    //Create the Graph
    connections.addElements(Neuron(),totalNeurons);//we add the bias 1 input, 1 hidden

    double temp;
    //Set the Graph reference of the neurones
    for (int i = 0 ; i < connections.getDataSize(); ++i) {
        connections.getData(i).setGraphReference(&connections);
    }
    //Set Connections from input and bias layers to hiddelLayer
    for (int j = 1+nInputLayers; j < 1+1+nInputLayers+nHiddenLayers; ++j) {
        for (int i = 0; i < 1+nInputLayers; ++i) {//Comienza desde 0 para tomar el bias
            connections.setArco(i,j,rand()/double(RAND_MAX));
        }
    }
    //Set Connections from Hidden layer to Result Layer
    for (int j = 1+1+nInputLayers+nHiddenLayers; j < totalNeurons; ++j) {
        for (int i = 1+nInputLayers; i < 1+1+nInputLayers+nHiddenLayers; ++i) {
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

void Net::setInputLayer(const vector<double> &inputVals){
    //Asserts
    assert(nInputLayers == inputVals.size());
    if(DEBUG){
        cout << "EL Vector Input = { ";
        for_each(inputVals.begin(),inputVals.end(),[](double i){ cout << i << ", ";});cout << "}"<< endl;
    }
    //Set the first layer to the inputs
    uint32_t tempIndex = 1;
    for_each(inputVals.begin(),inputVals.end(),[this,&tempIndex](double i){connections.getData(tempIndex++).setOutputVal(i);});
}

void Net::train(const vector<double> &inputVals, const vector<double> &wantedVal) {

}

void Net::feedForward(const vector<double> &inputVals) {
    setInputLayer(inputVals);
    //Feed forwads the other layers
    for (int i = 2+nInputLayers; i < totalNeurons; ++i) {//Exeptuamos la bias de la hidden layer
        connections.getData(i).feedForward();
        if(DEBUG)cout << "Data of the " << i <<"th neuron = " << connections.getData(i).getTransfered() <<endl;// << endl;
    }
    //Despues de esto cada neurona esta activada
}

void Net::backPropagation(const vector<double> &targetVals) {
    assert(nResultLayers == targetVals.size());
    //Primero las neuronas de salida
    uint32_t j = 0;
    double temp = 0;
    for (int i = nBiasLayers+nInputLayers+nHiddenLayers; i < totalNeurons; ++i) {
        temp = targetVals.at(j++);
        //connections.getData(i).calculateES(temp);//TODO CUIDADO AQUI CON SGV
    }
    //Ahora las neuronas ocultas
    for (int k = nBiasLayers+nInputLayers; k < nBiasLayers+nInputLayers+nHiddenLayers; ++k) {
        //connections.getData(k).calculateES(0);//TODO CUIDADO AQUI CON SGV
    }
    for (int l = nBiasLayers+nInputLayers; l < totalNeurons; ++l) {
        connections.getData(l).calculateED();
    }
    for (int l = totalNeurons-1; l >= 0; --l) {
        connections.getData(l).updateWeights();
    }
}

vector<double> Net::getResult(vector<double> &inputVals) {
    //feedForward(inputVals);//TODO PROBLEMA EN ESTA FUNCION
    /*for (int i = 2+nInputLayers+nHiddenLayers; i < totalNeurons; ++i) {
        cout << "Result: " << connections.getData(i).getTransfered() << endl;
    }*/
}

void Net::printNeurons(){
    for (int i = 0; i < connections.getDataSize(); ++i) {
        cout << "<" << connections.getData(i).getTransfered() << ">";
    }cout << endl;}//Imprime el vector del grafo
void Net::printConnections(){connections.printMatrix();}//Imprime la matriz del grafo


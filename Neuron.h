//
// Created by Guaberx on 10/31/2016.
//

#ifndef HANDWRITERECOGNITION_NEURON_H
#define HANDWRITERECOGNITION_NEURON_H
#define DEBUG 0
#include <cmath>
#include <random>
#include "Graph/Graph.h"
#include <cassert>
using std::exp;
using std::rand;
using std::sqrt;

double sigmoidEquation(double x);
double sigmoidDerivatedFunction(double x);

class Neuron{
public:
    //Constructoras
    Neuron();
    ~Neuron();

    //Sets de informacion sobre el entorno en el que se encuentra la neurona
    void setGraphReference(Graph<Neuron,double> *_graphReference);
    void setIndex(uint32_t i);
    void setPredecessors(vector<uint32_t> i);
    void setSuccessors(vector<uint32_t> i);

    void setOutputVal(double newData);//transfered es el valor de salida de cada neurona

    double getTransfered()const;//Retorna el output de la neurona
    double getTransferedPrime()const;//Retorna la derivada del valor de la neurona

    void SumProdToData();
    void transferFunction(double x);//Funcion para normalizar el valor entre [0,1]
    void transferFunctionDerivative(double x);;//Funcion para normalizar el valor entre [0,1]

    void feedForward();//Realiza esas dos funciones

    uint32_t getIndex();//Retorna el index de esta neurona en el grafo

    double getES();//El error
    double getED();//El cambio a las conexiones con la neurona

    void calculateED();
    void updateWeights();

    friend std::ostream &operator <<(std::ostream &output, const Neuron &n){output << n.transfered; return output;}

protected:
    double sumOfProducts;//La suma de las neuronas que se conectan a esta multiplicada por su respectivo arco
    double transfered;//transfer function. Guarda El valor de la funcion con su respectivo sigmoid. es el valor con el cual se calculan las cosas y el valor de retorno en la ultima capa
    double transferedPrime;//la derivada de transfer function
    uint32_t inGraphIndex;//El index de la neurona en el grafo
    vector<uint32_t> predecessors;//Lista de indexes de las neuronas que se conectan con esta neurona
    vector<uint32_t> succesors;//Lista de indexes de neuronas a las cuales se conecta esta neurona
    Graph<Neuron,double> * graphReference;//Una referencia al grafo para poder modificar los arcos
    double miu;
    double es;//Error Signal
    double ed;//Error Derivative
};
#endif //HANDWRITERECOGNITION_NEURON_H

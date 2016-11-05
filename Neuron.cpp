//
// Created by Guaberx on 11/4/2016.
//
#include "Neuron.h"

double sigmoidEquation(double x){
    return  1/(1+exp(-x));
}
double sigmoidDerivatedFunction(double x){
    return sigmoidEquation(x)*sigmoidEquation(1-x);
}


//Constructoras
Neuron::Neuron():transfered(1),transferedPrime(0),graphReference(NULL),inGraphIndex(0),sumOfProducts(0),
         miu(0.1),es(0),ed(0),squaredError(0),squaredErrorDerivative(0){}
Neuron::~Neuron(){
//cout << "Neurona " << inGraphIndex << " Destruida" << endl;
}

//Sets de informacion sobre el entorno en el que se encuentra la neurona
void Neuron::setGraphReference(Graph<Neuron,double> *_graphReference){graphReference = _graphReference;}
void Neuron::setIndex(uint32_t i){inGraphIndex = i;}
void Neuron::setPredecessors(vector<uint32_t> i){predecessors = i;}
void Neuron::setSuccessors(vector<uint32_t> i){succesors = i;}

//Set
void Neuron::setOutputVal(double newData){
    transfered = newData; transferedPrime = newData*(1-newData);
}//transfered es el valor de salida de cada neurona

double Neuron::getTransfered()const{
    return transfered;
}//Retorna el output de la neurona
double Neuron::getTransferedPrime()const{
    return transferedPrime;
}//Retorna la derivada del valor de la neurona

void Neuron::SumProdToData(){
    //La sumatoria de los arcos por el valor de la neurona anterior se guarda en sumOfProducts
    assert(graphReference != NULL);
    assert(graphReference->getDataSize() > predecessors.back());
    sumOfProducts = 0;
    if(DEBUG)cout <<"Feeding forward neuron "<<inGraphIndex <<": "<<endl;
    for_each(predecessors.begin(),predecessors.end(),[this](uint32_t i){
        if(DEBUG)cout << "i = " << i << " \tdata of prev Neuron = " <<graphReference->infoVertice(i).transfered << " \tweight = " << graphReference->costoArco(i,inGraphIndex);
        sumOfProducts += graphReference->infoVertice(i).transfered * graphReference->costoArco(i,inGraphIndex);
        if(DEBUG)cout << " \tThe sumOfProd by the iteration = " <<sumOfProducts<<endl;
    });
    if(DEBUG){
        cout << "The Total sumOfProd = " << sumOfProducts
             << " \tThat value with the activation function = " << sigmoidEquation(sumOfProducts)
             << " \tIts derivative = " << sigmoidDerivatedFunction(sumOfProducts) << endl;
    }
}
void Neuron::transferFunction(double x){
    transfered = sigmoidEquation(x);
}//Funcion para normalizar el valor entre [0,1]/
/*
void Neuron::transferFunctionDerivative(double x){
    transferedPrime = sigmoidDerivatedFunction(x);
}//Funcion para normalizar el valor entre [0,1]*/
void Neuron::feedForward(){
    SumProdToData();
    transferFunction(sumOfProducts);
}//Realiza esas dos funciones

void Neuron::calculateSquaredError(double target){
    squaredError = (pow((target - transfered),2))/2;//transfered es el output
}
void Neuron::calculateSquaredErrorDerivative(double target){
    squaredErrorDerivative = (transfered - target);//-(target - out)
}
void Neuron::calculatedOutdNet(){
    transferedPrime = transfered*(1-transfered);
}
double Neuron::getSquaredError()const{
    return squaredError;
}
double Neuron::getSquaredErrorDerivative()const{
    return squaredErrorDerivative;
}
double Neuron::getdOutdNet()const{
    return transferedPrime;
}

uint32_t Neuron::getIndex()const{return inGraphIndex;}//Retorna el index de esta neurona en el grafo

///NEW///
double Neuron::getES()const{return es;}
double Neuron::getED()const{return ed;}

//Calculate es
void Neuron::calculateED(){
    ed = 0;
    for_each(predecessors.begin(),predecessors.end(),[this](uint32_t i){
        ed += es * graphReference->getData(i).transfered;
    });
}
void Neuron::updateWeights(){
    double newWeightValue;
    //cout << "NEURONA: " << inGraphIndex << "| ES = " << es << "  ED = " << ed <<endl;
    for_each(predecessors.begin(),predecessors.end(),[this,&newWeightValue](uint32_t i){
        newWeightValue = graphReference->getArco(i,inGraphIndex) + ed * miu;//miu = Learning Rate
        graphReference->setArco(i,inGraphIndex,newWeightValue);
    });
}

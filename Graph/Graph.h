//
// Created by Guaberx on 10/21/2016.
//

#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H
#define CLOSED (~0)

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::for_each;
using std::ofstream;
using std::ifstream;
using std::ios;
template <typename T, typename G>
class Graph{
public:
    Graph(){}
    Graph(vector<T> newData):data(newData){}

    void insVertix(T newElem);//Agrega un elemento a data y en la matriz se inicializa sin conexiones
    void setVertix(uint32_t i,T newElem);//se describe sola
    void setArco(uint32_t i,uint32_t j,G newArco);//i,j de matrix
    void elimArco(uint32_t i,uint32_t j);//Lo cierra
    G costoArco(uint32_t i,uint32_t j);

    vector<uint32_t> predecesores(uint32_t i);//retorna los predecesores del vértice vi
    vector<uint32_t> sucesores(uint32_t i);//retorna la lista de sucesores del vertice vi

    //Persistencia
    void clean();

    void save(string filePath);
    void load(string filePath);

    void printData(){for_each(data.begin(),data.end(),[](T i){
            cout << "<" << i << ">";});
        cout << endl;
    }
    void printMatrix(){for_each(matrix.begin(),matrix.end(),[](vector<G> i){
            for_each(i.begin(),i.end(),[](T j){
                cout << (G)j << " ";
            });
            cout << endl;
        });
    }
    //Destructora
    ~Graph(){clean();}//Devuelve al sistema toda la memoria dinamica utilizada
private:
    vector<T> data;
    vector<vector<G>> matrix;
};


template <typename T, typename G>
void Graph<T,G>::insVertix(T newElem){
    data.push_back(newElem);
    vector<G> tempVector;
    for (int i = 0; i < matrix.size(); ++i) {
        tempVector.push_back(CLOSED);
    }
    matrix.push_back(tempVector);
    for (int j = 0; j < matrix.size(); ++j) {
        matrix[j].push_back(CLOSED);
    }
};

template <typename T, typename G>
void Graph<T,G>::setVertix(uint32_t i,T newElem){data[i] = newElem;};

template <typename T, typename G>
void Graph<T,G>::setArco(uint32_t i,uint32_t j,G newArco){matrix[i][j] = newArco;};

template <typename T, typename G>
void Graph<T,G>::elimArco(uint32_t i,uint32_t j){ matrix[i][j] = CLOSED;};

template <typename T, typename G>
G Graph<T,G>::costoArco(uint32_t i,uint32_t j){ return matrix[i][j];};

template <typename T, typename G>
vector<uint32_t> Graph<T,G>::predecesores(uint32_t i){
    vector<uint32_t> result;
    for (int j = 0; j < matrix.size(); ++j) {
        if(matrix[j][i] != CLOSED)
            result.push_back(matrix[j][i]);
    }
    return result;
};

template <typename T, typename G>
vector<uint32_t> Graph<T,G>::sucesores(uint32_t i){
    vector<uint32_t> result;
    for (int j = 0; j < matrix.size(); ++j) {
        if(matrix[i][j] != CLOSED)
            result.push_back(matrix[i][j]);
    }
    return result;
};

//Persistencia
template <typename T, typename G>
void Graph<T,G>::clean(){data.clear(); for_each(matrix.begin(),matrix.end(),[](vector<G> i){ i.clear();}); matrix.clear();};

template <typename T, typename G>
void Graph<T,G>::save(string filePath){
    ofstream file(filePath, ios::out | ofstream::binary);
    //Header Of Data Size
    uint32_t dataSize = data.size();
    file.write((char*)&dataSize,sizeof(uint32_t));
    //Header Of Matrix Size
    uint32_t matrixSize = matrix.size();
    file.write((char*)&matrixSize,sizeof(uint32_t));
    //Writes the data
    for (int i = 0; i < data.size(); ++i) {
        file.write((char*)&data[i],sizeof(T));
    }
    //Writes the matrix
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            file.write((char*)&matrix[i][j],sizeof(G));
        }
    }
}

template <typename T, typename G>
void Graph<T,G>::load(string filePath){
    clean();
    ifstream file(filePath, ios::in | ifstream::binary);
    uint32_t dataSize = data.size();
    uint32_t matrixSize = matrix.size();
    file.read((char*)&dataSize,sizeof(uint32_t));
    file.read((char*)&matrixSize,sizeof(uint32_t));

    T tempDataElem;
    for (int i = 0; i < dataSize; ++i) {
        file.read((char*)&tempDataElem,sizeof(T));
        data.push_back(tempDataElem);
    }
    G tempMatrixElem;
    vector<G> tempVector;
    for (int j = 0; j < matrixSize; ++j) {
        matrix.push_back(tempVector);
        for (int i = 0; i < matrixSize; ++i) {
            file.read((char*)&tempMatrixElem,sizeof(G));
            matrix[j].push_back(tempMatrixElem);
        }
    }
}


#endif //GRAPH_GRAPH_H

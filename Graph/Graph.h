//
// Created by Guaberx on 9/24/2016.
//

#ifndef GRAPHTALLEROBJETOS_GRAPH_H
#define GRAPHTALLEROBJETOS_GRAPH_H
//CLOSED representa un arreglo de bits lleno de unos
#define CLOSED (uint32_t)~0

#include <fstream>
#include <string>
#include <vector>
#include "Matrix/Matrix.h"

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;
using std::ios;

struct GraphHeader{
    //FileSize
    uint32_t size;
    //dataType dice cuantos bytes ocupa el tipo de dato usado en el grafo
    uint32_t dataType;//TODO Enhance!!!!
    //vectorSize es la cardinalidad del conjunto de vertices; que es la raiz cuadrada de la cardinalidad de los arcos
    uint32_t vectorSize;
    //offset indica en que byte comienzan los datos
    uint8_t offset;
    //Sabemos que contiene un vector y una matriz que ocupan (_size + _size*_size)
    //Los datos vienen organizados primero por los vertices y luego cada arco Aij de la matriz de adyacencia
};

//Las filas de la matriz representan el nodo de salida
//Las columnas el nodo de llegada
//El grafo contiene un vector con los nodos y una matriz de adyacencia
template <typename T>//TODO Se puede anadir otro parametro para reemplazar las medidas de la matriz de adyacencia
class Graph{
private:
    Matrix<float> adjacencyMatrix;
    vector<T> data;//Lo que contiene cada vertice del grafo
    uint32_t _size;

    void AdjacendyMatrixUpdate();
public:
    //Constructoras_____________________
    Graph();
    //Crea un grafo de tamano numVertices. datosGrafo trae la informacion de cada vertice
    // y arcos es una matriz donde en arcos[i][j] esta el costo del vertice v1 y el vertice vj
    Graph(vector<T> datosGrafo, float **arcos, uint32_t numVertices);
    //Modificadoras_____________________
    void insVertice(T dato);//Anexa un vertice con la informacion dato
    void setVertice(uint32_t i, T dato);//Cambia la informacion del vertice Vi, por dato
    void setArco(uint32_t i, uint32_t j, int32_t costo);//Arco entre Vi y Vj
    void elimArco(uint32_t i, uint32_t j);//Elimina el arco
    Graph<T> copy(Graph<T>&& fuente);

    //Analizadoras (Operaciones	get)
    float costoArco(uint32_t i, uint32_t j);//retorna el costo entre el vértice vi y el vértice vj. Si no hay arco retorna -1.

    T infoVertice(uint32_t i);
    uint32_t size();
    vector<uint32_t> predecesores(uint32_t i);//retorna los predecesores del vértice vi
    vector<uint32_t> sucesores(uint32_t i);//retorna la lista de sucesores del vertice vi
    void print();

    //Persistencia
    void clean();

    void load(string filePath);
    void save(string filePath);

    //Destructora
    ~Graph();//Devuelve al sistema toda la memoria dinamica utilizada

    //Sobrecarga de operadores
    Graph<T> &operator = (Graph<T> &other){
        data = other.data;
        adjacencyMatrix = other.adjacencyMatrix;
        _size = other._size;
        return *this;
    }
    Graph<T> operator = (Graph<T> &&other){
        //TODO TERMINAR
        auto tempSize = _size;
        auto tempData = data;
        data = other.data;
        _size = other._size;
        other.data = tempData;
        other._size = tempSize;
        return *this;
    }
    friend std::ostream &operator <<(std::ostream &output, Graph<T> &OU){
        for (int i = 0; i < OU.size(); ++i) {
            output << OU.data[i];
            for (int j = 0; j < OU.size(); ++j) {
                if(OU.adjacencyMatrix.cellInfo(i,j) != CLOSED)
                    output << " -> " << OU.data[i];
            }
            output << std::endl;
        }
        return output;
    }
    T &operator [](uint32_t i){
        return data[i];
    }
    /*
     * copiarGrafo utilizando operator=
     * imprimirGrafo utilizando operator<<
     * infoVertice utilizando operator[]
     */

    //Punto 3
    /*
     * defina un grafo de tipo float (Grafo<float>) y calcule la suma de
     * producto de los predecesores (importante para el proyecto).
     * prodPredecesores(Vi) se calcula así: Para un nodo vi, extraiga
     * la lista de sus predecesores (predecesores(i)). Multiplique el
     * valor del nodo predecesor por el costo del arco de dicho nodo
     * al nodo Vi. Acumule todos los resultados parciales.
     */
};
//Provate
template <typename T>
void Graph<T>::AdjacendyMatrixUpdate() {
    //Cierra todos los campos
    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            if(i != j){
                adjacencyMatrix.modifyCell(i,j,CLOSED);
            }
        }
    }
}


//Public
template <typename T>
Graph<T>::Graph():_size(0){
    //Tanto vector como Matrix tienen su propio constructor, por lo que no se necesita implementar esta
    std::cout << "Grafo vacio creado" << std::endl;
    AdjacendyMatrixUpdate();
}
//Arcos tiene que ser una matriz cuadrada
template <typename T>
Graph<T>::Graph(vector<T> datosGrafo, float **arcos, uint32_t numVertices):data(datosGrafo),_size(numVertices){
    //|i|==numVertices && |j|==numVertices o hay SGV
    adjacencyMatrix.addRowCol(numVertices);
    //Llenamos la matriz con todos los nodos cerrados, exepto las diagonales
    AdjacendyMatrixUpdate();
    //Llenamos la matriz de adyacencia con la informacion proporcionada
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            adjacencyMatrix.modifyCell(i,j,arcos[i][j]);//TODO Si hay SGV es aqui!!!!!!!!!!!!!!!!!!!!!!
        }
    }
    std::cout << "Grafo de " << numVertices <<" vertices creado" << std::endl;
}
template <typename T>
void Graph<T>::insVertice(T dato) {
    //Como inserta un vertice, tambien toca modificar la matriz de adyacencia
    data.push_back(dato);
    adjacencyMatrix.addRowCol();
    _size++;
}
template <typename T>
void Graph<T>::setVertice(uint32_t i, T dato) {
    if(i > data.size()){
        std::cout << "Numero instroducido en funcion setVertice(int i, T dato) de i fuera del rango" <<std::endl;
        return;
    }
    data.at(data.begin() + i) = dato;
}
template <typename T>
void Graph<T>::setArco(uint32_t i, uint32_t j, int32_t costo) {
    if(i>=_size || j>=_size)
        cout << "En la funcion setArco: i o j no apunta/n a un elemento entre los datos" << endl;
    else
        adjacencyMatrix.modifyCell(i,j,costo);
}
template <typename T>
void Graph<T>::elimArco(uint32_t i, uint32_t j) {
    //TODO supongo que se refiere a cerrar la ruta, pero no quitar el nodo. por lo que se le asigna infinito
    adjacencyMatrix.modifyCell(i,j,CLOSED);
}
template <typename T>
Graph<T> Graph<T>::copy(Graph<T>&& fuente) {
    data = fuente.data;
    adjacencyMatrix = fuente.adjacencyMatrix;
    return fuente;
}
template <typename T>
float Graph<T>::costoArco(uint32_t i, uint32_t j) {
    return adjacencyMatrix.cellInfo(i,j);
}
template <typename T>
T Graph<T>::infoVertice(uint32_t i) {
    return data[i];
}
template <typename T>
uint32_t Graph<T>::size() {
    return _size;
}
template <typename T>
vector<uint32_t> Graph<T>::predecesores(uint32_t i) {
    //Muestra todos los predecesores de Vi
    //TODO poner atencion al valor de condicion CLOSED al crear la matriz
    vector<uint32_t> predecessors;
    for (int j = 0; j < _size; ++j) {
        if(adjacencyMatrix.cellInfo(i,j) != CLOSED){
            predecessors.push_back(j);
        }
    }
    return predecessors;
}
template <typename T>
vector<uint32_t> Graph<T>::sucesores(uint32_t i) {
    //Muestra todos los sucesores de Vi
    //TODO poner atencion al valor de condicion CLOSED al crear la matriz
    vector<uint32_t> sucessors;
    for (int j = 0; j < _size; ++j) {
        if(adjacencyMatrix.cellInfo(j,i) != CLOSED){
            sucessors.push_back(j);
        }
    }
    return sucessors;
}
template <typename T>
void Graph<T>::print() {
    for (int i = 0; i < _size; ++i) {
        std::cout << data[i];
        for (int j = 0; j < _size; ++j) {
            if(adjacencyMatrix.cellInfo(i,j) != CLOSED)
                std::cout << " -> " << data[j];
        }
        std::cout << std::endl;
    }
}
template <typename T>
void Graph<T>::clean(){
    data.clear();
    adjacencyMatrix.clean();
    _size = 0;
}
template <typename T>
void Graph<T>::load(string filePath) {
    //First we clean the Graph
    clean();
    //Open File
    ifstream file(filePath, ios::in | ifstream::binary);
    //Read the data into the struct
    GraphHeader tempGraphHeader;
    file.read((char*)&tempGraphHeader,sizeof(GraphHeader));
    //Set the reading pointer to the offset
    //file.seekg((uint32_t)tempGraphHeader.offset,file.beg);//TODO REVISAR SI SALE MAL ALGO: PROBLEMA AQUI
    //We fill the vector<T> data
    T tempData;
    for (int i = 0; i < tempGraphHeader.vectorSize; ++i) {
        file.read((char*)&tempData,sizeof(T));
        data.push_back(tempData);
    }
    _size = data.size();
    //Then we create a temporal Matrix and then copy it to the Graph adjacency matrix
    adjacencyMatrix.addRowCol(tempGraphHeader.vectorSize);//Define adjacencyMatrix Size
    float tempFloat;
    for (int i = 0; i < tempGraphHeader.vectorSize; ++i) {
        for (int j = 0; j < tempGraphHeader.vectorSize; ++j) {
            file.read((char*)&tempFloat,(tempGraphHeader.vectorSize*tempGraphHeader.vectorSize));
            adjacencyMatrix.modifyCell(i,j,tempFloat);
        }
    }
}
//Ambas formas funcionan, pero me demore mucho haciendo la segunda asi que es la que voy a mostrar :')
template <typename T>
void Graph<T>::save(string filePath) {
    ofstream file(filePath, ios::out | ofstream::binary);

    GraphHeader tempHeader;
    tempHeader.vectorSize = _size;
    tempHeader.dataType = sizeof(T);
    tempHeader.size = sizeof(GraphHeader)+(sizeof(T)*_size)+sizeof(T)*(_size*_size);;
    uint8_t offset = sizeof(GraphHeader);//TODO!!!!!!!!!!!
    //Writes the header
    file.write((char*)&tempHeader,sizeof(GraphHeader));
    //Writes the data
    for (int i = 0; i < _size; ++i) {
        file.write((char*)&data[i],sizeof(T));
    }
    //Writes the matrix
    float tempFloat;
    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            tempFloat = adjacencyMatrix.cellInfo(i,j);
            file.write((char*)&tempFloat,sizeof(float));
        }
    }
}

template <typename T>
Graph<T>::~Graph() {
    //No se utiliza memoria dinamica
    clean();
    std::cout << "Grafo destruido" << std::endl;
}

#endif //GRAPHTALLEROBJETOS_GRAPH_H

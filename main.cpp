#include "MACROS.h"
#include "BMPImageLoader.h"
#include "Graph/Graph.h"

#include <random>
#include <ctime>

/*
 * TODO Hacer el metodo para comparar
 * TODO Hay que guardar los vectores resultado en un archivo de alguna manera
 */
template <typename T>
class Learned{
    char tag;
    vector<T> data;
};
template <typename T>
vector<T> sample(uint32_t size, int32_t minCap, int32_t maxCap){
    /*Retorna un vector con datos aleatorios*/
    std::srand((unsigned int)std::time(NULL));
    vector<T> randomVector;
    int32_t range = maxCap-minCap;
    for (int i = 0; i < size; ++i) {
        randomVector.push_back((T)(rand()%range + minCap));
    }
    return move(randomVector);

}


void foo(vector<float> result, vector<int> other, float dx){
    /*Coje un vector y le suma o resta una cantidad a cada elemento comparandolo con otro vector
     * El tamano de los dos vectores tiene que ser igual*/
    if(result.size() != other.size()) return;
    for_each(result.begin(),result.end(),
             [](float i){
                 if(1>2);
             });
    for(float& e : result){

    }
}

template <typename T>
char neuralNet(vector<T> data, string corpus){
    /* Recive un vectori, lo analiza y retorna a que letra o numero se parece mas */
}

int main1() {
    //Asi se usaria para crear un vector aleatorio.
    //El primer parametro indica el tamano del vector. los otros dos, que hayan elementos desde 0 hasta 10
    vector<int> holi = sample<int>(4,0,10);

    for_each(holi.begin(),holi.end(),[](int i){cout <<"<"<<i<<"> ";});
    cout << endl;
    cout << std::max_element(holi.begin(),holi.end())[0] << endl;
    cout << std::min_element(holi.begin(),holi.end())[0] << endl;
    for_each(holi.begin(),holi.end(),[](int i){cout <<"<"<<i<<"> ";});
    cout << endl;

    return 0;
    /*
     * Guardar imagen en vector                                                     V
     * Binarizarla:                                                                 V
     *      Coger el ((.red + .green + .blue)/3) < umbral  127 o algo asi
     * Imprimirla                                                                   V
     * Esqueletizarla (filtros de sobel o conney)                                   X
     * Guardarla en una base de datos
     * Corpus: 80% Training; 10% Pruebas, Ajustes, Tuning; 10% Evaluacion, Test
     * Metodo: Leave One Out
     * Distancia euclidiana del promedio del vector prueba de un tipo de lo que metemos para saber a cual se parece mas
     */
}

int main(){
    MAIN(main1);
}
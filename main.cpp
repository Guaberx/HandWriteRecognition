#include "MACROS.h"
#include "BMPImageLoader.h"
#include "Graph/Graph.h"
#include <random>
#include <ctime>
#include <sstream>

/*
 * TODO Hacer el metodo para comparar
 * TODO Hay que guardar los vectores resultado en un archivo de alguna manera
 */
template <typename T>
struct Learned{
    char tag;
    vector<T> data;
    Learned(vector<T> newData);
};
/*
 *vector<Learned<T>> vectoresResultantes    (es decir el aprendizaje)
_______________________
|cantidadDeVectores|TamanosVectores
|tag|data[0]|data[1]|...|
|tag|data[0]|data[1]|...|
------------------------
 */
template <typename T>
vector<T> sample(uint32_t size, int32_t minCap, int32_t maxCap){
    /*Retorna un vector con datos aleatorios*/
    vector<T> randomVector;
    int32_t range = maxCap-minCap;
    for (int i = 0; i < size; ++i) {
        randomVector.push_back(((T)(rand()%range + minCap))/100);//Asi lo toma como un float
    }
    return move(randomVector);
}

//For training
void foo(vector<float>& result, const vector<int> other, const float dx){
    /*Coje un vector y le suma o resta una cantidad a cada elemento comparandolo con otro vector
     * El tamano de los dos vectores tiene que ser igual*/
    if(result.size() != other.size()) return;
    for (int i = 0; i < result.size(); ++i) {
        if(result[i] < other[i]){
            result[i] = result[i] + dx;
        }
        else if(result[i] > other[i]){
            result[i] -= dx;
        }
    }
}
/*
 * para todos los archivos de entrenamiento do -> foo(result)
 */

template <typename T>
char neuralNet(vector<T> data, string corpus){
    /* Recive un vectori, lo analiza y retorna a que letra o numero se parece mas */
}

void qu(string pathOfFolder){
    /*Takes the path of the folder with the training data and trains the net*/

}

string easyPathOfFolder(const string folderPath, const int fileNumeration, const string prefix, const string postfix){
    //Helps getting the path of enumerated files in a folder
    string result = folderPath;
    std::stringstream convert;
    if(fileNumeration < 10) convert << 0;
    convert << fileNumeration;
    result += "\\";
    result += prefix;
    result += convert.str();
    result += postfix;
    return std::move(result);
}

int main1() {
    std::srand((unsigned int)std::time(NULL));//RANDOM!!!!!
    BMPImage<int> test;
    test.read("C:\\Users\\Guaberx\\Desktop\\HandWriteRecognition\\Corpus\\Images\\0_Training\\_01.bmp");
    test.normalize();
    test.patron();

    vector<int> a = test.patron();
    test.printNormalized();

    for_each(a.begin(),a.end(),[](int i){cout << "<"<<i <<"> ";});

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
#include "MACROS.h"
#include "BMPImageLoader.h"
#include "Neural_Net.h"
#include <ctime>
#include <sstream>

//IGNORA ESTO HASTA EL MAIN.
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
    /*TODO Lee los comentarios de Neural_Net.h, Intenta No cambiar el grafo o lo de las imagenes
     *TODO Ponele 8 neuronas de salida, utiliza Topology para definir la red
     *TODO El vector de una imagen se consigue cargando la imagen y llamando la funcion patron() que retorna un vector
     */
    //srand tiene que ser llamado en el main!!!!!!!!
    std::srand((unsigned int)std::time(NULL));//RANDOM!!!!!
    rand();

    vector<double> iv0 = {0,0};
    vector<double> iv1 = {0,1};
    vector<double> iv2 = {1,0};
    vector<double> iv3 = {1,1};

    Topology top1(iv0,2,1);
    Net net0(top1);

    net0.printNeurons();
    net0.feedForward(iv0);
    net0.printNeurons();
    net0.printConnections();

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
#include "MACROS.h"
#include "BMPImageLoader.h"
#include "Neural_Net.h"
#include <ctime>
#include <sstream>
/*
 * Bibliografias
 * https://mattmazur.com/2015/03/17/a-step-by-step-backpropagation-example/
 */

//IGNORA ESTO HASTA EL MAIN.
string easyPathOfFolder(const string folderPath, const int folderNumber,
                        const string folder, const string prefix, const int fileNumeration, const string postfix){
    //Helps getting the path of enumerated files in a folder
    std::stringstream converter1;
    string result = folderPath;
    result += "\\";
    converter1 << folderNumber;
    result += converter1.str();
    result += folder;
    result += "\\";
    result += prefix;
    std::stringstream converter2;
    if(fileNumeration < 10) converter2 << 0;
    converter2 << fileNumeration;
    result += converter2.str();
    result += postfix;
    return std::move(result);
}

template<typename T>
struct is_pointer { static const bool value = false; };

template<typename T>
struct is_pointer<T*> { static const bool value = true; };

template<typename T>
void func(const vector<T>& v) {
    std::cout << "is it a pointer? " << is_pointer<T>::value << std::endl;
}

int main() {
    /*TODO Lee los comentarios de Neural_Net.h, Intenta No cambiar el grafo o lo de las imagenes
     *TODO Ponele 8 neuronas de salida, utiliza Topology para definir la red
     *TODO El vector de una imagen se consigue cargando la imagen y llamando la funcion patron() que retorna un vector
     */
    //srand tiene que ser llamado en el main!!!!!!!!
    std::srand((unsigned int)std::time(NULL));//RANDOM!!!!!
    rand();
/*
    //Cargar todas las imagenes en un vector de doubles que representan cada patron
    vector<vector<double>> patronesDeImagenes;
    BMPImage<double> imageLoader;
    string pathToFolders = "C:\\Users\\Guaberx\\Downloads\\HandWriteRecognition-master\\Corpus\\Images";
    string nameOfFolderX = "_Training";
    string singleFileName = "_";
    string fileType = ".bmp";
    uint32_t numeroDeCarpetas = 10;
    uint32_t numeroDeArchivosPorCarpeta = 36;
    for (int i = 0; i < numeroDeCarpetas; ++i) {//Each Folder
        for (int j = 1; j <= numeroDeArchivosPorCarpeta; ++j) {//Each File from folder
            imageLoader.read(easyPathOfFolder(pathToFolders,i,nameOfFolderX,singleFileName,j,fileType));
            imageLoader.normalize();
            patronesDeImagenes.push_back(imageLoader.patron());//Metemos el vector normalizado de esa imagen a nuestros patrones
        }
    }*/

    //Red neuronal

    vector<double> iv0 = {0,0};
    vector<double> iv1 = {0,1};
    vector<double> iv2 = {1,0};
    vector<double> iv3 = {1,1};
    vector<double> r0 = {0};
    vector<double> r1 = {1};
    vector<double> r2 = {1};
    vector<double> r3 = {0};

    cout << exp(0.2)/(0.2*7) << endl;

    Topology top1(2,2,1);
    Net net0(top1);

    net0.printNeurons();
    net0.printConnections();cout << endl;

    net0.feedForward(iv0);
    net0.printNeurons();
    net0.printConnections();cout << endl;
    net0.calculateError(r0);

    net0.feedForward(iv1);
    net0.printNeurons();
    net0.printConnections();cout << endl;
    net0.calculateError(r1);

    net0.feedForward(iv2);
    net0.printNeurons();
    net0.printConnections();cout << endl;
    net0.calculateError(r2);

    net0.feedForward(iv3);
    net0.printNeurons();
    net0.printConnections();cout << endl;
    net0.calculateError(r3);
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
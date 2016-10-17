#include "MACROS.h"
#include "BMPImageLoader.h"
#include "Graph/Graph.h"
template <typename T>
vector<T> sample(uint32_t size){

}

int main1() {
    BMPImage t1;
    t1.read("C:\\Users\\Guaberx\\Desktop\\HandWriteRecognition\\Corpus\\Images\\A_Training\\Lower\\_05.bmp");
    //t1.print();
    t1.normalize();
    t1.printNormalized();

    Graph<uint16_t > a;
    for_each(t1.getNormalizedData().begin(),t1.getNormalizedData().end(),
             [&a](uint16_t i){
                 a.insVertice(i);
             });

    //a.save("C:\\Users\\Guaberx\\Desktop\\HandWriteRecognition\\HolaJuan");
    /*Graph<uint16_t> a;
    a.load("C:\\Users\\Guaberx\\Desktop\\HandWriteRecognition\\HolaJuan");

    a.setArco(0,1,5);*/
    return 0;
    /*
     * Guardar imagen en vector
     * Binarizarla:
     *      Coger el ((.red + .green + .blue)/3) < umbral  127 o algo asi
     * Imprimirla
     * Esqueletizarla (filtros de sobel o conney)
     * Guardarla en una base de datos
     * Corpus: 80% Training; 10% Pruebas, Ajustes, Tuning; 10% Evaluacion, Test
     * Metodo: Leave One Out
     * Distancia euclidiana del promedio del vector prueba de un tipo de lo que metemos para saber a cual se parece mas
     */
}

int main(){
    MAIN(main1);
}
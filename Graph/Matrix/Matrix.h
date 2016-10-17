#pragma once
#include "Node.h"
#define TEMPLATE(x) template <typename x>
TEMPLATE(T)
class Matrix
{
	Node<T>* headCell;//The 0,0 of the matrix
    //Utility functions to simplify the Publc functions
	void joinRowNode(Node<T>* first);
    void joinColNode(Node<T>* first);
    void delRow(Node<T>* first);
	void delCol(Node<T>* first);

public:
	Matrix():headCell(NULL){}
	Matrix(int nRows, int nCols);
    ~Matrix();

	bool empty(){return headCell == NULL;}
    void clean();

    //TODO Puede que en este caso sea mejor guardar el tamano
	int RowSize();//Returns the number of rows
	int ColSize();//Returns the number of colmuns

	void addRow();//Adds an empty Row to the Matrix
    void addRow(int n);//Adds n empty Rows to the Matrix
	void addCol();//Adds an empty Column to the Matrix
    void addCol(int n);//Adds n empty Column to the Matrix
	void addRowCol(){
        if(ColSize() > 0){
            addRow();
        }
        addCol();}//Adds an empty Row and a Column to the matrix
    void addRowCol(int n){//TODO CUANDO SE ANADE A UNA MATRIX VACIA UNA FILA, TAMBIEN SE ANADE UNA COLUMNA Y VICEVERSA
        for(int i = 0; i < n; ++i){
            addRowCol();
        }
    }//Adds n empty Row and n empty Columns to the matrix

	void delRow(int Row);//Deletes a row
	void delCol(int Col);//Deletes a column

	void modifyCell(int Row, int Col, T newElem);//Modifies the element in a cell
	T cellInfo(int Row, int Col);//Returns the element in the cell

	void printMatrix();

    //T &operator[](uint32_t i){}

    Matrix<T>& operator=(Matrix<T> &other){
        uint8_t comparison = 0;
        //Vemos que no sean iguales
        if(RowSize() == RowSize() && ColSize() == other.ColSize()){
            for (int i = 0; i < RowSize(); ++i) {
                for (int j = 0; j < ColSize(); ++j) {
                    if(cellInfo(i,j) != other.cellInfo(i,j)){
                        comparison = 1;
                        break;
                    }
                }
                if(comparison) break;
            }
        }else{
            comparison = 1;
        }
        if(comparison){
            clean();
            addRow(other.RowSize());
            addCol(other.ColSize()-1);
            for (int i = 0; i < other.RowSize(); i++) {
                for (int j = 0; j < other.ColSize(); ++j) {
                    //Aqui copiamos todo
                    modifyCell(i,j,other.cellInfo(i,j));
                }
            }
        }
        return *this;
    }
    //TODO REVISAR ESTA
    Matrix<T> operator=(Matrix<T> &&other){
        auto temp = headCell;
        headCell = other.headCell;
        other.headCell = temp;
        return *this;
    }

    friend std::ostream &operator <<(std::ostream &output, Matrix<T> &OU){
        for (int i = 0; i < OU.RowSize(); ++i)
        {
            output << "\t";
            for (int j = 0; j < OU.ColSize(); ++j)
            {
                output << OU.cellInfo(i,j) << " ";
            }
            output << std::endl;
        }
        return output;
    }

    T OPHelper(uint32_t i, uint32_t j){

    }

    T &operator[](uint32_t ij[2]);
};

TEMPLATE(T)
void Matrix<T>::joinRowNode(Node<T>* first){
	//Re conectamos los nodos
	if(first == NULL)
		return;
	if(first -> getTop() != NULL){
		first -> getTop() -> setBot(first -> getBot());
	}
	if(first -> getBot() != NULL){
		first -> getBot() -> setTop(first -> getTop());
	}
}
//Private Functions
TEMPLATE(T)
void Matrix<T>::delRow(Node<T>* first){
    if(first != NULL){
        if(headCell == first){
            headCell = headCell -> getBot();
        }
        Node<T>* pTemp = first;
        Node<T>* p2Temp = NULL;
        while(pTemp != NULL){
            p2Temp = pTemp;
            joinRowNode(pTemp);

            pTemp = pTemp -> getNext();
            delete p2Temp;
            p2Temp = NULL;
        }
    }
}
TEMPLATE(T)
void Matrix<T>::joinColNode(Node<T>* first){
    //Re conectamos los nodos
    if(first == NULL)
        return;
    if(first -> getPrevious() != NULL){
        first -> getPrevious() -> setNext(first -> getNext());
    }
    if(first -> getNext() != NULL){
        first -> getNext() -> setPrevious(first -> getPrevious());
    }
}
TEMPLATE(T)
void Matrix<T>::delCol(Node<T>* first){
    if(first != NULL){
        if(headCell == first){
            headCell = headCell -> getNext();
        }
        Node<T>* pTemp = first;
        Node<T>* p2Temp = NULL;
        while(pTemp != NULL){
            p2Temp = pTemp;
            joinColNode(pTemp);

            pTemp = pTemp -> getBot();
            delete p2Temp;
            p2Temp = NULL;
        }
    }
}
TEMPLATE(T)
//Public Functions
Matrix<T>::Matrix(int nRows, int nCols):headCell(NULL){
    for (int i = 0; i < nRows; ++i)
    {
        addRow();
    }
    //nCols-1 porque al agregar filas se agrega la primera columna
    for (int j = 0; j < nCols-1; ++j)
    {
        addCol();
    }
}
TEMPLATE(T)
Matrix<T>::~Matrix(){//TODO HERES AN INFINITE LOOP
    //Borra Toda la matrix y libera toda la memoria
    clean();
}
TEMPLATE(T)
void Matrix<T>::clean(){
    //Borra Toda la matrix y libera toda la memoria
    while(headCell!=NULL){
        delCol(0);
    }
}
//TODO ESTAS DOS!!!!
TEMPLATE(T)
int Matrix<T>::RowSize(){
    //Number of elements in a row (# of columns)
    int count = 0;
    Node<T>* pTemp = headCell;
    while(pTemp != NULL){
        count++;
        pTemp = pTemp->getBot();
    }
    return count;
}
TEMPLATE(T)
int Matrix<T>::ColSize(){
    //Number of elements in a colimn (# of rows)
    int count = 0;
    Node<T>* pTemp = headCell;
    while(pTemp != NULL){
        count++;
        pTemp = pTemp->getNext();
    }
    return count;
}
/*TEMPLATE(T)
void Matrix<T>::addRow() {

}*/
TEMPLATE(T)
//Adds an empty Row to the Matrix
void Matrix<T>::addRow(){
    if(empty()){
        headCell = new Node<T>();
    }else{
        Node<T>* pTemp = headCell;
        Node<T>* p2Temp = headCell;

        //Posicionamos pTemp en la ultima Fila
        while(pTemp -> getBot() != NULL){
            pTemp = pTemp -> getBot();
        }

        //Le agregamos a cada elemento de la Fila un bot
        p2Temp = pTemp;//p2Temp sirve para el siguiente paso
        while(pTemp != NULL){
            Node<T>* newNode = new Node<T>;
            pTemp -> setBot(newNode);
            newNode -> setTop(pTemp);
            /*if(pTemp->getNext() != NULL){
                newNode -> setNext(pTemp->getNext()->getBot());
            }if(pTemp->getPrevious() != NULL){
                newNode -> setPrevious(pTemp->getPrevious()->getBot());
            }*/
            //TODO SET TODOS LOS LADOS
            pTemp = pTemp -> getNext();
        }

        //Le agregamos a cada elemento de la nueva Fila un next y prev
        pTemp = p2Temp;//Actualizamos el puntero
        pTemp = pTemp -> getBot();
        p2Temp = p2Temp -> getNext();
        while(p2Temp!=NULL){
            pTemp -> setNext(p2Temp -> getBot());
            p2Temp -> getBot() ->setPrevious(pTemp);

            p2Temp = p2Temp -> getNext();
            pTemp = pTemp -> getNext();
        }

    }
}
TEMPLATE(T)
void Matrix<T>::addRow(int n) {
    for (int i = 0; i < n; ++i) {
        addRow();
    }
}
/*TEMPLATE(T)
//Adds an empty Column to the Matrix
void Matrix<T>::addCol(){

}*/
TEMPLATE(T)
//Adds an empty Column to the Matrix
void Matrix<T>::addCol(){//TODO REVISAR
    if(empty()){
        headCell = new Node<T>();
    }else{
        Node<T>* pTemp = headCell;
        Node<T>* p2Temp = NULL;

        //Posicionamos pTemp en la ultima Columna
        while(pTemp ->getNext() != NULL){
            pTemp = pTemp -> getNext();
        }

        //Le agregamos a cada elemento de la Columna un next
        p2Temp = pTemp;//p2Temp sirve para el siguiente paso
        while(pTemp != NULL){
            Node<T>* newNode = new Node<T>;
            pTemp -> setNext(newNode);
            newNode -> setPrevious(pTemp);
            pTemp = pTemp -> getBot();
        }

        //Le agregamos a cada elemento de la nueva Columna un next y prev
        pTemp = p2Temp;//Actualizamos el puntero
        pTemp = pTemp -> getNext();
        p2Temp = p2Temp -> getBot();
        while(p2Temp!=NULL && pTemp!=NULL){
            pTemp -> setBot(p2Temp -> getNext());
            p2Temp -> getNext() ->setTop(pTemp);

            p2Temp = p2Temp -> getBot();
            pTemp = pTemp -> getBot();
        }

    }
}
TEMPLATE(T)
void Matrix<T>::addCol(int n) {
    for (int i = 0; i < n; ++i) {
        addCol();
    }
}
TEMPLATE(T)
void Matrix<T>::delRow(int Row){
    if(Row>=RowSize() || Row<0){
        std::cout << "El numero de Filas introducidas se sale del rango" << std::endl;
        //exit(1);
    }else{
        Node<T>* pTemp = headCell;
        if(pTemp -> getBot() == NULL)
            headCell = NULL;
        else{
            for (int i = 0; i < Row; ++i)
            {
                pTemp = pTemp -> getBot();
            }
            delRow(pTemp);
        }
    }
}
TEMPLATE(T)
void Matrix<T>::delCol(int Col){
    if(Col>=ColSize() || Col<0){
        std::cout << "El numero de Columnas introducidas PARA ELIMINAR se sale del rango" << std::endl;
        //exit(1);
    }else{
        Node<T>* pTemp = headCell;
        if(pTemp -> getNext() == NULL){
            delete headCell;
            headCell = NULL;
        }
        else{
            for (int i = 0; i < Col; ++i)
            {
                pTemp = pTemp -> getNext();
            }
            delCol(pTemp);
        }
    }
}
TEMPLATE(T)
//Modifies the element in a cell
void Matrix<T>::modifyCell(int Row, int Col, T newElem){
    if(Row>=RowSize() || Row<0){
        std::cout << "El numero de filas introducidas PARA MODIFICAR se sale del rango" << std::endl;
        //exit(1);
    }else if(Col>=ColSize() || Col<0){
        std::cout << "El numero de columnas introducidas PARA MODIFICAR se sale del rango" << std::endl;
        //exit(1);
    }else{
        Node<T>* pTemp = headCell;
        for (int i = 0; i < Row; ++i)
        {
            pTemp = pTemp -> getBot();
        }
        for (int j = 0; j < Col; ++j)
        {
            pTemp = pTemp -> getNext();
        }

        pTemp -> setElem(newElem);
    }
}
TEMPLATE(T)
//Returns the element in the cell
T Matrix<T>::cellInfo(int Row, int Col){
    //TODO REVISAR
    if(Row>=RowSize()){
        std::cout << "El Valor Row se sale del rango" << std::endl;
        //exit(1);
    }else if(Col>=ColSize()){
        std::cout << "El Valor Col se sale del rango" << std::endl;
        //exit(1);
    }else{
        Node<T>* pTemp = headCell;
        for (int i = 0; i < Row; ++i)
        {
            pTemp = pTemp -> getBot();
        }
        for (int j = 0; j < Col; ++j)
        {
            pTemp = pTemp -> getNext();
        }

        return pTemp -> getElem();
    }
}
TEMPLATE(T)
void Matrix<T>::printMatrix(){
    for (int i = 0; i < RowSize(); ++i)
    {
        std::cout << "\t";
        for (int j = 0; j < ColSize(); ++j)
        {
            std::cout << cellInfo(i,j) << " ";
        }
        std::cout << std::endl;
    }
}
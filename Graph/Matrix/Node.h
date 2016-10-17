#pragma once
#include <iostream>
#include <cstdlib>


//Es utilizada para crear una matriz con cada nodo con conexiones hacia todos los nodos adyacentes
template <class T>
class Node
{
    T elem;
    Node<T>* next;
    Node<T>* previous;
    Node<T>* top;
    Node<T>* bot;
public:

    Node():elem(T()), next(NULL),previous(NULL),top(NULL),bot(NULL){}

    Node(T elem):elem(elem), next(NULL),previous(NULL),top(NULL),bot(NULL){}

    ~Node(){};

    T getElem(){return elem;}

    Node<T>* getNext(){return next;}

    Node<T>* getPrevious(){return previous;}

    Node<T>* getTop(){return top;}

    Node<T>* getBot(){return bot;}

    void setElem(T x){elem = x;}

    void setNext(Node<T>* newNext){next = newNext;}

    void setPrevious(Node<T>* newPrevious){previous = newPrevious;}

    void setTop(Node<T>* newTop){top = newTop;}

    void setBot(Node<T>* newBot){bot = newBot;}
};
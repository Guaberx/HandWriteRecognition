//
// Created by Guaberx on 9/26/2016.
//

#ifndef GRAPHTALLEROBJETOS_MACROS_H
#define GRAPHTALLEROBJETOS_MACROS_H

#include <iostream>
using std::cout;
using std::endl;
template <typename T>
void toBinary(const T c){
    for (int i = sizeof(T)*8-1; i >= 0; --i) {
        if(c & (1 << i)){
            cout << 1;
        }else
            cout << 0;
    }
    cout << endl;
}
//Hace una union unica entre los tipos
#define CHARUNIONCAST(__type,__name) \
union{\
    __type t ;\
    char s[sizeof(__type)];\
}__name;

//Hace el cast a char* Y guarda en el buffer y la union __name
#define CASTTOCHARFROMUNION(__index, __buffer, __data, __type,__name) \
CHARUNIONCAST(__type,__name) \
__name.t = __data; \
for (int i = 0; i < sizeof(__type); ++i) { \
    __buffer[__index] = __name.s[i]; \
    __index++; \
}

template <typename T, typename Q>
void* anyCasting(T data){
    Q* test = new Q[sizeof(T)/sizeof(Q)];//Cuanto le cabe a Q de T
    for (int i = 0; i < sizeof(T); ++i) {
        test[i] = (data >> (sizeof(T)-(i+1))*8);//i+1 porque van desfazados por uno porque i comienza en 0
    }
    return test;
}

#endif //GRAPHTALLEROBJETOS_MACROS_H

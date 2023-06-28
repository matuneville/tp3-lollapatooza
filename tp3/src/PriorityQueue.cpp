// Created by neville on 26/06/23.
//

#include "PriorityQueue.h"

PriorityQueue::PriorityQueue(set<Persona> personas): _heap({}), _indicePersona({}){
    // Armamos del diccionario con todas las personas e indice 0 (momentáneo)
    for(auto a: personas){ // O(A)
        _indicePersona[a] = 0;
    }
    // Hacemos un ciclo en el diccionario para pushear a todas las personas al heap con el índice correspondiente
    for(auto it = _indicePersona.begin(); it != _indicePersona.end(); ++it){
        _heap.push_back(make_tuple(0, it));
    }

    // actualizo los índices correspondientes
    for(int i=0;i<_heap.size();i++){
        get<1>(_heap[i])->second = i;
    }
}

Persona PriorityQueue::proximo() const{
    return get<1>(_heap[0])->first; // O(1)
}

void PriorityQueue::modificar(Persona persona, int gasto){
    // busco el índice de esa persona y le sumo el gasto al heap
    Nat indice = _indicePersona[persona]; // O(log A)
    get<0>(_heap[indice]) += gasto; // O(1)

    // Hago el happyfeet
    Nat indicePadre;
    if(gasto > 0){ // si el gasto es mayor a 0
        if(indice%2 == 0){
            indicePadre = indice/2 - 1;
        }
        else {
            indicePadre = indice/2;
        }
        while(indicePadre >= 0){ // O(log A)
            if(get<0>(_heap[indice]) > get<0>(_heap[indicePadre]) or (get<0>(_heap[indice]) == get<0>(_heap[indicePadre])
                    and get<1>(_heap[indice])->second < get<1>(_heap[indicePadre])->second)){
                // intercambiamos de posición a la persona con su padre
                swap(_heap[indice], _heap[indicePadre]); // O(1)

                // actualizamos los índices correspondientes
                get<1>(_heap[indice])->second = indicePadre; // O(1)
                get<1>(_heap[indicePadre])->second = indice; // O(1)

                indice = indicePadre;
                if(indice%2 ==0){
                    indicePadre = indice/2 - 1;
                }
                else {
                    indicePadre = indice/2;
                }
            }
            else{
                return;
            }
        }
    } // Si el gasto es negativo
    else {
        // Vemos cuántos hijos tiene
        Nat indiceHijoIzq;
        Nat indiceHijoDer;
        Nat indiceHijoMayor;

        // Si tiene dos hijos
        if(2*indice+2 < _heap.size()){ // O(1)
            indiceHijoIzq = 2*indice+1;
            indiceHijoDer = 2*indice+2;
            while(indiceHijoDer < _heap.size()){ // O(log A)
                // Vemos cuál es el hijo mayor
                if(indiceHijoIzq > indiceHijoDer){ // O(1)
                    indiceHijoMayor =  indiceHijoIzq;
                }
                else {
                    indiceHijoMayor =  indiceHijoDer;
                }
                // Hacemos swap con hijo mayor
                if(get<0>(_heap[indice]) < get<0>(_heap[indiceHijoMayor]) or (get<0>(_heap[indice]) == get<0>(_heap[indiceHijoMayor])
                        and get<1>(_heap[indice])->second > get<1>(_heap[indiceHijoMayor])->second)){ // O(1)
                    // intercambiamos de posición a la persona con su hijo mayor
                    swap(_heap[indice], _heap[indiceHijoMayor]); // O(1)

                    // actualizamos los índices correspondientes
                    get<1>(_heap[indice])->second = indiceHijoMayor; // O(1)
                    get<1>(_heap[indiceHijoMayor])->second = indice; // O(1)

                    indice = indiceHijoMayor;
                    indiceHijoIzq = 2*indice+2;
                    indiceHijoDer = 2*indice+1;
                }
                else {
                    return;
                }
            }
        }
        // Vemos si tiene 1 hijo. Si es así a lo sumo hacemos 1 swap
        if(2*indice+1 < _heap.size()) {
            indiceHijoIzq = 2 * indice + 1;

            if (get<0>(_heap[indice]) < get<0>(_heap[indiceHijoIzq]) or
                (get<0>(_heap[indice]) == get<0>(_heap[indiceHijoIzq])
                 and get<1>(_heap[indice])->second > get<1>(_heap[indiceHijoIzq])->second)) { // O(1)
                // intercambiamos de posición a la persona con su hijo izq
                swap(_heap[indice], _heap[indiceHijoIzq]); // O(1)

                // actualizamos los índices correspondientes
                get<1>(_heap[indice])->second = indiceHijoIzq; // O(1)
                get<1>(_heap[indiceHijoIzq])->second = indice; // O(1)
            } else {
                return;
            }
        }
    }

}

Nat PriorityQueue::devolverGasto(Persona persona) const {
    // busco el índice de esa persona para saber dónde está en el vector
    Nat i = _indicePersona.at(persona); // O(log A)
    return get<0>(_heap[i]); // O(1)

}
//
// Created by neville on 26/06/23.
//

#include "PriorityQueue.h"

PriorityQueue::PriorityQueue(set<Persona>){

}

Nat PriorityQueue::proximo() const{
    return get<0>(_heap[0]);
}

void PriorityQueue::modificar(Persona persona, Nat gasto){

}

Nat PriorityQueue::devolverGasto(Persona persona) const {
    // busco el índice de esa persona para saber dónde está en el vector
    Nat i = _indicePersona.at(persona);
    return get<i>(_heap[0]);

}
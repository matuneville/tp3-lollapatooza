//
// Created by neville on 26/06/23.
//

#ifndef TP_LOLLA_PRIORITYQUEUE_H
#define TP_LOLLA_PRIORITYQUEUE_H
#include "tipos.h"
#include <set>
#include <vector>
#include <tuple>
#include <map>



class PriorityQueue {
public:
    // Operaciones básicas
    PriorityQueue(set<Persona>);
    Persona proximo() const;
    void modificar(Persona persona, int gasto);
    Nat devolverGasto(Persona persona) const;

private:
    vector<tuple<Nat, map<Persona, Nat>::iterator>> _heap;
    map<Persona, Nat> _indicePersona;
};


#endif //TP_LOLLA_PRIORITYQUEUE_H

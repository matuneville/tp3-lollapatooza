//
// Created by neville on 26/06/23.
//

#include "lollapatuza.h"

void lollapatuza::registrarCompra(Persona persona, IdPuesto idPuesto, Producto item, Nat cant){

}

void lollapatuza::hackear(Persona persona, Producto item){

}

Nat lollapatuza::gastoTotal(Persona persona) const{
    return _gastoTotal.devolverGasto(persona);
}

Persona lollapatuza::mayorGastador() const{
    return _gastoTotal.proximo();
}

IdPuesto lollapatuza::menorStock(Producto item) const{

}

const set<Persona> &lollapatuza::personas() const {
    return _personas;
}

map<IdPuesto, Puesto> lollapatuza::idsDePuestos() const {
    return _puestosPorID;
}



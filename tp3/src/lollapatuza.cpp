//
// Created by neville on 26/06/23.
//
#include "lollapatuza.h"

lollapatuza::lollapatuza(const set<Persona>& personas, const map<IdPuesto, Puesto>& infoPuestos) :
        _personas(personas),
        _puestosPorID(infoPuestos),
        _gastoTotal(PriorityQueue(personas)),
        _puestosHackeables(map<Persona, map<Producto, map<IdPuesto, Puesto>>>())
{
    for (Persona persona : personas) {
        _puestosHackeables[persona] = {};
    }
}

void lollapatuza::compra(Persona persona, IdPuesto idPuesto, Producto item, Nat cant){
    // buscamos el puesto
    Puesto& puesto = _puestosPorID.at(idPuesto); // O(log P)

    // calculo cuánto es el gasto de la compra
    Nat precioTotal = puesto.precioTotal(item,cant); // O(log I)

    // Modificamos gasto total
    _gastoTotal.modificar(persona,precioTotal); // O(log A)


    Nat descuento = puesto.descuentoDe(item,cant);
    map<Producto ,map<IdPuesto,Puesto>>& diccPer = _puestosHackeables[persona];

    // modificamos puestos hackeables
    if(descuento == 0){
        if(diccPer.count(item)){ // O(log I)
            map<IdPuesto, Puesto>& diccItem = diccPer[item];
            if(!diccItem.count(idPuesto)){ // O(log P)
                //diccItem[idPuesto] = puesto; // O(log P)
                diccItem.insert({idPuesto, puesto});
            }
        }
        else {
            diccPer[item] = {}; // O(log I)
            map<IdPuesto, Puesto>& diccItem = diccPer[item];
            //diccItem[idPuesto] = puesto; // O(log P)
            diccItem.insert({idPuesto, puesto});
        }
    }

    // Modificamos el puesto
    puesto.registrarCompra(persona, item, cant); // O(log A + log I + log cant)
}

void lollapatuza::hackear(Persona persona, Producto item){
    // Buscamos el puesto
    map<IdPuesto, Puesto> diccPerItem = _puestosHackeables[persona][item]; // O(log A + log I)
    auto it = diccPerItem.begin(); // O(1)
    Puesto puestoHack = it->second; // O(1)

    // Modificamos el puesto
    puestoHack.registrarHackeo(persona, item); // O(log A + log I)

    // Si deja de ser hackeable, lo quito
    if(!puestoHack.esHackeable(persona, item)){ // O(log A + log I)
        diccPerItem.erase(it); // O(log P)
    }

    // Busco el precio de una unidad de este ítem
    int precioUnidad = puestoHack.precioTotal(item, 1);

    // Modificamos la cola de prioridad
    _gastoTotal.modificar(persona, -precioUnidad);

}

Nat lollapatuza::gastoTotal(Persona persona) const{
    return _gastoTotal.devolverGasto(persona); // O(log A)
}

Persona lollapatuza::mayorGastador() const{
    return _gastoTotal.proximo(); // O(1)
}

IdPuesto lollapatuza::menorStock(Producto item) const{
    map<IdPuesto, Puesto>::const_iterator itPuesto = _puestosPorID.begin();
    Nat menor = (itPuesto->second).stockDe(item);
    IdPuesto menorID = itPuesto->first;

    while(itPuesto != _puestosPorID.end()){ // O(P)
        IdPuesto id = itPuesto->first;
        Puesto puesto = itPuesto->second;
        if(puesto.stockDe(item) < menor){ // O(log I)
            menor = puesto.stockDe(item); // O(log I)
            menorID = id;
        }
        else if(puesto.stockDe(item) == menor){ // O(log I)
            if(id < menorID){
                menor = puesto.stockDe(item); // O(log I)
                menorID = id;
            }
        }
        itPuesto++;
    } // en el ciclo, O(P * log I)
    return menorID;
}

const set<Persona> &lollapatuza::personas() const {
    return _personas; // O(1)
}

map<IdPuesto, Puesto> lollapatuza::idsDePuestos() const {
    return _puestosPorID; //O(1)
}



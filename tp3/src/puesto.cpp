//
// Created by neville on 26/06/23.
//

#include "puesto.h"

Puesto::Puesto(Menu menu, Stock stock, Promociones descuentos): _menu(menu), _stock(stock){
    Promociones ::iterator itItem = descuentos.begin();
    Nat contadorCant = 0;
    Nat sgteDesc = 0;

    while(itItem != descuentos.end()){
        vector<Nat> descPorIndice {0};
        map<Nat,Nat>::iterator itCant = (itItem->second).begin();
        while(itCant != itItem->second.end()) {
            while (contadorCant < itCant->first) {
                descPorIndice.push_back(sgteDesc);
                contadorCant++;
            }
            sgteDesc = itCant->second;
            descPorIndice.push_back(sgteDesc);
            contadorCant++;
            itCant++;
        }
        _descuentos[itItem->first] = descPorIndice;
        contadorCant = 0;
        sgteDesc = 0;
        itItem++;
    }
}

Nat Puesto::stockDe(Producto item){
    if(this->_stock.count(item) > 0)
        return this->_stock[item];
    else return 0;
}

Nat Puesto::descuentoDe(Producto item, Nat cant) {
    if(not this->_descuentos.count(item) )
        return 0;
    else return (this->_descuentos[item])[cant];
}

Nat Puesto::gastoDe(Persona persona) {
    if(not this->_gastoDe.count(persona))
        return 0;
    else return this->_gastoDe[persona];
}

void Puesto::registrarCompra(Persona persona, Producto item, Nat cant){
    Nat precioT = precioTotal(item, cant);
    const Nat descuento = descuentoDe(item,cant);

    if(descuento > 0){
        if(!_comprasConDesc.count(persona)){
            _comprasConDesc[persona] = {};
        }
        map<Producto ,multiset<Nat>>* diccItemConDesc = &_comprasConDesc[persona];
        if(!diccItemConDesc->count(item)){
            (*diccItemConDesc)[item] = {};
        }

        multiset<Nat> conjCantConDesc = (*diccItemConDesc)[item];
        conjCantConDesc.insert(cant);
    }
    else{
        if(!_comprasSinDesc.count(persona)){
            _comprasSinDesc[persona] = {};
        }
        map<Producto ,multiset<Nat>>* diccItemSinDesc = &_comprasSinDesc[persona];
        if(! diccItemSinDesc->count(item)){
            (*diccItemSinDesc)[item] = {};
        }

        multiset<Nat>* conjCantSinDesc = &(*diccItemSinDesc)[item];
        conjCantSinDesc->insert(cant);
    }
    if(!_gastoDe.count(persona)){
        _gastoDe[persona] = precioT;
    }
    else{
        _gastoDe[persona] += precioT;
    }
    _stock[item] -= cant;
}

void Puesto::registrarHackeo(Persona persona, Producto item){
    _stock[item] ++;
    multiset<Nat>* comprasSinDesc = &(_comprasSinDesc[persona])[item];
    multiset<Nat>::iterator cantHackeadaIt = comprasSinDesc->begin();
    if(*cantHackeadaIt == 1){
        comprasSinDesc->erase(cantHackeadaIt);
    }
    else{
        Nat cantidadMenos1 = *cantHackeadaIt;
        comprasSinDesc->erase(cantHackeadaIt);
        comprasSinDesc->insert(cantidadMenos1);
    }
}

Nat Puesto::precioTotal(Producto item, Nat cant){
    Nat precioTotal = _menu.at(item) * cant; //O(log I)
    Nat descuento = _descuentos.at(item)[cant]; //O(log I)
    return  precioTotal * ((100 - descuento) / 100); //O(1)
}

bool Puesto::esHackeable(Persona persona, Producto item){
    if(_comprasSinDesc.count(persona)){
        map<Producto ,multiset<Nat>> comprasPorItemSinDesc = _comprasSinDesc[persona];
        if(comprasPorItemSinDesc.count(item)){
            multiset<Nat> conjCantSinDesc = comprasPorItemSinDesc[item];
            return (conjCantSinDesc.empty());
        }
    }
    return false;
}

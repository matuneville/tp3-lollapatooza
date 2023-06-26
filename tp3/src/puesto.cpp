//
// Created by neville on 26/06/23.
//

#include "puesto.h"

Puesto::Puesto(Menu menu, Stock stock, Promociones descuentos): _menu(menu), _stock(stock){
    
}

Nat Puesto::stockDe(Producto item){
    if(this->_stock.count(item) > 0)
        return this->_stock[item];
    else return 0;
}

Nat Puesto::descuentoDe(Producto item, Nat cant) {
    if(this->_descuentos.count(item) == 0)
        return 0;
    else return (this->_descuentos[item])[cant];
}

Nat Puesto::gastoDe(Persona persona) {
    if(this->_gastoDe.count(persona) == 0)
        return 0;
    else return this->_gastoDe[persona];
}

void Puesto::registrarCompra(Persona persona, Producto item, Nat cant){


}

void Puesto::registrarHackeo(Persona persona, Producto item){

}

Nat Puesto::precioTotal(Producto item, Nat cant){
    precioTotal = _menu.at(item) * cant;
    des
    //descuento = descuento_de(p, i, cant);
    return  precioTotal * ((100 - descuento) / 100);
}

bool Puesto::esHackeable(Persona persona, Producto item){

}

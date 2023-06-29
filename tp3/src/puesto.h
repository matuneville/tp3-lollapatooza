//
// Created by neville on 26/06/23.
//

#ifndef TP_LOLLA_PUESTO_H
#define TP_LOLLA_PUESTO_H
#include "tipos.h"
#include "set"
#include "vector"

class Puesto {
public:
    // Operaciones Básicas
    Puesto(Menu menu, Stock stock, Promociones descuentos);
    const Nat stockDe(Producto item) const;
    Nat descuentoDe(Producto item, Nat cant);
    Nat gastoDe(Persona persona);

    // Otras operaciones
    void registrarCompra(Persona persona, Producto item, Nat cant);
    void registrarHackeo(Persona persona, Producto item);
    float precioTotal(Producto item, Nat cant);
    bool esHackeable(Persona persona, Producto item);


private:
    // Estructura
    Menu _menu;
    Stock _stock;
    map<Persona, Nat> _gastoDe;
    map<Producto , vector<Nat>> _descuentos;
    map<Persona, map<Producto, multiset<Nat>>> _comprasConDesc;
    map<Persona, map<Producto, multiset<Nat>>> _comprasSinDesc;
};


#endif //TP_LOLLA_PUESTO_H

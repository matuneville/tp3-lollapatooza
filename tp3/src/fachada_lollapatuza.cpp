#include "fachada_lollapatuza.h"


Puesto FachadaLollapatuza::structToPuesto (aed2_Puesto aed2Puesto){
    return Puesto(aed2Puesto.menu, aed2Puesto.stock, aed2Puesto.promociones);
}

const map<IdPuesto, Puesto> FachadaLollapatuza::diccFachada_a_diccLolla(const map<IdPuesto, aed2_Puesto> &infoPuestos){
    map<IdPuesto, Puesto> infoPuestosAux;
    for (auto it = infoPuestos.begin(); it != infoPuestos.end(); it++){
        infoPuestosAux.insert({it->first, structToPuesto(it->second)});
    }
    return infoPuestosAux;
}

FachadaLollapatuza::FachadaLollapatuza(const set<Persona> &personas, const map<IdPuesto, aed2_Puesto> &infoPuestos):
        _lolla(personas, diccFachada_a_diccLolla(infoPuestos)){}

void FachadaLollapatuza::registrarCompra(Persona persona, Producto producto, Nat cant, IdPuesto idPuesto) {
    _lolla.compra(persona, idPuesto, producto, cant);
}

void FachadaLollapatuza::hackear(Persona persona, Producto producto) {
    _lolla.hackear(persona, producto);
}

Nat FachadaLollapatuza::gastoTotal(Persona persona) const {
    return _lolla.gastoTotal(persona);
}

Persona FachadaLollapatuza::mayorGastador() const {
    return _lolla.mayorGastador();
}

IdPuesto FachadaLollapatuza::menorStock(Producto producto) const {
   return _lolla.menorStock(producto);
}

const set<Persona> &FachadaLollapatuza::personas() const {
    return _lolla.personas();
}

Nat FachadaLollapatuza::stockEnPuesto(IdPuesto idPuesto, const Producto &producto) const {
    return (_lolla.idsDePuestos()).at(idPuesto).stockDe(producto);
}

Nat FachadaLollapatuza::descuentoEnPuesto(IdPuesto idPuesto, const Producto &producto, Nat cantidad) const {
    return (_lolla.idsDePuestos()).at(idPuesto).descuentoDe(producto,cantidad);
}

Nat FachadaLollapatuza::gastoEnPuesto(IdPuesto idPuesto, Persona persona) const {
    Nat gasto = ((_lolla.idsDePuestos()).at(idPuesto)).gastoDe(persona);
    return gasto;
}

set<IdPuesto> FachadaLollapatuza::idsDePuestos() const {
    set<IdPuesto> conjunto;
    map<IdPuesto, Puesto> ids = _lolla.idsDePuestos();
    for (auto it = ids.begin(); it != ids.end(); ++it) {
        int clave = it->first;
        conjunto.insert(clave);
    }
    return conjunto;
}
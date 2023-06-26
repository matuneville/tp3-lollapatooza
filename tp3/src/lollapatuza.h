#ifndef TP_LOLLA_LOLLAPATUZA_H
#define TP_LOLLA_LOLLAPATUZA_H
#include "tipos.h"
#include "set"
#include "puesto.h"
#include "PriorityQueue.h"

class lollapatuza {
public:
    lollapatuza(const set<Persona>& personas, const map<IdPuesto, aed2_Puesto>& infoPuestos);

    void registrarCompra(Persona persona, IdPuesto idPuesto, Producto item, Nat cant);

    void hackear(Persona persona, Producto item);

    Nat gastoTotal(Persona persona) const;

    Persona mayorGastador() const;

    IdPuesto menorStock(Producto item) const;

    const set<Persona>& personas() const;

    map<IdPuesto, Puesto> idsDePuestos() const;

private:

    // Estructura
    set<Persona> _personas;
    map<IdPuesto, Puesto> _puestosPorID;
    PriorityQueue _gastoTotal;
    map<Persona, map<Producto, map<IdPuesto, Puesto>>> _puestosHackeables;

    // Operaciones para obtener información de los puestos
    Nat stockEnPuesto(IdPuesto idPuesto, const Producto& producto) const;
    Nat descuentoEnPuesto(IdPuesto idPuesto, const Producto& producto, Nat cantidad) const;
    Nat gastoEnPuesto(IdPuesto idPuesto, Persona persona) const;
};


#endif //TP_LOLLA_LOLLAPATUZA_H

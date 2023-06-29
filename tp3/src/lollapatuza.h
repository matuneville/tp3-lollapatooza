#ifndef TP_LOLLA_LOLLAPATUZA_H
#define TP_LOLLA_LOLLAPATUZA_H
#include "tipos.h"
#include "set"
#include "puesto.h"
#include "PriorityQueue.h"

class lollapatuza {
public:
    lollapatuza(const set<Persona>& personas, const map<IdPuesto, Puesto>& infoPuestos);
    void compra(Persona persona, IdPuesto idPuesto, Producto item, Nat cant);
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
    map<Persona, map<Producto, map<IdPuesto, Puesto*>>> _puestosHackeables;
};


#endif //TP_LOLLA_LOLLAPATUZA_H

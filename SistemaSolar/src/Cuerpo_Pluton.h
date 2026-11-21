#pragma once
#include "Contratos.h"

inline Cuerpo crearPluton()
{
    Cuerpo c;
    c.nombre = "Pluton";
    c.radio = 0.30f;
    c.distancia = 36.0f;
    c.periodoOrbital = 365.0f;
    return c;
}

#pragma once
#include "Contratos.h"

inline Cuerpo crearMercurio()
{
    Cuerpo c;
    c.nombre = "Mercurio";
    c.radio = 0.40f;
    c.distancia = 6.0f;
    c.periodoOrbital = 365.0f;
    return c;
}

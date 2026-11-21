#pragma once
#include "Contratos.h"

inline Cuerpo crearMarte()
{
    Cuerpo c;
    c.nombre = "Marte";
    c.radio = 0.40f;
    c.distancia = 15.0f;
    c.periodoOrbital = 365.0f;
    return c;
}

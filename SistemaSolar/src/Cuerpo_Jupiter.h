#pragma once
#include "Contratos.h"

inline Cuerpo crearJupiter()
{
    Cuerpo c;
    c.nombre = "Jupiter";
    c.radio = 1.00f;
    c.distancia = 19.0f;
    c.periodoOrbital = 365.0f;
    return c;
}

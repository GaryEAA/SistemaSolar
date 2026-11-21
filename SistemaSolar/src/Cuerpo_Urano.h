#pragma once
#include "Contratos.h"

inline Cuerpo crearUrano()
{
    Cuerpo c;
    c.nombre = "Urano";
    c.radio = 0.60f;
    c.distancia = 28.0f;
    c.periodoOrbital = 365.0f;
    return c;
}

#pragma once
#include "Contratos.h"

inline Cuerpo crearTierra()
{
    Cuerpo c;
    c.nombre = "Tierra";
    c.radio = 0.50f;
    c.distancia = 12.0f;
    c.periodoOrbital = 365.0f;
    return c;
}

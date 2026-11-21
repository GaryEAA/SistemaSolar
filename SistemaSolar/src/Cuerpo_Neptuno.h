#pragma once
#include "Contratos.h"

inline Cuerpo crearNeptuno()
{
    Cuerpo c;
    c.nombre = "Neptuno";
    c.radio = 0.60f;
    c.distancia = 32.0f;
    c.periodoOrbital = 365.0f;
    return c;
}

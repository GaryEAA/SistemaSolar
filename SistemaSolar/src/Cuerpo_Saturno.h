#pragma once
#include "Contratos.h"

inline Cuerpo crearSaturno()
{
    Cuerpo c;
    c.nombre = "Saturno";
    c.radio = 1.00f;
    c.distancia = 24.0f;
    c.periodoOrbital = 365.0f;
    return c;
}

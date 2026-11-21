#pragma once
#include "Contratos.h"

inline Cuerpo crearVenus()
{
    Cuerpo c;
    c.nombre = "Venus";
    c.radio = 0.50f;
    c.distancia = 9.0f;
    c.periodoOrbital = 365.0f;
    return c;
}

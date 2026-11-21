#pragma once
#include "Contratos.h"

inline Cuerpo crearLuna()
{
    Cuerpo c;
    c.nombre = "Luna";
    c.radio = 0.15f;
    c.distancia = 1.3f;
    c.periodoOrbital = 365.0f;
    c.padre = TIERRA;
    return c;
}

#pragma once
#include "Contratos.h"

inline Cuerpo crearSol()
{
    Cuerpo c;
    c.nombre = "Sol";
    c.radio = 2.50f;
    c.emisivo = true;
    return c;
}

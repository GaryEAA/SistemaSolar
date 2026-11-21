#pragma once
#include "Contratos.h"

inline Cuerpo crearSol()
{
    Cuerpo c;
    c.nombre = "Sol";
    c.radio = 3.0f;
    c.periodoRotacion = 609.0f;
    c.inclinacionEje = 7.25f;
    c.emisivo = true;
    c.rutaTextura = "res/Texture/sol.jpg";
    return c;
}

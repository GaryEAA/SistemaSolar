#pragma once
#include "Contratos.h"

inline Cuerpo crearNeptuno()
{
    Cuerpo c;
    c.nombre = "Neptuno";
    c.radio = 0.82f;
    c.distancia = 38.0f;
    c.periodoOrbital = 60190.0f;
    c.periodoRotacion = 16.1f;
    c.inclinacionEje = 28.3f;
    c.inclinacionOrbita = 1.8f;
    c.faseInicial = 250.0f;
    c.rutaTextura = "res/Texture/neptuno.jpg";
    return c;
}

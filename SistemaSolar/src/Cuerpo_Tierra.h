#pragma once
#include "Contratos.h"

inline Cuerpo crearTierra()
{
    Cuerpo c;
    c.nombre = "Tierra";
    c.radio = 0.5f;
    c.distancia = 11.0f;
    c.periodoOrbital = 365.25f;
    c.periodoRotacion = 23.93f;
    c.inclinacionEje = 23.4f;
    c.inclinacionOrbita = 0.0f;
    c.faseInicial = 120.0f;
    c.rutaTextura = "res/Texture/tierra.jpg";
    return c;
}
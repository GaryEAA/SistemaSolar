#pragma once
#include "Contratos.h"

inline Cuerpo crearPluton()
{
    Cuerpo c;
    c.nombre = "Pluton";
    c.radio = 0.18f;
    c.distancia = 43.0f;
    c.periodoOrbital = 90560.0f;
    c.periodoRotacion = 153.3f;
    c.inclinacionEje = 122.5f;
    c.inclinacionOrbita = 17.2f;
    c.faseInicial = 20.0f;
    c.rutaTextura = "res/Texture/pluton.jpg";
    return c;
}
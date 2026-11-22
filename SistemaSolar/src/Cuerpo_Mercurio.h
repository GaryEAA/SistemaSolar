#pragma once
#include "Contratos.h"

inline Cuerpo crearMercurio()
{
    Cuerpo c;
    c.nombre = "Mercurio";
    c.radio = 0.25f;
    c.distancia = 6.0f;
    c.periodoOrbital = 88.0f;
    c.periodoRotacion =1407.6f;
    c.inclinacionEje = 0.03f;
    c.inclinacionOrbita = 7.0f;
    c.faseInicial = 40.0f;
    c.rutaTextura = "res/Texture/mercurio.jpg";
    return c;
}

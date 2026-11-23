#pragma once
#include "Contratos.h"

inline Cuerpo crearJupiter()
{
    Cuerpo c;
    c.nombre = "Jupiter";
    c.radio = 1.6f;
    c.distancia = 20.0f;
    c.periodoOrbital = 4333.0f;
    c.periodoRotacion = 9.93f;
    c.inclinacionEje = 3.1f;
    c.inclinacionOrbita = 1.3f;
    c.faseInicial = 300.0f;
    c.rutaTextura = "res/Texture/jupiter.jpg";
    
    return c;
}

#pragma once
#include "Contratos.h"

inline Cuerpo crearJupiter()
{
    Cuerpo c;
    c.nombre = "Jupiter";
    c.radio = 1.6f;
    c.distancia = 20.0f;
    c.periodoOrbital = 4333.0.0f;    //dias
    c.periodoRotacion = 9.93f;     // horas (el que gira más rápido)
    c.inclinacionEje = 3.1f;      // grados
    c.inclinacionOrbita = 1.3f;      // grados
    c.faseInicial = 300.0f;    // grados
    c.rutaTextura = "res/Texture/jupiter.jpg";
    
    return c;
}

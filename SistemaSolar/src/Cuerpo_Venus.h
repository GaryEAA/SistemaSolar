#pragma once
#include "Contratos.h"

inline Cuerpo crearVenus()
{
    Cuerpo c;
    c.nombre = "Venus";
    c.distancia = 8.5f;
    c.periodoOrbital = 224.7f;
    c.periodoRotacion = 5832.5f;
    c.inclinacionEje = 177.4f;
    c.inclinacionOrbita = 3.4f;
    c.faseInicial = 250.0f;
    c.rutaTextura = "res/Texture/venus.jpg";
    return c;
}

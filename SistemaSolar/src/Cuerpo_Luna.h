#pragma once
#include "Contratos.h"

inline Cuerpo crearLuna()
{
    Cuerpo c;
    c.nombre            = "Luna";
    c.radio             = 0.14f;
    c.distancia         = 1.1f;
    c.periodoOrbital    = 27.3f;
    c.periodoRotacion   = 0.0f;
    c.inclinacionEje    = 6.7f;
    c.inclinacionOrbita = 5.1f;
    c.faseInicial       = 0.0f;
    c.padre             = TIERRA;
    c.sincrona          = true; // Usa el mismo periodo que la orbita.

    c.rutaTextura       = "res/Texture/luna.jpg";
    return c;
}

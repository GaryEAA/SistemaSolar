#pragma once
#include "Contratos.h"

inline Cuerpo crearVenus()
{
    Cuerpo c;
    c.nombre = "Venus";
    c.distancia = 8.5f;
    c.periodoOrbital = 224.7f;    // días
    c.periodoRotacion = 5832.5f;   // horas (positivo; gira al revés por inclinacionEje > 90°)
    c.inclinacionEje = 177.4f;    // grados (> 90° hace que gire en sentido retrógrado)
    c.inclinacionOrbita = 3.4f;      // grados
    c.faseInicial = 250.0f;    // grados
    c.rutaTextura = "res/Texture/venus.jpg";
    return c;
}

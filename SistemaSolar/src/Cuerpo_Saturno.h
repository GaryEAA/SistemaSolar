#pragma once
#include "Contratos.h"
inline Cuerpo crearSaturno()
{
    Cuerpo c;
    c.nombre = "Saturno";
    c.radio = 1.35f;
    c.distancia = 27.0f;
    c.periodoOrbital = 10759.0f;   
    c.periodoRotacion = 10.7f;     
    c.inclinacionEje = 26.7f;      
    c.inclinacionOrbita = 2.5f;   
    c.faseInicial = 70.0f;        
    c.rutaTextura = "res/Texture/saturno.jpg";
    return c;
}
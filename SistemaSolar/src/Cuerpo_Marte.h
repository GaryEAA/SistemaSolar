#pragma once
#include "Contratos.h"

inline Cuerpo crearMarte()
{
    Cuerpo c;
    c.nombre = "Marte";
    c.radio = 0.27f;                
    c.distancia = 14.0f;
    c.periodoOrbital = 687.0f;    
    c.periodoRotacion = 24.6f;   
    c.inclinacionEje = 25.2f;      
    c.inclinacionOrbita = 1.85f;    
    c.faseInicial = 200.0f;        
    c.rutaTextura = "res/Texture/marte.jpg";
    return c;
}

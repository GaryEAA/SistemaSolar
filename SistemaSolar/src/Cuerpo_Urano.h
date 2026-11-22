#pragma once
#include "Contratos.h"

inline Cuerpo crearUrano()
{
    Cuerpo c;
    c.nombre = "Urano";
    c.radio = 0.85f;                
    c.distancia = 33.0f;            
    c.periodoOrbital = 30687.0f;    
    c.periodoRotacion = 17.2f;      
    c.inclinacionEje = 97.8f;       
    c.inclinacionOrbita = 0.8f;     
    c.faseInicial = 150.0f;         
    c.rutaTextura = "res/Texture/urano.jpg";
    return c;
}

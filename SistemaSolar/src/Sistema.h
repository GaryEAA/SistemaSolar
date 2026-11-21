#pragma once
#include "Contratos.h"

inline std::vector<Cuerpo> crearSistema()
{
    std::vector<Cuerpo> cuerpos(TOTAL_CUERPOS);
    cuerpos[SOL] = crearSol();
    cuerpos[MERCURIO] = crearMercurio();
    cuerpos[VENUS] = crearVenus();
    cuerpos[TIERRA] = crearTierra();
    cuerpos[LUNA] = crearLuna();
    cuerpos[MARTE] = crearMarte();
    cuerpos[JUPITER] = crearJupiter();
    cuerpos[SATURNO] = crearSaturno();
    cuerpos[URANO] = crearUrano();
    cuerpos[NEPTUNO] = crearNeptuno();
    cuerpos[PLUTON] = crearPluton();
    return cuerpos;
}

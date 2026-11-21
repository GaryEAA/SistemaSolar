#pragma once
#include "Contratos.h"

inline glm::vec3 posicionCuerpo(const std::vector<Cuerpo>& cuerpos, int indice, float tiempo)
{
    const Cuerpo& c = cuerpos[indice];
    glm::vec3 posicion(c.distancia, 0.0f, 0.0f);

    if (c.padre >= 0)
        posicion += posicionCuerpo(cuerpos, c.padre, tiempo);

    return posicion;
}

inline glm::mat4 matrizModelo(const std::vector<Cuerpo>& cuerpos, int indice, float tiempo)
{
    glm::mat4 model = glm::translate(glm::mat4(1.0f), posicionCuerpo(cuerpos, indice, tiempo));
    model = glm::scale(model, glm::vec3(cuerpos[indice].radio));
    return model;
}

#pragma once
#include "Contratos.h"

inline float segundosPorVuelta(float dias)
{
    return 6.0f * std::sqrt(dias / 365.25f);
}

inline float segundosPorGiro(float horas)
{
    float segundos = 3.0f * std::sqrt(std::fabs(horas) / 24.0f);
    return horas < 0.0f ? -segundos : segundos;
}

inline float anguloOrbital(const Cuerpo& c, float tiempo)
{
    return c.faseInicial + 360.0f * tiempo / segundosPorVuelta(c.periodoOrbital);
}

inline glm::vec3 posicionCuerpo(const std::vector<Cuerpo>& cuerpos, int indice, float tiempo)
{
    const Cuerpo& c = cuerpos[indice];
    if (c.periodoOrbital <= 0.0f)
        return glm::vec3(0.0f);

    float angulo = glm::radians(anguloOrbital(c, tiempo));
    glm::vec3 local(c.distancia * std::cos(angulo), 0.0f, -c.distancia * std::sin(angulo));

    glm::mat4 inclinacion = glm::rotate(glm::mat4(1.0f), glm::radians(c.inclinacionOrbita), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::vec3 posicion = glm::vec3(inclinacion * glm::vec4(local, 1.0f));

    if (c.padre >= 0)
        posicion += posicionCuerpo(cuerpos, c.padre, tiempo);

    return posicion;
}

inline glm::mat4 matrizModelo(const std::vector<Cuerpo>& cuerpos, int indice, float tiempo)
{
    const Cuerpo& c = cuerpos[indice];

    float giro = 0.0f;
    if (c.sincrona && c.periodoOrbital > 0.0f)
        giro = anguloOrbital(c, tiempo);
    else if (c.periodoRotacion != 0.0f)
        giro = 360.0f * tiempo / segundosPorGiro(c.periodoRotacion);

    glm::mat4 model = glm::translate(glm::mat4(1.0f), posicionCuerpo(cuerpos, indice, tiempo));
    model = glm::rotate(model, glm::radians(c.inclinacionEje), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::rotate(model, glm::radians(giro), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(c.radio));
    return model;
}
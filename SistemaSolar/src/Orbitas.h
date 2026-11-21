#pragma once
#include "Contratos.h"

static std::vector<ObjetoGL> orbitasGL;

inline void iniciarOrbitas(const std::vector<Cuerpo>& cuerpos)
{
    orbitasGL.assign(cuerpos.size(), ObjetoGL());

    for (size_t i = 0; i < cuerpos.size(); i++)
    {
        const Cuerpo& c = cuerpos[i];
        if (c.periodoOrbital <= 0.0f)
            continue;

        float gris = c.padre >= 0 ? 0.55f : 0.38f;
        int puntos = 160;
        Malla3D malla;

        for (int k = 0; k < puntos; k++)
        {
            float angulo = 2.0f * PI * k / puntos;
            malla.vertices.insert(malla.vertices.end(), {
                c.distancia * std::cos(angulo), 0.0f, -c.distancia * std::sin(angulo),
                gris, gris + 0.05f, gris + 0.15f, 0.0f, 0.0f });
            malla.indices.push_back(k);
        }
        orbitasGL[i] = subirMalla(malla, GL_LINE_LOOP);
    }
}

inline void dibujarOrbitas(Shader& shader, const std::vector<Cuerpo>& cuerpos, float tiempo)
{
    shader.setInt("modo", MODO_COLOR);

    for (size_t i = 0; i < cuerpos.size(); i++)
    {
        if (orbitasGL[i].cantidad == 0)
            continue;

        float escala = factorVisible((int)i);
        if (escala < 0.01f)
            continue;

        glm::vec3 centro(0.0f);
        if (cuerpos[i].padre >= 0)
            centro = posicionCuerpo(cuerpos, cuerpos[i].padre, tiempo);

        glm::mat4 model = glm::translate(glm::mat4(1.0f), centro);
        model = glm::rotate(model, glm::radians(cuerpos[i].inclinacionOrbita), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(escala));
        shader.setMat4("model", model);
        dibujarObjeto(orbitasGL[i]);
    }
}

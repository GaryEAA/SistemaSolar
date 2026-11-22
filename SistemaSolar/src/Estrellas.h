#pragma once
#include <random>
#include "Contratos.h"

static ObjetoGL estrellasGL;

inline void iniciarEstrellas()
{
    std::mt19937 azar(2026);
    std::uniform_real_distribution<float> unidad(0.0f, 1.0f);

    Malla3D malla;
    int cantidad = 2500;
    float radio = 400.0f;

    for (int i = 0; i < cantidad; i++)
    {
        float z = unidad(azar) * 2.0f - 1.0f;
        float angulo = unidad(azar) * 2.0f * PI;
        float r = std::sqrt(1.0f - z * z);

        float brillo = 0.35f + 0.65f * std::pow(unidad(azar), 2.0f);
        float tinte = unidad(azar);
        float rojo = brillo * (0.85f + 0.15f * tinte);
        float azul = brillo * (1.0f - 0.15f * tinte);

        malla.vertices.insert(malla.vertices.end(), {
            radio * r * std::cos(angulo), radio * z, radio * r * std::sin(angulo),
            rojo, brillo, azul, 0.0f, 0.0f });
        malla.indices.push_back(i);
    }
    estrellasGL = subirMalla(malla, GL_POINTS);
}

inline void dibujarEstrellas(Shader& shader)
{
    shader.setInt("modo", MODO_COLOR);
    shader.setMat4("model", glm::mat4(1.0f));
    glDisable(GL_DEPTH_TEST);
    glPointSize(1.8f);
    dibujarObjeto(estrellasGL);
    glEnable(GL_DEPTH_TEST);
}
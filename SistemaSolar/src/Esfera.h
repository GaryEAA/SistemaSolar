#pragma once
#include "Contratos.h"

inline Malla3D generarEsfera(float radio, int sectores, int stacks)
{
    Malla3D malla;
    float p[6][3] = { { 0, radio, 0 }, { 0, -radio, 0 }, { radio, 0, 0 }, { -radio, 0, 0 }, { 0, 0, radio }, { 0, 0, -radio } };
    float uv[6][2] = { { 0.5f, 1.0f }, { 0.5f, 0.0f }, { 0.0f, 0.5f }, { 1.0f, 0.5f }, { 0.25f, 0.5f }, { 0.75f, 0.5f } };

    for (int i = 0; i < 6; i++)
        malla.vertices.insert(malla.vertices.end(), { p[i][0], p[i][1], p[i][2], 1.0f, 1.0f, 1.0f, uv[i][0], uv[i][1] });

    malla.indices = { 0, 4, 2, 0, 3, 4, 0, 5, 3, 0, 2, 5, 1, 2, 4, 1, 4, 3, 1, 3, 5, 1, 5, 2 };
    return malla;
}

inline ObjetoGL subirMalla(const Malla3D& malla, GLenum primitiva)
{
    ObjetoGL objeto;
    objeto.primitiva = primitiva;
    objeto.cantidad = (int)malla.indices.size();

    glGenVertexArrays(1, &objeto.VAO);
    glGenBuffers(1, &objeto.VBO);
    glGenBuffers(1, &objeto.EBO);

    glBindVertexArray(objeto.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, objeto.VBO);
    glBufferData(GL_ARRAY_BUFFER, malla.vertices.size() * sizeof(float), malla.vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objeto.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, malla.indices.size() * sizeof(unsigned int), malla.indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    return objeto;
}

inline void dibujarObjeto(const ObjetoGL& objeto)
{
    glBindVertexArray(objeto.VAO);
    glDrawElements(objeto.primitiva, objeto.cantidad, GL_UNSIGNED_INT, 0);
}

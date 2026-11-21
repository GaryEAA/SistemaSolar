#pragma once
#include "Contratos.h"

inline Malla3D generarEsfera(float radio, int sectores, int stacks)
{
    Malla3D malla;
    float sectorStep = 2.0f * PI / sectores;
    float stackStep = PI / stacks;

    for (int i = 0; i <= stacks; ++i)
    {
        float stackAngle = PI / 2.0f - i * stackStep;
        float xz = radio * std::cos(stackAngle);
        float y = radio * std::sin(stackAngle);

        for (int j = 0; j <= sectores; ++j)
        {
            float sectorAngle = j * sectorStep;
            float x = xz * std::cos(sectorAngle);
            float z = -xz * std::sin(sectorAngle);

            malla.vertices.push_back(x);
            malla.vertices.push_back(y);
            malla.vertices.push_back(z);

            malla.vertices.push_back(x / radio + 0.5f);
            malla.vertices.push_back(y / radio + 0.5f);
            malla.vertices.push_back(z / radio + 0.5f);

            malla.vertices.push_back((float)j / sectores);
            malla.vertices.push_back(1.0f - (float)i / stacks);
        }
    }

    for (int i = 0; i < stacks; ++i)
    {
        int k1 = i * (sectores + 1);
        int k2 = k1 + sectores + 1;

        for (int j = 0; j < sectores; ++j, ++k1, ++k2)
        {
            if (i != 0)
            {
                malla.indices.push_back(k1);
                malla.indices.push_back(k2);
                malla.indices.push_back(k1 + 1);
            }
            if (i != (stacks - 1))
            {
                malla.indices.push_back(k1 + 1);
                malla.indices.push_back(k2);
                malla.indices.push_back(k2 + 1);
            }
        }
    }
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

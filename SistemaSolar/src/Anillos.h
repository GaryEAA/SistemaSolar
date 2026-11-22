#pragma once
#include "Contratos.h"

struct EstadoAnillos
{
    ObjetoGL objeto;
    unsigned int textura = 0;
    bool listo = false;
};

inline EstadoAnillos& anillos()
{
    static EstadoAnillos a;
    return a;
}

inline Malla3D generarAnillo(float radioInterior, float radioExterior, int segmentos)
{
    Malla3D malla;
    float paso = 2.0f * PI / segmentos;

    for (int i = 0; i <= segmentos; ++i)
    {
        float ang = i * paso;
        float c = std::cos(ang);
        float s = std::sin(ang);
        float v = (float)i / segmentos;

        // vertice interior: u = 0
        malla.vertices.insert(malla.vertices.end(),
            { radioInterior * c, 0.0f, -radioInterior * s,   0.0f, 1.0f, 0.0f,   0.0f, v });
        // vertice exterior: u = 1
        malla.vertices.insert(malla.vertices.end(),
            { radioExterior * c, 0.0f, -radioExterior * s,   0.0f, 1.0f, 0.0f,   1.0f, v });
    }

    for (int i = 0; i < segmentos; ++i)
    {
        unsigned int in0 = i * 2, out0 = i * 2 + 1;
        unsigned int in1 = i * 2 + 2, out1 = i * 2 + 3;

        // cara de arriba
        malla.indices.insert(malla.indices.end(), { in0, out0, in1,   in1, out0, out1 });
        // cara de abajo
        malla.indices.insert(malla.indices.end(), { in0, in1, out0,   in1, out1, out0 });
    }
    return malla;
}

inline void iniciarAnillos()
{
    EstadoAnillos& a = anillos();
    Malla3D malla = generarAnillo(1.25f, 2.3f, 128);   // en radios de Saturno
    a.objeto = subirMalla(malla, GL_TRIANGLES);
    a.textura = cargarTextura("res/Texture/anillos_saturno.png");
    a.listo = true;
}

inline void dibujarAnillos(Shader& shader, const glm::mat4& modeloPlaneta)
{
    EstadoAnillos& a = anillos();
    if (!a.listo) return;

    shader.use();
    shader.setMat4("model", modeloPlaneta);
    shader.setInt("modo", MODO_SIN_LUZ);
    shader.setFloat("brillo", 1.0f);
    shader.setInt("textura", 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, a.textura);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);

    dibujarObjeto(a.objeto);

    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}
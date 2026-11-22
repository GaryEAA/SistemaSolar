#pragma once
#include "Contratos.h"

inline void actualizarModoPluton(GLFWwindow* window, float deltaTime, const std::vector<Cuerpo>& cuerpos)
{
    EstadoGlobal& e = estado();

    static bool teclaSuelta = true;
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        if (teclaSuelta)
            e.sistemaAntiguo = !e.sistemaAntiguo;
        teclaSuelta = false;
    }
    else
        teclaSuelta = true;

    float meta = e.sistemaAntiguo ? 1.0f : 0.0f;
    float paso = deltaTime / 1.6f;
    if (e.transicionPluton < meta)
        e.transicionPluton = std::fmin(meta, e.transicionPluton + paso);
    else if (e.transicionPluton > meta)
        e.transicionPluton = std::fmax(meta, e.transicionPluton - paso);

    if (!e.sistemaAntiguo && camaraSeleccion() == PLUTON)
        camaraSeguir(-1, cuerpos);
}

inline float factorVisible(int indice)
{
    if (indice != PLUTON)
        return 1.0f;
    float t = estado().transicionPluton;
    return t * t * (3.0f - 2.0f * t);
}
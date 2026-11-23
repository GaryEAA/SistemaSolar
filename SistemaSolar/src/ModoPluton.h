#pragma once
#include "Contratos.h"

inline void actualizarModoPluton(GLFWwindow* window, float deltaTime, const std::vector<Cuerpo>& cuerpos)
{
    static bool teclaPresionada = false;

    // Presionar la tecla P alterna entre Sistema Antiguo (con Pluton) y Sistema Moderno (sin Pluton)
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        if (!teclaPresionada)
        {
            estado().sistemaAntiguo = !estado().sistemaAntiguo;
            teclaPresionada = true;
        }
    }
    else
    {
        teclaPresionada = false;
    }

    // Transicion suave de escala entre 1.0 (visible) y 0.0 (oculto)
    float objetivo = estado().sistemaAntiguo ? 1.0f : 0.0f;
    float velocidad = 2.5f;

    if (estado().transicionPluton < objetivo)
    {
        estado().transicionPluton += velocidad * deltaTime;
        if (estado().transicionPluton > objetivo)
            estado().transicionPluton = objetivo;
    }
    else if (estado().transicionPluton > objetivo)
    {
        estado().transicionPluton -= velocidad * deltaTime;
        if (estado().transicionPluton < objetivo)
            estado().transicionPluton = objetivo;
    }

    // Si la camara estaba siguiendo a Pluton y se cambia a modo moderno, vuelve al Sol
    if (!estado().sistemaAntiguo && camaraSeleccion() == PLUTON)
    {
        camaraSeguir(SOL, cuerpos);
    }
}

inline float factorVisible(int indice)
{
    if (indice == PLUTON)
        return estado().transicionPluton;

    return 1.0f;
}
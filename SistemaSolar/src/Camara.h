#pragma once
#include "Contratos.h"

inline void camaraMouse(GLFWwindow* window, double xpos, double ypos)
{
}

inline void camaraScroll(double desplazamiento)
{
}

inline void camaraTeclado(GLFWwindow* window, float deltaTime, const std::vector<Cuerpo>& cuerpos)
{
}

inline void camaraSeguir(int indice, const std::vector<Cuerpo>& cuerpos)
{
}

inline int camaraSeleccion()
{
    return -1;
}

inline glm::mat4 camaraVista(const glm::vec3& objetivo, float deltaTime)
{
    return glm::lookAt(glm::vec3(0.0f, 45.0f, 110.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

inline glm::mat4 camaraProyeccion(float aspecto)
{
    return glm::perspective(glm::radians(45.0f), aspecto, 0.1f, 1000.0f);
}

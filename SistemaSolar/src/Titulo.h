#pragma once
#include "Contratos.h"
#include <sstream>
#include <iomanip>

inline void actualizarTitulo(GLFWwindow* window, float deltaTime, const std::vector<Cuerpo>& cuerpos)
{
const auto& est = estado();

std::stringstream ss;
ss << "Sistema Solar | Modo: "
    << (est.sistemaAntiguo ? "Antiguo (9 planetas)" : "Moderno (8 planetas)");

if (est.pausa)
{
    ss << " | [PAUSA]";
}
else
{
    ss << " | Vel: x" << std::fixed << std::setprecision(1) << est.escalaTiempo;
}

if (deltaTime > 0.0f)
{
    int fps = static_cast<int>(1.0f / deltaTime);
    ss << " | FPS: " << fps;
}

glfwSetWindowTitle(window, ss.str().c_str());
 
}

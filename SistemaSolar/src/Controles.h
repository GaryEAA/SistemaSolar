#pragma once
#include "Contratos.h"

inline void controlesTeclado(GLFWwindow* window, float deltaTime)
{
    auto& est = estado();
  
  // Variables estáticas para evitar que la tecla parpadee al mantenerla presionada
  static bool espacioAnterior = false;
  static bool oAnterior = false;

  // 1. Pausa / Reanudar con ESPACIO
  bool espacioActual = (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS);
  if (espacioActual && !espacioAnterior)
  {
      est.pausa = !est.pausa;
  }
  espacioAnterior = espacioActual;

  // 2. Mostrar / Ocultar órbitas con O
  bool oActual = (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS);
  if (oActual && !oAnterior)
  {
      est.mostrarOrbitas = !est.mostrarOrbitas;
  }
  oAnterior = oActual;

  // 3. Aumentar velocidad con '+' (teclado numérico o tecla '+/=' principal)
  if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS ||
      glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS)
  {
      est.escalaTiempo += 2.0f * deltaTime;
      if (est.escalaTiempo > 20.0f) est.escalaTiempo = 20.0f;
  }

  // 4. Disminuir velocidad con '-' (teclado numérico o tecla '-' principal)
  if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS ||
      glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS)
  {
       est.escalaTiempo -= 2.0f * deltaTime;
      if (est.escalaTiempo < 0.1f) est.escalaTiempo = 0.1f;
  }
}

#pragma once
#include "Contratos.h"

static float camYaw = 0.6f;
static float camPitch = 0.5f;
static float camDistancia = 110.0f;
static float camDistanciaMeta = 110.0f;
static int camSeguir = -1;
static glm::vec3 camObjetivo(0.0f);
static glm::vec3 camDesde(0.0f);
static float camTransicion = 1.0f;
static double camUltimoX = 0.0;
static double camUltimoY = 0.0;
static bool camPrimerMovimiento = true;

inline float limitarValor(float v, float minimo, float maximo)
{
    return v < minimo ? minimo : (v > maximo ? maximo : v);
}

inline void camaraMouse(GLFWwindow* window, double xpos, double ypos)
{
    bool arrastrando = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
    if (arrastrando && !camPrimerMovimiento)
    {
        camYaw -= (float)(xpos - camUltimoX) * 0.005f;
        camPitch += (float)(ypos - camUltimoY) * 0.005f;
        camPitch = limitarValor(camPitch, -1.5f, 1.5f);
    }
    camPrimerMovimiento = false;
    camUltimoX = xpos;
    camUltimoY = ypos;
}

inline void camaraScroll(double desplazamiento)
{
    camDistanciaMeta *= 1.0f - 0.1f * (float)desplazamiento;
    camDistanciaMeta = limitarValor(camDistanciaMeta, 1.5f, 260.0f);
}

inline void camaraSeguir(int indice, const std::vector<Cuerpo>& cuerpos)
{
    if (indice == camSeguir)
        return;
    camSeguir = indice;
    camDesde = camObjetivo;
    camTransicion = 0.0f;
    camDistanciaMeta = indice < 0 ? 110.0f : std::fmax(cuerpos[indice].radio * 5.0f, 2.5f);
}

inline void camaraTeclado(GLFWwindow* window, float deltaTime, const std::vector<Cuerpo>& cuerpos)
{
    float giro = 1.6f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camYaw += giro;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camYaw -= giro;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camPitch += giro;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camPitch -= giro;
    camPitch = limitarValor(camPitch, -1.5f, 1.5f);

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) camDistanciaMeta *= 1.0f - 0.8f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) camDistanciaMeta *= 1.0f + 0.8f * deltaTime;
    camDistanciaMeta = limitarValor(camDistanciaMeta, 1.5f, 260.0f);

    static const int teclas[] = { GLFW_KEY_0, GLFW_KEY_1, GLFW_KEY_2, GLFW_KEY_3, GLFW_KEY_4,
                                  GLFW_KEY_5, GLFW_KEY_6, GLFW_KEY_7, GLFW_KEY_8, GLFW_KEY_9 };
    static const int cuerposDeTecla[] = { SOL, MERCURIO, VENUS, TIERRA, MARTE,
                                          JUPITER, SATURNO, URANO, NEPTUNO, PLUTON };
    for (int i = 0; i < 10; i++)
        if (glfwGetKey(window, teclas[i]) == GLFW_PRESS)
            camaraSeguir(cuerposDeTecla[i], cuerpos);

    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) camaraSeguir(LUNA, cuerpos);
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) camaraSeguir(-1, cuerpos);

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        camYaw = 0.6f;
        camPitch = 0.5f;
        camaraSeguir(-1, cuerpos);
        camDistanciaMeta = 110.0f;
    }
}

inline int camaraSeleccion()
{
    return camSeguir;
}

inline glm::mat4 camaraVista(const glm::vec3& objetivo, float deltaTime)
{
    if (camTransicion < 1.0f)
    {
        camTransicion = std::fmin(1.0f, camTransicion + deltaTime * 1.5f);
        float k = camTransicion * camTransicion * (3.0f - 2.0f * camTransicion);
        camObjetivo = glm::mix(camDesde, objetivo, k);
    }
    else
    {
        camObjetivo = objetivo;
    }

    camDistancia += (camDistanciaMeta - camDistancia) * std::fmin(1.0f, 6.0f * deltaTime);

    glm::vec3 posicion = camObjetivo + camDistancia * glm::vec3(
        std::cos(camPitch) * std::sin(camYaw),
        std::sin(camPitch),
        std::cos(camPitch) * std::cos(camYaw));

    return glm::lookAt(posicion, camObjetivo, glm::vec3(0.0f, 1.0f, 0.0f));
}

inline glm::mat4 camaraProyeccion(float aspecto)
{
    return glm::perspective(glm::radians(45.0f), aspecto, 0.1f, 1000.0f);
}
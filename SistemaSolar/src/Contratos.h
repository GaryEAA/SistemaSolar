#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

const float PI = 3.14159265359f;

const int MODO_TEXTURA = 0;
const int MODO_COLOR = 1;
const int MODO_SIN_LUZ = 2;

enum IndiceCuerpo
{
    SOL, MERCURIO, VENUS, TIERRA, LUNA, MARTE, JUPITER, SATURNO, URANO, NEPTUNO, PLUTON,
    TOTAL_CUERPOS
};

struct EstadoGlobal
{
    float tiempo = 0.0f;
    float escalaTiempo = 1.0f;
    bool pausa = false;
    bool mostrarOrbitas = true;
    bool sistemaAntiguo = true;
    float transicionPluton = 1.0f;
};

inline EstadoGlobal& estado()
{
    static EstadoGlobal e;
    return e;
}

struct Cuerpo
{
    std::string nombre = "";
    float radio = 1.0f;
    float distancia = 0.0f;
    float periodoOrbital = 0.0f;
    float periodoRotacion = 24.0f;
    float inclinacionEje = 0.0f;
    float inclinacionOrbita = 0.0f;
    float faseInicial = 0.0f;
    int padre = -1;
    bool emisivo = false;
    bool sincrona = false;
    std::string rutaTextura = "res/Texture/planeta_base.jpg";
    unsigned int textura = 0;
};

struct Malla3D
{
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
};

struct ObjetoGL
{
    unsigned int VAO = 0;
    unsigned int VBO = 0;
    unsigned int EBO = 0;
    int cantidad = 0;
    GLenum primitiva = GL_TRIANGLES;
};

inline Cuerpo crearSol();
inline Cuerpo crearMercurio();
inline Cuerpo crearVenus();
inline Cuerpo crearTierra();
inline Cuerpo crearLuna();
inline Cuerpo crearMarte();
inline Cuerpo crearJupiter();
inline Cuerpo crearSaturno();
inline Cuerpo crearUrano();
inline Cuerpo crearNeptuno();
inline Cuerpo crearPluton();

inline Malla3D generarEsfera(float radio, int sectores, int stacks);
inline ObjetoGL subirMalla(const Malla3D& malla, GLenum primitiva);
inline void dibujarObjeto(const ObjetoGL& objeto);
inline void iniciarEstrellas();
inline void dibujarEstrellas(Shader& shader);

inline unsigned int cargarTextura(const char* ruta);
inline void cargarTexturasDelSistema(std::vector<Cuerpo>& cuerpos);

inline glm::vec3 posicionCuerpo(const std::vector<Cuerpo>& cuerpos, int indice, float tiempo);
inline glm::mat4 matrizModelo(const std::vector<Cuerpo>& cuerpos, int indice, float tiempo);

inline void camaraMouse(GLFWwindow* window, double xpos, double ypos);
inline void camaraScroll(double desplazamiento);
inline void camaraTeclado(GLFWwindow* window, float deltaTime, const std::vector<Cuerpo>& cuerpos);
inline int camaraSeleccion();
inline glm::mat4 camaraVista(const glm::vec3& objetivo, float deltaTime);
inline glm::mat4 camaraProyeccion(float aspecto);
inline void iniciarOrbitas(const std::vector<Cuerpo>& cuerpos);
inline void dibujarOrbitas(Shader& shader, const std::vector<Cuerpo>& cuerpos, float tiempo);

inline Malla3D generarAnillo(float radioInterior, float radioExterior, int segmentos);
inline void iniciarAnillos();
inline void dibujarAnillos(Shader& shader, const glm::mat4& modeloPlaneta);

inline void camaraSeguir(int indice, const std::vector<Cuerpo>& cuerpos);

inline void controlesTeclado(GLFWwindow* window, float deltaTime);
inline void actualizarModoPluton(GLFWwindow* window, float deltaTime, const std::vector<Cuerpo>& cuerpos);
inline float factorVisible(int indice);
inline void actualizarTitulo(GLFWwindow* window, float deltaTime, const std::vector<Cuerpo>& cuerpos);

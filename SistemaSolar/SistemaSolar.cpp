#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>

#include "src/Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "src/Contratos.h"
#include "src/Cuerpo_Sol.h"
#include "src/Cuerpo_Mercurio.h"
#include "src/Cuerpo_Venus.h"
#include "src/Cuerpo_Tierra.h"
#include "src/Cuerpo_Luna.h"
#include "src/Cuerpo_Marte.h"
#include "src/Cuerpo_Jupiter.h"
#include "src/Cuerpo_Saturno.h"
#include "src/Cuerpo_Urano.h"
#include "src/Cuerpo_Neptuno.h"
#include "src/Cuerpo_Pluton.h"
#include "src/Sistema.h"
#include "src/Esfera.h"
#include "src/Estrellas.h"
#include "src/Texturas.h"
#include "src/Movimiento.h"
#include "src/Camara.h"
#include "src/Orbitas.h"
#include "src/Anillos.h"
#include "src/Controles.h"
#include "src/ModoPluton.h"
#include "src/Titulo.h"

float aspecto = 1200.0f / 800.0f;
float deltaTime = 0.0f;
float lastFrame = 0.0f;


void responsive(GLFWwindow* window, int width, int height);
void userInput(GLFWwindow* window);
void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos);
void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset);

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(1200, 800, "Sistema Solar", NULL, NULL);

	if (!window)
	{
		std::cout << "Error en la inicializacion de la ventana\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, responsive);
	glfwSetCursorPosCallback(window, mouse_cursor_position);
	glfwSetScrollCallback(window, mouse_scroll_position);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error al iniciar GLEW\n";
		glfwTerminate();
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	std::vector<Cuerpo> cuerpos = crearSistema();
	cargarTexturasDelSistema(cuerpos);

	ObjetoGL esfera = subirMalla(generarEsfera(1.0f, 64, 32), GL_TRIANGLES);
	iniciarEstrellas();
	iniciarOrbitas(cuerpos);
	iniciarAnillos();

	Shader myShader("res/Shader/vertexShader.glsl", "res/Shader/fragmentShader.glsl");
	myShader.use();
	myShader.setInt("textura", 0);
	myShader.setVec3("luzPos", glm::vec3(0.0f));
	myShader.setFloat("brillo", 1.0f);

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		userInput(window);
		controlesTeclado(window, deltaTime);
		camaraTeclado(window, deltaTime, cuerpos);
		actualizarModoPluton(window, deltaTime, cuerpos);

		if (!estado().pausa)
			estado().tiempo += deltaTime * estado().escalaTiempo;
		float tiempo = estado().tiempo;

		int seguido = camaraSeleccion();
		glm::vec3 objetivo(0.0f);
		if (seguido >= 0)
			objetivo = posicionCuerpo(cuerpos, seguido, tiempo);

		glClearColor(0.0f, 0.0f, 0.015f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		myShader.use();
		myShader.setMat4("projection", camaraProyeccion(aspecto));
		myShader.setMat4("view", camaraVista(objetivo, deltaTime));

		dibujarEstrellas(myShader);

		if (estado().mostrarOrbitas)
			dibujarOrbitas(myShader, cuerpos, tiempo);

		for (int i = 0; i < (int)cuerpos.size(); i++)
		{
			float escala = factorVisible(i);
			if (escala < 0.01f)
				continue;
			glm::mat4 model = glm::scale(matrizModelo(cuerpos, i, tiempo), glm::vec3(escala));

			myShader.setInt("modo", MODO_TEXTURA);
			myShader.setInt("emisivo", cuerpos[i].emisivo ? 1 : 0);
			myShader.setMat4("model", model);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, cuerpos[i].textura);
			dibujarObjeto(esfera);

			if (i == SATURNO)
				dibujarAnillos(myShader, model);
		}

		actualizarTitulo(window, deltaTime, cuerpos);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void responsive(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	if (height > 0)
		aspecto = (float)width / (float)height;
}

void userInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos)
{
	camaraMouse(window, xpos, ypos);
}

void mouse_scroll_position(GLFWwindow* window, double xoffset, double yoffset)
{
	camaraScroll(yoffset);
}
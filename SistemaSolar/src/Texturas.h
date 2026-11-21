#pragma once
#include <iostream>
#include "stb_image/stb_image.h"
#include "Contratos.h"

inline unsigned int cargarTextura(const char* ruta)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(ruta, &width, &height, &nrChannels, 0);

    if (data)
    {
        GLenum format = GL_RGB;
        if (nrChannels == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    }
    else
    {
        std::cout << "Error al cargar la textura: " << ruta << "\n";
    }

    stbi_image_free(data);
    return textureID;
}

inline void cargarTexturasDelSistema(std::vector<Cuerpo>& cuerpos)
{
    for (Cuerpo& c : cuerpos)
        c.textura = cargarTextura(c.rutaTextura.c_str());
}

#include "TextureHelper.h"
#include "GlHelper.h"
#include "main.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

unsigned int LoadTexture(const char* fileName)
{
    int width, height, nrChannels;
    unsigned char* texData = stbi_load(fileName,
        &width, &height, &nrChannels, 0);

    if (texData == NULL)
    {
        stbi_image_free(texData);
        std::cout <<
            "cannot open this file : [" << fileName << "]"
            << std::endl;

        return 0;
    }

    unsigned int tex, format;
    if (nrChannels == 4)
    {
        format = GL_RGBA;
    }
    else
    {
        format = GL_RGB;
    }

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
        GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, format,
        width, height, 0, format, GL_UNSIGNED_BYTE, texData);

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(texData);

    return tex;
}

void UnloadTexture(unsigned int texture)
{
    glDeleteTextures(1, &texture);
}

void SetTexture(unsigned int texture)
{
    if (texture == 0)
    {
        glUniform1i(glGetUniformLocation(
            GetGlHelperPtr()->GetShaderID("default"), 
            "uTextureEnable"), 0);
    }
    else
    {
        glUniform1i(glGetUniformLocation(
            GetGlHelperPtr()->GetShaderID("default"),
            "uTextureEnable"), 1);
        glBindTexture(GL_TEXTURE_2D, texture);
    }
}

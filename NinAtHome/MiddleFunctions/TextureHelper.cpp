#include "TextureHelper.h"
#include "GlHelper.h"
#include "main.h"
#include <iostream>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void SplitByRomSymbol(const std::string& s, 
    std::vector<std::string>& v, const std::string& c)
{
    v.clear();
    std::string::size_type pos1 = 0, pos2 = s.find(c);
    while (std::string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2 - pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if (pos1 != s.length())
        v.push_back(s.substr(pos1));
}

unsigned int LoadTexture(std::string fileName)
{
    {
        std::vector<std::string> v;
        SplitByRomSymbol(fileName, v, ":/");
        fileName = v[0] + "\\" + v[1];
    }

    int width, height, nrChannels;
    unsigned char* texData = stbi_load(fileName.c_str(),
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

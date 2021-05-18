#include "GlHelper.h"
#include <iostream>
#include <TP\glm\glm.hpp>
#include <TP\glm\ext\matrix_clip_space.hpp>
#include <TP\glm\gtc\type_ptr.hpp>

const char* g_DefaultVertShader =
"#version 330 core\n"
"precision highp float;\n"

"uniform mat4 uProjection;\n"
"uniform mat4 uRotateZ;\n"

"layout( location = 0 ) in vec3 inPosition;\n"
"layout( location = 1 ) in vec4 inColor;\n"
"layout( location = 2 ) in vec2 inTexCoord;\n"

"out vec4 vColor;\n"
"out vec2 vTexCoord;\n"

"void main() {\n"
"    vColor = inColor;\n"
"    vTexCoord = inTexCoord;\n"
"    gl_Position = vec4(inPosition, 1.0) * uRotateZ * uProjection;\n"
"}\n";

const char* g_DefaultFragShader =
"#version 330 core\n"
"precision highp float;\n"

"uniform sampler2D uSampler;\n"
"uniform bool uTextureEnable;\n"

"in vec4 vColor;\n"
"in vec2 vTexCoord;\n"

"out vec4 outColor;\n"

"void main() {\n"
"    if(uTextureEnable)\n"
"		outColor = vColor * texture(uSampler, vTexCoord);\n"
"    else\n"
"		outColor = vColor;\n"
"}\n";

GlHelper::GlHelper() {}

GlHelper::~GlHelper() {}

bool GlHelper::StartUp()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);

    if (CompileDefaultShaders())
    {
        glUseProgram(mShaders["default"]);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);

        glm::fmat4x4 projection;
        projection = glm::ortho(0.f, 1920.f, 0.f, 1080.f);

        glUniformMatrix4fv(
            glGetUniformLocation(
                mShaders["default"],
                "uProjection"),
            1, GL_TRUE, (float*)glm::value_ptr(projection));
        glUniform1i(glGetUniformLocation(
            mShaders["default"], "uTextureEnable"), 0);

        return true;
    }

    return false;
}

bool GlHelper::CompileDefaultShaders()
{
    GLuint vertShaderId;
    GLuint fragShaderId;
    GLuint shaderProgramId;
    GLint result;

    vertShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShaderId, 1, &g_DefaultVertShader, 0);
    glCompileShader(vertShaderId);
    glGetShaderiv(vertShaderId, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        std::cout <<
            "failed to compile default vert shader"
            << std::endl;
        return false;
    }

    fragShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShaderId, 1, &g_DefaultFragShader, 0);
    glCompileShader(fragShaderId);
    glGetShaderiv(fragShaderId, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        std::cout <<
            "failed to compile default vert shader"
            << std::endl;
        return false;
    }

    shaderProgramId = glCreateProgram();
    glAttachShader(shaderProgramId, vertShaderId);
    glAttachShader(shaderProgramId, fragShaderId);
    glLinkProgram(shaderProgramId);

    mVertShaders.insert(std::make_pair("default", vertShaderId));
    mFragShaders.insert(std::make_pair("default", fragShaderId));
    mShaders.insert(std::make_pair("default", shaderProgramId));

    return true;
}

void GlHelper::CleanAndStop()
{

}

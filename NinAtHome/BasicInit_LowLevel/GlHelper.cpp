#include "GlHelper.h"
#include <iostream>
#include <TP\glm\glm.hpp>
#include <TP\glm\ext\matrix_clip_space.hpp>
#include <TP\glm\gtc\type_ptr.hpp>
#include "NinLog.h"

const char* g_DefaultVertShader =
"#version 330 core\n"
"precision highp float;\n"

"uniform mat4 uProjection;\n"

"layout( location = 0 ) in vec3 inPosition;\n"
"layout( location = 1 ) in vec4 inColor;\n"
"layout( location = 2 ) in vec2 inTexCoord;\n"

"out vec4 vColor;\n"
"out vec2 vTexCoord;\n"

"void main() {\n"
"    vColor = inColor;\n"
"    vTexCoord = inTexCoord;\n"
"    gl_Position = vec4(inPosition, 1.0) * uProjection;\n"
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
        projection = glm::ortho(-960.f, 960.f, 540.f, -540.f);

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
        NN_LOG(LOG_ERROR, 
            "failed to compile default vert shader\n");
        return false;
    }

    fragShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShaderId, 1, &g_DefaultFragShader, 0);
    glCompileShader(fragShaderId);
    glGetShaderiv(fragShaderId, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        NN_LOG(LOG_ERROR,
            "failed to compile default frag shader\n");
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

void GlHelper::MoveDataToBuffer(const VERTEX* origin,
    const unsigned int size, float* buffer)
{
    for (unsigned int i = 0; i < size; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            buffer[9 * i + j] =
                ((float*)value_ptr(origin[i].Position))[j];
        }
        for (int j = 0; j < 4; j++)
        {
            buffer[9 * i + 3 + j] =
                ((float*)value_ptr(origin[i].Color))[j];
        }
        for (int j = 0; j < 2; j++)
        {
            buffer[9 * i + 7 + j] =
                ((float*)value_ptr(origin[i].TexCoord))[j];
        }
    }
}

void GlHelper::BindVAOWithVBO(unsigned int* vao,
    unsigned int* vbo, float* buffer, int bufferSize)
{
    glGenVertexArrays(1, vao);
    glGenBuffers(1, vbo);
    glBindVertexArray(*vao);
    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    glBufferData(GL_ARRAY_BUFFER,
        bufferSize * sizeof(*buffer), buffer,
        GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
        9 * sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE,
        9 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
        9 * sizeof(float), (GLvoid*)(7 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    mVAOs.push_back(*vao);
    mVBOs.push_back(*vbo);
}

GLuint GlHelper::GetShaderID(std::string name)
{
    return mShaders[name];
}

void GlHelper::ClearVaoVbo()
{
    while (!mVAOs.empty())
    {
        GLuint vaoID = mVAOs.back();
        glDeleteVertexArrays(1, &vaoID);
        mVAOs.pop_back();
    }

    while (!mVBOs.empty())
    {
        GLuint vboID = mVBOs.back();
        glDeleteBuffers(1, &vboID);
        mVBOs.pop_back();
    }
}

void MatrixStore(Float4x4* ptr, Matrix4x4f mat)
{
    *ptr = glm::value_ptr(mat);
}

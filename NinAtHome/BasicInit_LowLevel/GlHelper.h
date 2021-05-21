#pragma once

#include <map>
#include <vector>
#include <string>
#include <TP\glad\glad.h>
#include <TP\glm\glm.hpp>
#include <TP\glm\gtc\type_ptr.hpp>

typedef glm::fvec3 Float3;
typedef glm::fvec4 Float4;
typedef glm::fvec2 Float2;
typedef glm::fmat4x4 Matrix4x4f;
typedef float* Float4x4;

void MatrixStore(Float4x4* ptr, Matrix4x4f mat);

#define MakeFloat2 glm::fvec2
#define MakeFloat3 glm::fvec3
#define MakeFloat4 glm::fvec4

typedef struct _VERTEX
{
    Float3 Position;
    Float4 Color;
    Float2 TexCoord;
}VERTEX;

class GlHelper
{
public:
    GlHelper();
    ~GlHelper();
    bool StartUp();
    void CleanAndStop();
    void MoveDataToBuffer(const VERTEX* origin,
        const unsigned int size, float* buffer);
    void BindVAOWithVBO(unsigned int* vao, unsigned int* vbo,
        float* buffer, int bufferSize);
    GLuint GetShaderID(std::string name);
    void ClearVaoVbo();

private:
    bool CompileDefaultShaders();

    std::map<std::string, GLuint> mShaders;
    std::map<std::string, GLuint> mVertShaders;
    std::map<std::string, GLuint> mFragShaders;
    std::vector<GLuint> mVAOs;
    std::vector<GLuint> mVBOs;
};


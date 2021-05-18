#pragma once

#include <map>
#include <string>
#include <TP\glad\glad.h>

class GlHelper
{
public:
    GlHelper();
    ~GlHelper();
    bool StartUp();
    void CleanAndStop();

private:
    bool CompileDefaultShaders();

    std::map<std::string, GLuint> mShaders;
    std::map<std::string, GLuint> mVertShaders;
    std::map<std::string, GLuint> mFragShaders;
};


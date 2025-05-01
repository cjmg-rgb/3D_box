#ifndef SHADER_H
#define SHADER_H

#include "iostream"
#include "fstream"
#include "sstream"
#include "string"

#include "glad/glad.h"

class Shader {
    unsigned int ID;
    void compileShader(GLenum shaderType, unsigned int* shader, std::string& codeSource);
    void linkProgram(unsigned int* vertex, unsigned int* fragment);
    std::string shaderString(const char* filePath);
    public:
        Shader(const char* vFile, const char* fFile);
        void use();
};

#endif
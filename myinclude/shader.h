#ifndef SHADER_H
#define SHADER_H

#include "iostream"
#include "fstream"
#include "sstream"
#include "string"

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Shader {
    unsigned int ID;
    void compileShader(GLenum shaderType, unsigned int* shader, std::string& codeSource);
    void linkProgram(unsigned int* vertex, unsigned int* fragment);
    std::string shaderString(const char* filePath);
    public:
        Shader(const char* vFile, const char* fFile);
        void use();

        void setInt(const char* name, int value);
        void setMat4fv(const char* name, glm::mat4 value);
};

#endif
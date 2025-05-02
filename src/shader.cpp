#include "shader.h"

Shader::Shader(const char* vFile, const char* fFile) {
    std::string vertexCode = shaderString(vFile);
    std::string fragmentCode = shaderString(fFile);
    
    unsigned int vertex, fragment;
    compileShader(GL_VERTEX_SHADER, &vertex, vertexCode);
    compileShader(GL_FRAGMENT_SHADER, &fragment, fragmentCode);
    linkProgram(&vertex, &fragment);
    

};

std::string Shader::shaderString(const char* filePath) {
    std::string code;
    
    std::ifstream file;
    std::stringstream fileStream;
    fileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {

        file.open(filePath);
        fileStream << file.rdbuf();
        file.close();

        code = fileStream.str();
    } catch(std::ifstream::failure e) {
        std::cout << "Failed to open file " << filePath << "\n";
    };

    return code;
};

void Shader::compileShader(GLenum shaderType, unsigned int* shader, std::string& codeSource) {
    const char* shaderSource = codeSource.c_str();
    int success;
    char infoLog[512];
    
    *shader = glCreateShader(shaderType);
    glShaderSource(*shader, 1, &shaderSource, NULL);
    glCompileShader(*shader);
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
    if(success == GL_FALSE) {
        glGetShaderInfoLog(*shader, 512, NULL, infoLog);
        std::cout << "Failed to compile shader " << infoLog << "\n";
    };

}

void Shader::linkProgram(unsigned int* vertex, unsigned int* fragment) {
    ID = glCreateProgram();
    glAttachShader(ID, *vertex);
    glAttachShader(ID, *fragment);
    glLinkProgram(ID);

    glDeleteShader(*vertex);
    glDeleteShader(*fragment);
}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::setInt(const char* name, int value) {
    glUniform1i(glGetUniformLocation(ID, name), value);
};

void Shader::setMat4fv(const char* name, glm::mat4 value) {
    glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(value));
};

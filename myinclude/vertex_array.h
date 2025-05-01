#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "glad/glad.h"

class VertexArray {

    unsigned int ID;
    unsigned int vbo;
    unsigned int ebo;

    public:
        VertexArray();
        ~VertexArray();
        void createVertexBuffer(GLsizei size, const void* data, GLenum usage);
        void createIndexBuffer(GLsizei size, const void* data, GLenum usage);
        void enableVertixAttrib(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
        void use();

};


#endif
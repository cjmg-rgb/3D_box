#include "vertex_array.h"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &ID);
    glBindVertexArray(ID);
};
VertexArray::~VertexArray() {
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &ID);
}

void VertexArray::createVertexBuffer(GLsizei size, const void* data, GLenum usage) {
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexArray::createIndexBuffer(GLsizei size, const void* data, GLenum usage) {
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexArray::enableVertixAttrib(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) {
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    glEnableVertexAttribArray(index);
}

void VertexArray::use() {
    glBindVertexArray(ID);
}
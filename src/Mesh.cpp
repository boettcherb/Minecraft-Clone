#include "Mesh.h"
#include "ShaderProgram.h"

#include <glad/glad.h>

Mesh::Mesh(const void* data, unsigned int size) : m_vertexCount{ size / sizeof(unsigned int) } {
    // create and bind vertex array
    glGenVertexArrays(1, &m_vertexArrayID);
    glBindVertexArray(m_vertexArrayID);

    // create and bind vertex buffer
    glGenBuffers(1, &m_vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);

    // set up memory location for vertex data (don't pass in any data yet)
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    // tell openGL the layout of our vertex data
    glEnableVertexAttribArray(0);
    glVertexAttribIPointer(0, 1, GL_UNSIGNED_INT, sizeof(unsigned int), 0);
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &m_vertexArrayID);
    glDeleteBuffers(1, &m_vertexBufferID);
}

void Mesh::render(const ShaderProgram* shader) const {
    shader->bind();
    glBindVertexArray(m_vertexArrayID);
    glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);
}

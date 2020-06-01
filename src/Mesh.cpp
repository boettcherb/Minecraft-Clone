#include "Mesh.h"
#include "ShaderProgram.h"

#include <glad/glad.h>

#include <iostream>

Mesh::Mesh(unsigned int vbSize) : m_shader{ nullptr }, m_vertexCount{ 0 } {
    glGenVertexArrays(1, &m_vertexArrayID);
    glBindVertexArray(m_vertexArrayID);
    m_vertexBufferID = setVertexBuffer(vbSize);
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &m_vertexArrayID);
    glDeleteBuffers(1, &m_vertexBufferID);
}

unsigned int Mesh::setVertexBuffer(unsigned int size) const {
    // create and bind vertex buffer
    unsigned int vertexBufferID;
    glGenBuffers(1, &vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    
    // set up memory location for vertex data (don't pass in any data yet)
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);

    // tell openGL the layout of our vertex data.
    glEnableVertexAttribArray(0);
    glVertexAttribIPointer(0, 1, GL_UNSIGNED_INT, sizeof(unsigned int), 0);
    
    return vertexBufferID;
}

void Mesh::setVertexData(const void* data, unsigned int size) {
    glBindVertexArray(m_vertexArrayID);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    m_vertexCount = size / sizeof(unsigned int);
}

void Mesh::setShader(const ShaderProgram* shader) {
    m_shader = shader;
}

void Mesh::render(const ShaderProgram* shader) const {
    // if a shader is passed in as a parameter, use it over any shader that
    // was set by setShader()
    if (shader == nullptr) {
        if (m_shader == nullptr) {
            std::cerr << "Error: No shader program specified\n";
            return;
        }
        shader = m_shader;
    }
    shader->bind();
    glBindVertexArray(m_vertexArrayID);
    glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);
}

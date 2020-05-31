#include "Mesh.h"
#include "ShaderProgram.h"

#include <glad/glad.h>

#include <iostream>
#include <numeric>
#include <vector>

Mesh::Mesh(unsigned int vbSize, unsigned int ibCount, const std::vector<unsigned int>& layout)
    : m_shader{ nullptr } {
    glGenVertexArrays(1, &m_vertexArrayID);
    glBindVertexArray(m_vertexArrayID);

    m_vertexBufferID = setVertexBuffer(vbSize, layout);
    m_indexBufferID = setIndexBuffer(ibCount);
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &m_vertexArrayID);
    glDeleteBuffers(1, &m_indexBufferID);
    glDeleteBuffers(1, &m_vertexBufferID);
}

unsigned int Mesh::setVertexBuffer(unsigned int size, const std::vector<unsigned int>& layout) const {
    // create and bind vertex buffer
    unsigned int vertexBufferID;
    glGenBuffers(1, &vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    
    // set up memory location for vertex data (don't pass in any data yet)
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);

    // calculate the number of bytes of each vertex
    // std::accumulate sums up the values in the vertex buffer layout
    int stride = std::accumulate(layout.begin(), layout.end(), 0) * sizeof(float);

    // tell openGL the layout of our vertex data.
    unsigned long long offset = 0;
    for (unsigned int i = 0; i < layout.size(); ++i) {
        glEnableVertexAttribArray(i);
        // offset is the number of bytes from the start of the data, but OpenGL
        // reads this information in as a const void pointer
        const void* offsetPtr = reinterpret_cast<const void*>(offset);
        glVertexAttribPointer(i, layout[i], GL_FLOAT, false, stride, offsetPtr);
        offset += layout[i] * sizeof(float);
    }
    return vertexBufferID;
}

unsigned int Mesh::setIndexBuffer(unsigned int count) const {
    // create and bind index buffer
    unsigned int indexBufferID;
    glGenBuffers(1, &indexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);

    // set up memory location for index data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), nullptr, GL_DYNAMIC_DRAW);
    
    return indexBufferID;
}

void Mesh::setVertexData(const void* data, unsigned int size) {
    glBindVertexArray(m_vertexArrayID);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

void Mesh::setIndexData(const void* data, unsigned int count) {
    glBindVertexArray(m_vertexArrayID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, count * sizeof(unsigned int), data);
    m_indexBufferCount = count;
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
    glDrawElements(GL_TRIANGLES, m_indexBufferCount, GL_UNSIGNED_INT, 0);
}

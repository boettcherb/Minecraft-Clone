#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

#include "ShaderProgram.h"

#include <glm/glm.hpp>

class Mesh {
    unsigned int m_vertexArrayID;
    unsigned int m_vertexBufferID;
    unsigned int m_vertexCount;

public:
    Mesh(unsigned int vbSize);
    ~Mesh();

    void setVertexData(const void* data, unsigned int size);
    void render(const ShaderProgram* shader) const;

private:
    unsigned int setVertexBuffer(unsigned int size) const;
};

#endif

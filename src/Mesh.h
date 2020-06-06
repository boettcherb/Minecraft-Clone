#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

#include "ShaderProgram.h"

class Mesh {
    unsigned int m_vertexArrayID;
    unsigned int m_vertexBufferID;
    unsigned int m_vertexCount;

public:
    Mesh(const void* data, unsigned int vbSize);
    ~Mesh();

    void render(const ShaderProgram* shader) const;
};

#endif

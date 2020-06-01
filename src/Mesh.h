#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

#include "ShaderProgram.h"

class Mesh {
	unsigned int m_vertexArrayID;
	unsigned int m_vertexBufferID;
	unsigned int m_vertexCount;
	ShaderProgram const* m_shader;

public:
	Mesh(unsigned int vbSize);
	~Mesh();

	void setVertexData(const void* data, unsigned int size);
	void setShader(const ShaderProgram* shader);
	void render(const ShaderProgram* shader = nullptr) const;

private:
	unsigned int setVertexBuffer(unsigned int size) const;
};

#endif

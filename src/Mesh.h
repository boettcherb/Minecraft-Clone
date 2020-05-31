#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

#include "ShaderProgram.h"

#include <vector>

class Mesh {
	unsigned int m_vertexArrayID;
	unsigned int m_vertexBufferID;
	unsigned int m_indexBufferID;
	unsigned int m_indexBufferCount;
	ShaderProgram const* m_shader;

public:
	Mesh(unsigned int vbSize, unsigned int ibCount, const std::vector<unsigned int>& layout);
	~Mesh();

	void setVertexData(const void* data, unsigned int size);
	void setIndexData(const void* data, unsigned int count);
	void setShader(const ShaderProgram* shader);
	void render(const ShaderProgram* shader = nullptr) const;

private:
	unsigned int setVertexBuffer(unsigned int size, const std::vector<unsigned int>& layout) const;
	unsigned int setIndexBuffer(unsigned int count) const;
};

#endif

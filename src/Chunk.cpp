#include "Chunk.h"
#include "BlockInfo.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Mesh.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <new>

Chunk::Chunk(float x, float y, float z, ShaderProgram* shader) : m_posX{ x }, m_posY{ y }, 
m_posZ{ z }, m_shader{ shader }, m_updated{ true }, m_blocks{ Block::BlockType::AIR } {
	m_mesh = new Mesh(BLOCKS_PER_CHUNK * Block::VERTICES_PER_BLOCK * sizeof(unsigned int));
	for (int i = 0; i < CHUNK_LENGTH; ++i) {
		for (int j = 0; j < CHUNK_HEIGHT; ++j) {
			for (int k = 0; k < CHUNK_WIDTH; ++k) {
				m_blocks[i][j][k] = Block::BlockType::GRASS;
			}
		}
	}
}

Chunk::~Chunk() {
	delete m_mesh;
}

unsigned int Chunk::getVertexData(unsigned int* data) {
	unsigned int* start = data;
	for (int x = 0; x < CHUNK_LENGTH; ++x) {
		for (int y = 0; y < CHUNK_HEIGHT; ++y) {
			for (int z = 0; z < CHUNK_WIDTH; ++z) {
				// skip if this block is air
				if (m_blocks[x][y][z] == Block::BlockType::AIR) {
					continue;
				}
				// check each of the six sides to see if this block is adjacent to air
				// only draw if this block is next to air or the edge of the chunk
				if (x == CHUNK_LENGTH - 1 || m_blocks[x + 1][y][z] == Block::BlockType::AIR) {
					setBlockFaceData(data, x, y, z, Block::BlockFace::PLUS_X);
					data += Block::UINTS_PER_FACE;
				}
				if (x == 0 || m_blocks[x - 1][y][z] == Block::BlockType::AIR) {
					setBlockFaceData(data, x, y, z, Block::BlockFace::MINUS_X);
					data += Block::UINTS_PER_FACE;
				}
				if (y == CHUNK_HEIGHT - 1 || m_blocks[x][y + 1][z] == Block::BlockType::AIR) {
					setBlockFaceData(data, x, y, z, Block::BlockFace::PLUS_Y);
					data += Block::UINTS_PER_FACE;
				}
				if (y == 0 || m_blocks[x][y - 1][z] == Block::BlockType::AIR) {
					setBlockFaceData(data, x, y, z, Block::BlockFace::MINUS_Y);
					data += Block::UINTS_PER_FACE;
				}
				if (z == CHUNK_WIDTH - 1 || m_blocks[x][y][z + 1] == Block::BlockType::AIR) {
					setBlockFaceData(data, x, y, z, Block::BlockFace::PLUS_Z);
					data += Block::UINTS_PER_FACE;
				}
				if (z == 0 || m_blocks[x][y][z - 1] == Block::BlockType::AIR) {
					setBlockFaceData(data, x, y, z, Block::BlockFace::MINUS_Z);
					data += Block::UINTS_PER_FACE;
				}
			}
		}
	}
	// all updates to vertex data were just processed
	m_updated = false;

	// return the number of bytes that were initialized
	return static_cast<unsigned int>(data - start) / Block::UINTS_PER_FACE * Block::BYTES_PER_FACE;
}

inline void Chunk::setBlockFaceData(unsigned int* data, int x, int y, int z, Block::BlockFace face) const {
	const unsigned int* blockData = Block::getData(m_blocks[x][y][z], face);
	for (unsigned int vertex = 0; vertex < Block::VERTICES_PER_FACE; ++vertex) {
		// x pos takes bits 20-24, y takes bits 15-19, z takes bits 10-14 (from the right)
		// add the relative x, y, and z positions of the block in the chunk
		data[vertex] = blockData[vertex] + (x << 20) + (y << 15) + (z << 10);
	}
}

void Chunk::render(const Camera* camera, float scrRatio) {
	if (m_updated) {
		unsigned int* vbData = new unsigned int[BLOCKS_PER_CHUNK * Block::VERTICES_PER_BLOCK];
		unsigned int size = getVertexData(vbData);
		m_mesh->setVertexData(vbData, size);
		delete[] vbData;
	}
	float worldX = m_posX * CHUNK_LENGTH;
	float worldY = m_posY * CHUNK_HEIGHT;
	float worldZ = m_posZ * CHUNK_WIDTH;
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(worldX, worldY, worldZ));
	m_shader->addUniformMat4f("u_model", model);
	m_shader->addUniformMat4f("u_view", camera->getViewMatrix());
	glm::mat4 projection = glm::perspective(glm::radians(camera->getZoom()), scrRatio, 0.1f, 100.0f);
	m_shader->addUniformMat4f("u_projection", projection);
	m_mesh->render(m_shader);
}

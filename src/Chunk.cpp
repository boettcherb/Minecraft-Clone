#include "Chunk.h"
#include "BlockInfo.h"

#include <iostream>

Chunk::Chunk(int x, int y, int z) : m_posX{ x }, m_posY{ y }, m_posZ{ z }, m_numFacesToDraw{ 0 }, m_updated{ true } {
	for (int i = 0; i < CHUNK_LENGTH; ++i) {
		for (int j = 0; j < CHUNK_HEIGHT; ++j) {
			for (int k = 0; k < CHUNK_WIDTH; ++k) {
				m_blocks[i][j][k] = Block::GRASS;
			}
		}
	}
}

unsigned int Chunk::getVertexData(unsigned int* data) {
	unsigned int* start = data;
	for (int x = 0; x < CHUNK_LENGTH; ++x) {
		for (int y = 0; y < CHUNK_HEIGHT; ++y) {
			for (int z = 0; z < CHUNK_WIDTH; ++z) {
				// skip if this block is air
				if (m_blocks[x][y][z] == Block::AIR) {
					continue;
				}
				// check each of the six sides to see if this block is adjacent to air
				// only draw if this block is next to air or the edge of the chunk
				if (x == CHUNK_LENGTH - 1 || m_blocks[x + 1][y][z] == Block::AIR) {
					setBlockFaceData(data, x, y, z, Block::PLUS_X);
					data += Block::UINTS_PER_FACE;
				}
				if (x == 0 || m_blocks[x - 1][y][z] == Block::AIR) {
					setBlockFaceData(data, x, y, z, Block::MINUS_X);
					data += Block::UINTS_PER_FACE;
				}
				if (y == CHUNK_HEIGHT - 1 || m_blocks[x][y + 1][z] == Block::AIR) {
					setBlockFaceData(data, x, y, z, Block::PLUS_Y);
					data += Block::UINTS_PER_FACE;
				}
				if (y == 0 || m_blocks[x][y - 1][z] == Block::AIR) {
					setBlockFaceData(data, x, y, z, Block::MINUS_Y);
					data += Block::UINTS_PER_FACE;
				}
				if (z == CHUNK_WIDTH - 1 || m_blocks[x][y][z + 1] == Block::AIR) {
					setBlockFaceData(data, x, y, z, Block::PLUS_Z);
					data += Block::UINTS_PER_FACE;
				}
				if (z == 0 || m_blocks[x][y][z - 1] == Block::AIR) {
					setBlockFaceData(data, x, y, z, Block::MINUS_Z);
					data += Block::UINTS_PER_FACE;
				}
			}
		}
	}
	// all updates to vertex data were just processed
	m_updated = false;

	// calculate the number of faces drawn based on the initial start 
	// of the array and the new start of the arary
	m_numFacesToDraw = static_cast<unsigned int>(data - start) / Block::UINTS_PER_FACE;

	// return the number of bytes that were initialized
	return m_numFacesToDraw * Block::BYTES_PER_FACE;
}

inline void Chunk::setBlockFaceData(unsigned int* data, int x, int y, int z, Block::BlockFace face) const {
	const unsigned int* blockData = Block::getData(m_blocks[x][y][z], face);
	for (unsigned int vertex = 0; vertex < Block::VERTICES_PER_FACE; ++vertex) {
		int index = vertex * Block::UINTS_PER_VERTEX;
		data[index] = blockData[index] + x + m_posX;
		data[index + 1] = blockData[index + 1] + y + m_posY;
		data[index + 2] = blockData[index + 2] + z + m_posZ;
		data[index + 3] = blockData[index + 3];
		data[index + 4] = blockData[index + 4];
	}
}

unsigned int Chunk::getIndexData(unsigned int* data) {
	// set the first six indices from Block::FACE_INDICES
	for (unsigned int i = 0; i < Block::INDICES_PER_FACE; ++i) {
		data[i] = Block::FACE_INDICES[i];
	}

	// then use the first six to set all the rest
	// m_numFacesToDraw must be set from a previous call to getVertexData
	unsigned int numIndices = m_numFacesToDraw * Block::INDICES_PER_FACE;
	for (unsigned int i = Block::INDICES_PER_FACE; i < numIndices; ++i) {
		data[i] = data[i - Block::INDICES_PER_FACE] + Block::VERTICES_PER_FACE;
	}
	return numIndices;
}

bool Chunk::updated() const {
	return m_updated;
}

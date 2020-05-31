#ifndef CHUNK_H_INCLUDED
#define CHUNK_H_INCLUDED

#include "BlockInfo.h"

inline constexpr int CHUNK_LENGTH = 8; // x
inline constexpr int CHUNK_HEIGHT = 8; // y
inline constexpr int CHUNK_WIDTH = 8;  // z
inline const unsigned int BLOCKS_PER_CHUNK = CHUNK_LENGTH * CHUNK_HEIGHT * CHUNK_WIDTH;

class Chunk {

	const int m_posX, m_posY, m_posZ;
	Block::BlockType m_blocks[CHUNK_LENGTH][CHUNK_WIDTH][CHUNK_HEIGHT];
	unsigned int m_numFacesToDraw;

public:
	Chunk(int x, int y, int z);

	unsigned int getVertexData(float* data);
	unsigned int getIndexData(unsigned int* data);

private:
	inline void setBlockFaceData(float* data, int x, int y, int z, Block::BlockFace face) const;
};

#endif
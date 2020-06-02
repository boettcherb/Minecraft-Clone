#ifndef CHUNK_H_INCLUDED
#define CHUNK_H_INCLUDED

#include "BlockInfo.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Camera.h"

inline constexpr int CHUNK_LENGTH = 16; // x
inline constexpr int CHUNK_HEIGHT = 16; // y
inline constexpr int CHUNK_WIDTH =  16; // z
inline const unsigned int BLOCKS_PER_CHUNK = CHUNK_LENGTH * CHUNK_HEIGHT * CHUNK_WIDTH;

class Chunk {

    const float m_posX, m_posY, m_posZ;
    Block::BlockType m_blocks[CHUNK_LENGTH][CHUNK_WIDTH][CHUNK_HEIGHT];
    Mesh* m_mesh;
    ShaderProgram* m_shader;
    bool m_updated;

public:
    Chunk(float x, float y, float z, ShaderProgram* shader);
    ~Chunk();

    unsigned int getVertexData(unsigned int* data);
    void render(const Camera* camera, float scrRatio);

private:
    inline void setBlockFaceData(unsigned int* data, int x, int y, int z, Block::BlockFace face) const;
};

#endif

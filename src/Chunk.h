#ifndef CHUNK_H_INCLUDED
#define CHUNK_H_INCLUDED

#include "BlockInfo.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Camera.h"

inline constexpr unsigned int CHUNK_LENGTH = 16;  // x
inline constexpr unsigned int CHUNK_HEIGHT = 256; // y
inline constexpr unsigned int CHUNK_WIDTH  = 16;  // z
inline constexpr unsigned int BLOCKS_PER_CHUNK = CHUNK_LENGTH * CHUNK_HEIGHT * CHUNK_WIDTH;
inline constexpr unsigned int MAX_VERTICES_PER_CHUNK = BLOCKS_PER_CHUNK * Block::VERTICES_PER_BLOCK;

class Chunk {

    struct BlockArray {
        Block::BlockType m_blockArray[CHUNK_LENGTH][CHUNK_HEIGHT][CHUNK_WIDTH];
        Block::BlockType get(int x, int y, int z) const;
        void put(int x, int y, int z, Block::BlockType type);
    };

    const float m_posX, m_posZ;
    BlockArray* m_blocks;
    Mesh* m_mesh;
    ShaderProgram* m_shader;
    bool m_updated;

public:
    Chunk(float x, float z, ShaderProgram* shader);
    ~Chunk();

    unsigned int getVertexData(unsigned int* data);
    void render(const Camera* camera, float scrRatio);

private:
    inline void setBlockFaceData(unsigned int* data, int x, int y, int z, Block::BlockFace face) const;
};

#endif

#ifndef CHUNK_H_INCLUDED
#define CHUNK_H_INCLUDED

#include "BlockInfo.h"
#include "ShaderProgram.h"
#include "Mesh.h"

inline constexpr int CHUNK_LENGTH = 16;  // x
inline constexpr int CHUNK_HEIGHT = 256; // y
inline constexpr int CHUNK_WIDTH = 16;  // z
inline constexpr int BLOCKS_PER_CHUNK = CHUNK_LENGTH * CHUNK_HEIGHT * CHUNK_WIDTH;

inline constexpr int NUM_SECTIONS = 16;
inline constexpr int SECTION_HEIGHT = 16;
inline constexpr int BLOCKS_PER_SECTION = BLOCKS_PER_CHUNK / NUM_SECTIONS;

class Chunk {

    struct Section {
        Block::BlockType m_blocks[CHUNK_LENGTH][SECTION_HEIGHT][CHUNK_WIDTH];
        Mesh m_mesh;
        void render(const ShaderProgram* shader) const;
    };

    const float m_posX, m_posZ;
    Section* m_sections[NUM_SECTIONS];
    ShaderProgram* m_shader;

public:
    Chunk(float x, float z, ShaderProgram* shader);
    ~Chunk();

    void put(int x, int y, int z, Block::BlockType block);
    Block::BlockType get(int x, int y, int z) const;
    void render(glm::mat4 viewMatrix, float zoom, float scrRatio);
    unsigned int getVertexData(unsigned int* data, int section) const;

private:
    void generateTerrain();
    inline void setBlockFaceData(unsigned int* data, int x, int y, int z, Block::BlockFace face) const;
};

#endif

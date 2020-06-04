#include "Chunk.h"
#include "BlockInfo.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Mesh.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <FastNoise/FastNoise.h>

#include <new>

Block::BlockType Chunk::BlockArray::get(int x, int y, int z) const {
    return m_blockArray[x][y][z];
}

void Chunk::BlockArray::put(int x, int y, int z, Block::BlockType type) {
    m_blockArray[x][y][z] = type;
}

Chunk::Chunk(float x, float z, ShaderProgram* shader) : m_posX{ x }, m_posZ{ z }, 
m_shader{ shader }, m_updated{ true } {
    m_mesh = new Mesh(BLOCKS_PER_CHUNK * Block::VERTICES_PER_BLOCK * sizeof(unsigned int));
    m_blocks = new BlockArray;
    FastNoise noise;
    for (int X = 0; X < CHUNK_LENGTH; ++X) {
        for (int Z = 0; Z < CHUNK_WIDTH; ++Z) {
            float noiseX = X + CHUNK_LENGTH * m_posX;
            float noiseZ = Z + CHUNK_WIDTH * m_posZ;
            int groundHeight = static_cast<int>(50.0 + (noise.GetSimplexFractal(noiseX, noiseZ) + 1.0) / 2.0 * 30.0);
            for (int Y = 0; Y <= groundHeight - 4; ++Y) {
                m_blocks->put(X, Y, Z, Block::BlockType::STONE);
            }
            m_blocks->put(X, groundHeight - 3, Z, Block::BlockType::DIRT);
            m_blocks->put(X, groundHeight - 2, Z, Block::BlockType::DIRT);
            m_blocks->put(X, groundHeight - 1, Z, Block::BlockType::DIRT);
            m_blocks->put(X, groundHeight, Z, Block::BlockType::GRASS);
            for (int Y = groundHeight + 1; Y < CHUNK_HEIGHT; ++Y) {
                m_blocks->put(X, Y, Z, Block::BlockType::AIR);
            }
        }
    }
}

Chunk::~Chunk() {
    delete m_blocks;
    delete m_mesh;
}

unsigned int Chunk::getVertexData(unsigned int* data) {
    unsigned int* start = data;
    for (int x = 0; x < CHUNK_LENGTH; ++x) {
        for (int y = 0; y < CHUNK_HEIGHT; ++y) {
            for (int z = 0; z < CHUNK_WIDTH; ++z) {
                // skip if this block is air
                if (m_blocks->get(x, y, z) == Block::BlockType::AIR) {
                    continue;
                }
                // check each of the six sides to see if this block is adjacent to a transparent block
                // only draw if this block is next to a transparent block or the edge of the chunk
                if (x == CHUNK_LENGTH - 1 || Block::isTransparent(m_blocks->get(x + 1, y, z))) {
                    setBlockFaceData(data, x, y, z, Block::BlockFace::PLUS_X);
                    data += Block::UINTS_PER_FACE;
                }
                if (x == 0 || Block::isTransparent(m_blocks->get(x - 1, y, z))) {
                    setBlockFaceData(data, x, y, z, Block::BlockFace::MINUS_X);
                    data += Block::UINTS_PER_FACE;
                }
                if (y == CHUNK_HEIGHT - 1 || Block::isTransparent(m_blocks->get(x, y + 1, z))) {
                    setBlockFaceData(data, x, y, z, Block::BlockFace::PLUS_Y);
                    data += Block::UINTS_PER_FACE;
                }
                if (y == 0 || Block::isTransparent(m_blocks->get(x, y - 1, z))) {
                    setBlockFaceData(data, x, y, z, Block::BlockFace::MINUS_Y);
                    data += Block::UINTS_PER_FACE;
                }
                if (z == CHUNK_WIDTH - 1 || Block::isTransparent(m_blocks->get(x, y, z + 1))) {
                    setBlockFaceData(data, x, y, z, Block::BlockFace::PLUS_Z);
                    data += Block::UINTS_PER_FACE;
                }
                if (z == 0 || Block::isTransparent(m_blocks->get(x, y, z - 1))) {
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
    const unsigned int* blockData = Block::getData(m_blocks->get(x, y, z), face);
    for (unsigned int vertex = 0; vertex < Block::VERTICES_PER_FACE; ++vertex) {
        // x pos takes bits 20-24, y takes bits 15-19, z takes bits 10-14 (from the right)
        // add the relative x, y, and z positions of the block in the chunk
        data[vertex] = blockData[vertex] + (x << 24) + (y << 15) + (z << 10);
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
    float worldZ = m_posZ * CHUNK_WIDTH;
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(worldX, 0.0f, worldZ));
    m_shader->addUniformMat4f("u_model", model);
    m_shader->addUniformMat4f("u_view", camera->getViewMatrix());
    glm::mat4 projection = glm::perspective(glm::radians(camera->getZoom()), scrRatio, 0.1f, 300.0f);
    m_shader->addUniformMat4f("u_projection", projection);
    m_mesh->render(m_shader);
}

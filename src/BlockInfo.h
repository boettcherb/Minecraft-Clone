#ifndef BLOCK_TYPE_H_INCLUDED
#define BLOCK_TYPE_H_INCLUDED

#include <cinttypes>
#include <vector>

namespace Block {

    inline constexpr unsigned int FACES_PER_BLOCK = 6;
    inline constexpr unsigned int VERTICES_PER_FACE = 4;
    inline constexpr unsigned int VERTICES_PER_BLOCK = VERTICES_PER_FACE * FACES_PER_BLOCK;
    inline constexpr unsigned int FLOATS_PER_VERTEX = 5;
    inline constexpr unsigned int FLOATS_PER_FACE = VERTICES_PER_FACE * FLOATS_PER_VERTEX;
    inline constexpr unsigned int BYTES_PER_FACE = FLOATS_PER_FACE * sizeof(float);
    inline constexpr unsigned int INDICES_PER_FACE = 6;
    inline const std::vector<unsigned int> VERTEX_BUFFER_LAYOUT = { 3, 2 };

	enum BlockType : unsigned char {
		AIR,
		GRASS,
		DIRT,
		STONE,
	};

    enum BlockFace : unsigned char {
        PLUS_X,
        MINUS_X,
        PLUS_Y,
        MINUS_Y,
        PLUS_Z,
        MINUS_Z,
    };

    const float* getData(Block::BlockType type, Block::BlockFace face);

    inline constexpr unsigned int FACE_INDICES[] = {
         0u, 1u, 3u, 3u, 2u, 0u,
    };

    inline constexpr float GRASS_BLOCK_DATA[] = {
        // right (+x)
        1.0f, 0.0f, 1.0f,    0.0f,    0.9375f,
        1.0f, 0.0f, 0.0f,    0.0625f, 0.9375f,
        1.0f, 1.0f, 1.0f,    0.0f,    1.0f,
        1.0f, 1.0f, 0.0f,    0.0625f, 1.0f,
        // left (-x)
        0.0f, 0.0f, 0.0f,    0.0f,    0.9375f,
        0.0f, 0.0f, 1.0f,    0.0625f, 0.9375f,
        0.0f, 1.0f, 0.0f,    0.0f,    1.0f,
        0.0f, 1.0f, 1.0f,    0.0625f, 1.0f,
        // top (+y)
        0.0f, 1.0f, 1.0f,    0.125f,  0.9375f,
        1.0f, 1.0f, 1.0f,    0.1875f, 0.9375f,
        0.0f, 1.0f, 0.0f,    0.125f,  1.0f,
        1.0f, 1.0f, 0.0f,    0.1875f, 1.0f,
        // bottom (-y)
        0.0f, 0.0f, 0.0f,    0.0625f, 0.9375f,
        1.0f, 0.0f, 0.0f,    0.125f,  0.9375f,
        0.0f, 0.0f, 1.0f,    0.0625f, 1.0f,
        1.0f, 0.0f, 1.0f,    0.125f,  1.0f,
        // front (+z)
        0.0f, 0.0f, 1.0f,    0.0f,    0.9375f,
        1.0f, 0.0f, 1.0f,    0.0625f, 0.9375f,
        0.0f, 1.0f, 1.0f,    0.0f,    1.0f,
        1.0f, 1.0f, 1.0f,    0.0625f, 1.0f,
        // back (-z)
        1.0f, 0.0f, 0.0f,    0.0f,    0.9375f,
        0.0f, 0.0f, 0.0f,    0.0625f, 0.9375f,
        1.0f, 1.0f, 0.0f,    0.0f,    1.0f,
        0.0f, 1.0f, 0.0f,    0.0625f, 1.0f,
    };

    inline constexpr float DIRT_BLOCK_DATA[] = {
        // right (+x)
        1.0f, 0.0f, 1.0f,    0.0625f, 0.9375f,
        1.0f, 0.0f, 0.0f,    0.125f,  0.9375f,
        1.0f, 1.0f, 1.0f,    0.0625f, 1.0f,
        1.0f, 1.0f, 0.0f,    0.125f,  1.0f,
        // left (-x)
        0.0f, 0.0f, 0.0f,    0.0625f, 0.9375f,
        0.0f, 0.0f, 1.0f,    0.125f,  0.9375f,
        0.0f, 1.0f, 0.0f,    0.0625f, 1.0f,
        0.0f, 1.0f, 1.0f,    0.125f,  1.0f,
        // top (+y)
        0.0f, 1.0f, 1.0f,    0.0625f, 0.9375f,
        1.0f, 1.0f, 1.0f,    0.125f,  0.9375f,
        0.0f, 1.0f, 0.0f,    0.0625f, 1.0f,
        1.0f, 1.0f, 0.0f,    0.125f,  1.0f,
        // bottom (-y)
        0.0f, 0.0f, 0.0f,    0.0625f, 0.9375f,
        1.0f, 0.0f, 0.0f,    0.125f,  0.9375f,
        0.0f, 0.0f, 1.0f,    0.0625f, 1.0f,
        1.0f, 0.0f, 1.0f,    0.125f,  1.0f,
        // front (+z)
        0.0f, 0.0f, 1.0f,    0.0625f, 0.9375f,
        1.0f, 0.0f, 1.0f,    0.125f,  0.9375f,
        0.0f, 1.0f, 1.0f,    0.0625f, 1.0f,
        1.0f, 1.0f, 1.0f,    0.125f,  1.0f,
        // back (-z)
        1.0f, 0.0f, 0.0f,    0.0625f, 0.9375f,
        0.0f, 0.0f, 0.0f,    0.125f,  0.9375f,
        1.0f, 1.0f, 0.0f,    0.0625f, 1.0f,
        0.0f, 1.0f, 0.0f,    0.125f,  1.0f,
    };

    inline constexpr float STONE_BLOCK_DATA[120] = {
        // right (+x)
        1.0f, 0.0f, 1.0f,    0.1875f, 0.9375f,
        1.0f, 0.0f, 0.0f,    0.25f,   0.9375f,
        1.0f, 1.0f, 1.0f,    0.1875f, 1.0f,
        1.0f, 1.0f, 0.0f,    0.25f,   1.0f,
        // left (-x)
        0.0f, 0.0f, 0.0f,    0.1875f, 0.9375f,
        0.0f, 0.0f, 1.0f,    0.25f,   0.9375f,
        0.0f, 1.0f, 0.0f,    0.1875f, 1.0f,
        0.0f, 1.0f, 1.0f,    0.25f,   1.0f,
        // top (+y)
        0.0f, 1.0f, 1.0f,    0.1875f, 0.9375f,
        1.0f, 1.0f, 1.0f,    0.25f,   0.9375f,
        0.0f, 1.0f, 0.0f,    0.1875f, 1.0f,
        1.0f, 1.0f, 0.0f,    0.25f,   1.0f,
        // bottom (-y)
        0.0f, 0.0f, 0.0f,    0.1875f, 0.9375f,
        1.0f, 0.0f, 0.0f,    0.25f,   0.9375f,
        0.0f, 0.0f, 1.0f,    0.1875f, 1.0f,
        1.0f, 0.0f, 1.0f,    0.25f,   1.0f,
        // front (+z)
        0.0f, 0.0f, 1.0f,    0.1875f, 0.9375f,
        1.0f, 0.0f, 1.0f,    0.25f,   0.9375f,
        0.0f, 1.0f, 1.0f,    0.1875f, 1.0f,
        1.0f, 1.0f, 1.0f,    0.25f,   1.0f,
        // back (-z)
        1.0f, 0.0f, 0.0f,    0.1875f, 0.9375f,
        0.0f, 0.0f, 0.0f,    0.25f,   0.9375f,
        1.0f, 1.0f, 0.0f,    0.1875f, 1.0f,
        0.0f, 1.0f, 0.0f,    0.25f,   1.0f,
    };

}

#endif

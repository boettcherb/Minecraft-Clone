#ifndef BLOCK_TYPE_H_INCLUDED
#define BLOCK_TYPE_H_INCLUDED

#include <vector>

namespace Block {

    inline constexpr unsigned int FACES_PER_BLOCK = 6;
    inline constexpr unsigned int VERTICES_PER_FACE = 4;
    inline constexpr unsigned int VERTICES_PER_BLOCK = VERTICES_PER_FACE * FACES_PER_BLOCK;
    inline constexpr unsigned int UINTS_PER_VERTEX = 1;
    inline constexpr unsigned int UINTS_PER_FACE = VERTICES_PER_FACE * UINTS_PER_VERTEX;
    inline constexpr unsigned int BYTES_PER_FACE = UINTS_PER_FACE * sizeof(float);
    inline constexpr unsigned int INDICES_PER_FACE = 6;
    inline const std::vector<unsigned int> VERTEX_BUFFER_LAYOUT = { 1 };

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

    const unsigned int* getData(Block::BlockType type, Block::BlockFace face);

    inline constexpr unsigned int FACE_INDICES[] = {
         0u, 1u, 3u, 3u, 2u, 0u,
    };

    inline constexpr unsigned int GRASS_BLOCK_DATA[] = {
        //posX  posY  posZ  texX  texY
        0b00001'00000'00001'00000'01111, // right (+x)
        0b00001'00000'00000'00001'01111, 
        0b00001'00001'00001'00000'10000, 
        0b00001'00001'00000'00001'10000, 

        0b00000'00000'00000'00000'01111, // left (-x)
        0b00000'00000'00001'00001'01111, 
        0b00000'00001'00000'00000'10000, 
        0b00000'00001'00001'00001'10000, 

        0b00000'00001'00001'00010'01111, // top (+y)
        0b00001'00001'00001'00011'01111, 
        0b00000'00001'00000'00010'10000, 
        0b00001'00001'00000'00011'10000, 

        0b00000'00000'00000'00001'01111, // bottom (-y)
        0b00001'00000'00000'00010'01111, 
        0b00000'00000'00001'00001'10000, 
        0b00001'00000'00001'00010'10000, 

        0b00000'00000'00001'00000'01111, // front (+z)
        0b00001'00000'00001'00001'01111, 
        0b00000'00001'00001'00000'10000, 
        0b00001'00001'00001'00001'10000, 

        0b00001'00000'00000'00000'01111, // back (-z)
        0b00000'00000'00000'00001'01111,
        0b00001'00001'00000'00000'10000,
        0b00000'00001'00000'00001'10000,
    };

    /*
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
    */

}

#endif

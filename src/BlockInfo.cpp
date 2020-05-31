#include "BlockInfo.h"

#include <iostream>

namespace Block {

    const float* getData(BlockType type, BlockFace face) {
        int offset = FLOATS_PER_FACE * face;
        switch (type) {
            case GRASS: return GRASS_BLOCK_DATA + offset;
            case DIRT:  return DIRT_BLOCK_DATA + offset;
            case STONE: return STONE_BLOCK_DATA + offset;
        }
        std::cerr << "Invalid type / No data for this block: " << type << '\n';
        return nullptr;
    }

}

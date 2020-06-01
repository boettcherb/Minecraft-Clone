#include "BlockInfo.h"

#include <iostream>

namespace Block {

    const unsigned int* getData(BlockType type, BlockFace face) {
        int offset = UINTS_PER_FACE * face;
        switch (type) {
            case GRASS: return GRASS_BLOCK_DATA + offset;
            case DIRT:  return DIRT_BLOCK_DATA + offset;
            case STONE: return STONE_BLOCK_DATA + offset;
        }
        std::cerr << "Invalid type / No data for this block: " << type << '\n';
        return nullptr;
    }

}

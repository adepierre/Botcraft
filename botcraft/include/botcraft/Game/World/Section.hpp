#pragma once

#include <vector>

#include "botcraft/Game/World/Chunk.hpp"

namespace Botcraft
{
    struct Section
    {
        Section(const bool has_sky_light)
        {
            // +2 because we also store the neighbour section blocks
            data_blocks = std::vector<Block>((CHUNK_WIDTH + 2) * (CHUNK_WIDTH + 2) * SECTION_HEIGHT);
            block_light = std::vector<unsigned char>(CHUNK_WIDTH * CHUNK_WIDTH * SECTION_HEIGHT);
            if (has_sky_light)
            {
                sky_light = std::vector<unsigned char>(CHUNK_WIDTH * CHUNK_WIDTH * SECTION_HEIGHT);
            }
        }
        std::vector<Block> data_blocks;
        std::vector<unsigned char> block_light;
        std::vector<unsigned char> sky_light;
    };
} // Botcraft
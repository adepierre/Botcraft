#pragma once

#include <vector>

namespace Botcraft
{
    class Blockstate;

    struct Section
    {
        Section(const bool has_sky_light);

        static size_t CoordsToBlockIndex(const int x, const int y, const int z);
        static size_t CoordsToLightIndex(const int x, const int y, const int z);

        std::vector<const Blockstate*> data_blocks;
        std::vector<unsigned char> block_light;
        std::vector<unsigned char> sky_light;
    };
} // Botcraft

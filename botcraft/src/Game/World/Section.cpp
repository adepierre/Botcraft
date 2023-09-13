#include "botcraft/Game/World/Blockstate.hpp"
#include "botcraft/Game/World/Chunk.hpp"
#include "botcraft/Game/World/Section.hpp"

namespace Botcraft
{
    Section::Section(const bool has_sky_light)
    {
#if USE_GUI
        // +2 because we also store the neighbour section blocks
        data_blocks = std::vector<const Blockstate*>((CHUNK_WIDTH + 2) * (CHUNK_WIDTH + 2) * SECTION_HEIGHT);
#else
        data_blocks = std::vector<Block>(CHUNK_WIDTH * CHUNK_WIDTH * SECTION_HEIGHT);
#endif

        block_light = std::vector<unsigned char>(CHUNK_WIDTH * CHUNK_WIDTH * SECTION_HEIGHT);
        if (has_sky_light)
        {
            sky_light = std::vector<unsigned char>(CHUNK_WIDTH * CHUNK_WIDTH * SECTION_HEIGHT);
        }
    }

    size_t Section::CoordsToBlockIndex(const int x, const int y, const int z)
    {
#if USE_GUI
        return (y * (CHUNK_WIDTH + 2) + z + 1) * (CHUNK_WIDTH + 2) + x + 1;
#else
        return (y * CHUNK_WIDTH + z) * CHUNK_WIDTH + x;
#endif
    }

    size_t Section::CoordsToLightIndex(const int x, const int y, const int z)
    {
        return (y * CHUNK_WIDTH + z) * CHUNK_WIDTH + x;
    }
} // Botcraft

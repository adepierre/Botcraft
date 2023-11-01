#pragma once

#include <string>

namespace Botcraft
{
    // Enum for biomes with special color processing
    enum class BiomeType
    {
        Classic = 0,
        Swamp = 1,
        DarkForest = 2,
        Badlands = 3,
#if PROTOCOL_VERSION >= 393 /* >= 1.13 */
        WarmOcean = 4,
        LukewarmOcean = 5,
        ColdOcean = 6,
        FrozenOcean = 7
#endif
    };

    class Biome
    {
    public:
        Biome(const std::string& name_, const float temperature_,
              const float rainfall_, const BiomeType biome_type_);
        ~Biome();

        const std::string& GetName() const;
        
        // Height is the y value of the block
        const unsigned int GetColorMultiplier(const int height, const bool is_grass) const;
        const unsigned int GetWaterColorMultiplier() const;

    private:
        // Compute the value of the pixel in the triangle defined by the colors of the three corners
        // height is 0 if y <= 64 and y - 64 otherwise
        const unsigned int ComputeColorTriangle(const int height, const bool is_grass) const;

    private:
        std::string name;
        float temperature;
        float rainfall;
        unsigned int default_grass;
        unsigned int default_leaves;
        BiomeType biome_type;
    };
} // Botcraft
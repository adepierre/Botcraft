#pragma once

#include <string>

namespace Botcraft
{
    /// @brief Enum for biomes with special color processing
    enum class BiomeType
    {
        Classic,
        Swamp,
        DarkForest,
        Badlands,
#if PROTOCOL_VERSION >= 393 /* >= 1.13 */
        WarmOcean ,
        LukewarmOcean,
        ColdOcean,
        FrozenOcean,
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        PaleGarden,
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
        unsigned int GetColorMultiplier(const int height, const bool is_grass) const;
        unsigned int GetWaterColorMultiplier() const;

    private:
        // Compute the value of the pixel in the triangle defined by the colors of the three corners
        // height is 0 if y <= 64 and y - 64 otherwise
        unsigned int ComputeColorTriangle(const int height, const bool is_grass) const;

    private:
        std::string name;
        float temperature;
        float rainfall;
        unsigned int default_grass;
        unsigned int default_leaves;
        BiomeType biome_type;
    };
} // Botcraft
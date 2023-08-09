#pragma once

#include <string>
#include <vector>
#include <random>
#include <map>

#include "protocolCraft/Utilities/Json.hpp"

#include "botcraft/Game/Model.hpp"
#include "botcraft/Game/Enums.hpp"

namespace Botcraft
{
#if USE_GUI
    namespace Renderer
    {
        class Atlas;
    }
#endif

    struct BestTool
    {
        ToolType tool_type;
        ToolMaterial min_material;
        float multiplier;
    };

    struct BlockstateProperties
    {
#if PROTOCOL_VERSION < 347
        int id = -1;
        unsigned char metadata = 0;
#else
        int id = -1;
#endif
        /// @brief True if the block is air (air, cave_air, void and structure_void are counted as air)
        bool air = false;
        /// @brief True if not a full 1x1x1 block OR at least one face texture has transparency
        bool transparent = false;
        /// @brief True if can't go through it
        bool solid = false;
        /// @brief True for water and lava
        bool fluid = false;
        /// @brief True if can be used as a ladder
        bool climbable = false;
        /// @brief True if the model is a custom one (chests/banners etc...)
        bool custom = false;
        /// @brief True if block can hurt when walking in/on it
        bool hazardous = false;
        /// @brief Digging hardness
        float hardness = -2.0f;
        TintType tint_type = TintType::None;
        std::string name = "";
        std::string path = "";
        std::vector<std::string> variables = std::vector<std::string>(0);
        bool any_tool_harvest = false;
        std::vector<BestTool> best_tools = std::vector<BestTool>(0);
    };

    class Blockstate
    {
    public:
        /// @brief Create a blockstate reading files from properties path
        /// @param properties The properties of this blockstate
        Blockstate(const BlockstateProperties& properties);

        /// @brief Create a blockstate from a given model, ignoring path in properties
        /// @param properties The properties of this blockstate
        /// @param model_ The model of this blockstate
        Blockstate(const BlockstateProperties& properties, const Model &model_);

        const unsigned int GetId() const;
#if PROTOCOL_VERSION < 347
        const unsigned char GetMetadata() const;
#endif
        const Model &GetModel(const unsigned short index) const;
        const unsigned char GetRandomModelId(const Position* pos = nullptr) const;
        const int GetNumModels() const;
        const std::string &GetName() const;
        const std::string& GetVariableValue(const std::string& variable) const;

        const bool IsAir() const;
        const bool IsSolid() const;
        const bool IsTransparent() const;
        const bool IsFluid() const;
        const bool IsClimbable() const;
        const bool IsHazardous() const;
        bool IsWaterlogged() const;
        const float GetHardness() const;
        const TintType GetTintType() const;

        /// @brief Compute the amount of time (in s) required to mine this block
        /// @param tool_type The tool used to mine
        /// @param tool_material The material the tool is made of
        /// @param tool_efficiency Level of efficiency enchantment on the tool
        /// @param haste Level of haste applied to the player
        /// @param fatigue Level of mining fatigue applied to the player
        /// @param on_ground Boolean indicating whether or not the player is currently on the ground
        /// @param head_in_fluid_wo_aqua_affinity Boolean indicating whether or not the player head is currently in fluid without aqua affinity enchantment
        /// @return The time required to mine this block in these conditions, or -1 if can't be mined
        float GetMiningTimeSeconds(const ToolType tool_type, const ToolMaterial tool_material,
            const unsigned char tool_efficiency = 0, const unsigned char haste = 0, const unsigned char fatigue = 0,
            const bool on_ground = true, const bool head_in_fluid_wo_aqua_affinity = false) const;

#if PROTOCOL_VERSION < 347
        const static unsigned int IdMetadataToId(const unsigned int id_, const unsigned char metadata_);
        static void IdToIdMetadata(const unsigned int input_id, unsigned int &output_id, unsigned char &output_metadata);
#endif
        static void ClearCache();

#if USE_GUI
        void UpdateModelsWithAtlasData(const Renderer::Atlas* atlas);
#endif

    private:
        static std::map<std::string, ProtocolCraft::Json::Value> cached_jsons;

        bool air;
        bool transparent;
        bool solid;
        bool fluid;
        bool climbable;
        bool hazardous;
        float hardness;
        TintType tint_type;
        std::string m_name;

        std::vector<Model> models;
        std::vector<int> models_weights;
        int weights_sum;
        mutable std::mt19937 random_generator;

        bool any_tool_harvest;
        std::vector<BestTool> best_tools;

        std::unordered_map<std::string, std::string> variables;

        unsigned int id;
#if PROTOCOL_VERSION < 347
        unsigned char metadata;
#endif
    };
} // Botcraft

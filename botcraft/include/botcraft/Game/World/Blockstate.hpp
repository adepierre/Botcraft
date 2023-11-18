#pragma once

#include <deque>
#include <map>
#include <string>
#include <vector>

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

#if PROTOCOL_VERSION < 347 /* < 1.13 */
    using BlockstateId = std::pair<int, unsigned char>;
#else
    using BlockstateId = unsigned int;
#endif

    struct BlockstateProperties
    {
#if PROTOCOL_VERSION < 347 /* < 1.13 */
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
        /// @brief Slipperiness coefficient
        float friction = 0.6f;
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
        Blockstate(const BlockstateProperties& properties, const Model& model_);

        BlockstateId GetId() const;
        const Model& GetModel(const unsigned short index) const;
        unsigned char GetModelId(const Position& pos) const;
        size_t GetNumModels() const;
        const std::string& GetName() const;
        const std::string& GetVariableValue(const std::string& variable) const;

        bool IsAir() const;
        bool IsSolid() const;
        bool IsTransparent() const;
        bool IsFluid() const;
        bool IsClimbable() const;
        bool IsHazardous() const;
        bool IsWaterlogged() const;
        float GetHardness() const;
        float GetFriction() const;
        TintType GetTintType() const;

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

#if PROTOCOL_VERSION < 347 /* < 1.13 */
        static unsigned int IdMetadataToId(const int id_, const unsigned char metadata_);
        static void IdToIdMetadata(const unsigned int input_id, int& output_id, unsigned char& output_metadata);
#endif
        static void ClearCache();

#if USE_GUI
        static void UpdateModelsWithAtlasData(const Renderer::Atlas* atlas);
#endif

    private:
        void LoadWeightedModels(const std::deque<std::pair<Model, int>>& models_to_load);

        // std::set does not invalidate pointers when growing
        static std::set<std::string> unique_strings;
        static const std::string* GetUniqueStringPtr(const std::string& s);
        static std::deque<Model> unique_models;
        static size_t GetUniqueModelIndex(const Model& model);
        static std::map<std::string, ProtocolCraft::Json::Value> cached_jsons;

        struct string_ptr_compare
        {
            bool operator()(const std::string* a, const std::string* b) const
            {
                return *a < *b;
            }
        };

    private:
        BlockstateId blockstate_id;

        bool air;
        bool transparent;
        bool solid;
        bool fluid;
        bool climbable;
        bool hazardous;
        float hardness;
        float friction;
        TintType tint_type;
        const std::string* m_name;

        std::vector<size_t> models_indices;
        std::vector<int> models_weights;
        int weights_sum;

        bool any_tool_harvest;
        std::vector<BestTool> best_tools;

        std::map<const std::string*, const std::string*, string_ptr_compare> variables; // map is smaller in RAM than unordered_map
    };
} // Botcraft

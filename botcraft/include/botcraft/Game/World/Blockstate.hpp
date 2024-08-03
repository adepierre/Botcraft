#pragma once

#include <bitset>
#include <deque>
#include <map>
#include <string>
#include <vector>

#include "protocolCraft/Utilities/Json.hpp"

#include "botcraft/Game/Enums.hpp"
#include "botcraft/Game/Model.hpp"

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
        /// @brief True if can't go through it
        ProtocolCraft::Json::Value solid = false;
        /// @brief True if not a full 1x1x1 block OR at least one face texture has transparency
        bool transparent = false;
        /// @brief True for lava
        bool lava = false;
        /// @brief True for water
        bool water = false;
        /// @brief True for blocks that are always waterlogged (kelp, seagrass...)
        ProtocolCraft::Json::Value waterlogged = false;
        /// @brief True if can be used as a ladder
        bool climbable = false;
        /// @brief True if block can hurt when walking in/on it
        bool hazardous = false;
        /// @brief True if this block drops item when broken with no tool
        bool any_tool_harvest = false;
        /// @brief True if this block is slime
        bool slime = false;
        /// @brief True if this block has the BEDS tag
        bool bed = false;
        /// @brief True if this block is soul_sand
        bool soul_sand = false;
        /// @brief True if this block is honey
        bool honey = false;
        /// @brief True if this block is scaffolding
        bool scaffolding = false;
        /// @brief True if this block is cobweb
        bool cobweb = false;
        /// @brief True if this block is a bubble column going up
        ProtocolCraft::Json::Value up_bubble_column = false;
        /// @brief True if this block is a bubble column going down
        ProtocolCraft::Json::Value down_bubble_column = false;
        /// @brief True if this block is sweet_berry_bush
        bool berry_bush = false;
        /// @brief True if this block is powder_snow
        bool powder_snow = false;
        /// @brief Max horizontal offset value of the colliders (for bamboo and pointed dripstone)
        float horizontal_offset = 0.0f;
        /// @brief Digging hardness
        float hardness = -2.0f;
        /// @brief Slipperiness coefficient
        float friction = 0.6f;
        /// @brief True if the model is a custom one (chests/banners etc...)
        bool custom = false;
        TintType tint_type = TintType::None;
        std::string name = "";
        std::string path = "";
        std::vector<std::string> variables = std::vector<std::string>(0);
        std::vector<BestTool> best_tools = std::vector<BestTool>(0);
        ProtocolCraft::Json::Value colliders = ProtocolCraft::Json::Value();
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
        Vector3<double> GetHorizontalOffsetAtPos(const Position& pos) const;
        std::set<AABB> GetCollidersAtPos(const Position& pos) const;
        /// @brief Get the closest point on this blockstate placed at block_pos from a reference pos
        /// @param block_pos Block position
        /// @param pos Reference position to find the closest point from
        /// @return The closest point inside the block AABB shapes
        Vector3<double> GetClosestPoint(const Position& block_pos, const Vector3<double>& pos) const;

        bool IsAir() const;
        bool IsSolid() const;
        bool IsTransparent() const;
        bool IsFluid() const;
        bool IsFluidOrWaterlogged() const;
        bool IsLava() const;
        bool IsFluidFalling() const;
        bool IsWater() const;
        bool IsWaterlogged() const;
        bool IsWaterOrWaterlogged() const;
        bool IsClimbable() const;
        bool IsHazardous() const;
        bool IsSlime() const;
        bool IsBed() const;
        bool IsSoulSand() const;
        bool IsHoney() const;
        bool IsScaffolding() const;
        bool IsCobweb() const;
        bool IsBubbleColumn() const;
        bool IsUpBubbleColumn() const;
        bool IsDownBubbleColumn() const;
        bool IsBerryBush() const;
        bool IsPowderSnow() const;
        float GetHardness() const;
        float GetFriction() const;
        TintType GetTintType() const;
        /// @brief Get fluid height for this block. Does not take into account neighbouring blocks
        /// @return Height of fluid in this block, between 0 and 1
        float GetFluidHeight() const;

        /// @brief Compute the amount of time (in s) required to mine this block
        /// @param tool_type The tool used to mine
        /// @param tool_material The material the tool is made of
        /// @param tool_efficiency_additional_speed Additional speed added by current tool level of efficiency enchantment (efficiency² + (efficiency > 0))
        /// @param haste Level of haste applied to the player
        /// @param fatigue Level of mining fatigue applied to the player
        /// @param on_ground Boolean indicating whether or not the player is currently on the ground
        /// @param speed_factor Speed multiplier to apply (e.g. 0.2 if under water with no aqua affinity)
        /// @return The time required to mine this block in these conditions, or -1 if can't be mined
        float GetMiningTimeSeconds(const ToolType tool_type, const ToolMaterial tool_material,
            const float tool_efficiency_additional_speed = 0.0f, const unsigned char haste = 0, const unsigned char fatigue = 0,
            const bool on_ground = true, const float speed_factor = 1.0f) const;

#if PROTOCOL_VERSION < 347 /* < 1.13 */
        static unsigned int IdMetadataToId(const int id_, const unsigned char metadata_);
        static void IdToIdMetadata(const unsigned int input_id, int& output_id, unsigned char& output_metadata);
#endif
        static void ClearCache();

#if USE_GUI
        static void UpdateModelsWithAtlasData(const Renderer::Atlas* atlas);
#endif

    private:
        void LoadProperties(const BlockstateProperties& properties);
        void LoadWeightedModels(const std::deque<std::pair<Model, int>>& models_to_load);
        bool GetBoolFromCondition(const ProtocolCraft::Json::Value& condition) const;
        /// @brief Check if a given string condition match this blockstate variables
        /// @param condition String to check, example: "layers=1"
        /// @return True if variables values match, false otherwise
        bool MatchCondition(const std::string& condition) const;

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


        enum class BlockstateFlags : size_t
        {
            Air = 0,
            Solid,
            Transparent,
            Lava,
            Water,
            WaterLogged,
            FluidFalling,
            FluidLevelBit_0,
            FluidLevelBit_1,
            FluidLevelBit_2,
            Climbable,
            Hazardous,
            AnyToolHarvest,
            Slime,
            Bed,
            SoulSand,
            Honey,
            Scaffolding,
            Cobweb,
            UpBubbleColumn,
            DownBubbleColumn,
            BerryBush,
            PowderSnow,
            HorizontalOffset0_25,
            HorizontalOffset0_125,
            NUM_FLAGS
        };

        std::bitset<static_cast<size_t>(BlockstateFlags::NUM_FLAGS)> flags;
        float hardness;
        float friction;
        TintType tint_type;
        const std::string* m_name;

        std::vector<size_t> models_indices;
        std::vector<int> models_weights;
        int weights_sum;

        std::vector<BestTool> best_tools;

        std::map<const std::string*, const std::string*, string_ptr_compare> variables; // map is smaller in RAM than unordered_map
    };
} // Botcraft

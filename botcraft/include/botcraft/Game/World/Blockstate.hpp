#pragma once

#include <string>
#include <random>
#include <map>

#include <nlohmann/json.hpp>

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

    struct BlockstateProperties
    {
#if PROTOCOL_VERSION < 347
        int id = -1;
        unsigned char metadata = 0;
#else
        int id = -1;
#endif
        bool transparent = false;//
        bool solid = false;//
        bool fluid = false;
        bool climbable = false;//
        bool custom = false;
        float hardness = -2.0f;//
        TintType tint_type = TintType::None;
        std::string name = "";//
        std::string path = "";
        std::vector<std::string> variables = std::vector<std::string>(0);
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
        const Model &GetModel(const unsigned char index) const;
        const unsigned char GetRandomModelId(const Position* pos = nullptr) const;
        const int GetNumModels() const;
        const std::string &GetName() const;
        const std::string& GetVariableValue(const std::string& variable) const;

        const bool IsAir() const;
        const bool IsSolid() const;
        const bool IsTransparent() const;
        const bool IsFluid() const;
        const bool IsClimbable() const;
        const float GetHardness() const;
        const TintType GetTintType() const;

#if PROTOCOL_VERSION < 347
        const static unsigned int IdMetadataToId(const unsigned int id_, const unsigned char metadata_);
        static void IdToIdMetadata(const unsigned int input_id, unsigned int &output_id, unsigned char &output_metadata);
#endif
        static void ClearCache();

#if USE_GUI
        void UpdateModelsWithAtlasData(const Renderer::Atlas* atlas);
#endif

    private:
        static std::map<std::string, nlohmann::json> cached_jsons;

        bool transparent;
        bool solid;
        bool fluid;
        bool climbable;
        float hardness;
        TintType tint_type;
        std::string m_name;

        std::vector<Model> models;
        std::vector<int> models_weights;
        int weights_sum;
        mutable std::mt19937 random_generator;

        std::unordered_map<std::string, std::string> variables;

        unsigned int id;
#if PROTOCOL_VERSION < 347
        unsigned char metadata;
#endif
    };
} // Botcraft
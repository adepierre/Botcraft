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

    class Blockstate
    {
    public:

#if PROTOCOL_VERSION < 347
        Blockstate(const int id_, const unsigned char metadata_,
                   const bool transparent_, const bool solid_,  const bool fluid_, const bool custom,
                   const float hardness_, const TintType tint_type_, const std::string &name_,
                   const std::string &path = "", const std::vector<std::string> &variables_ = std::vector<std::string>());

        Blockstate(const int id_, const unsigned char metadata_,
                   const bool transparent_, const bool solid_, const bool fluid_,
                   const float hardness_, const TintType tint_type_, const std::string &name_,
                   const Model &model_);
#else
        Blockstate(const int id_,
                   const bool transparent_, const bool solid_, const bool fluid_, const bool custom,
                   const float hardness_, const TintType tint_type_, const std::string &name_,
                   const std::string &path = "", const std::vector<std::string> &variables_ = std::vector<std::string>());
        
        Blockstate(const int id_,
                   const bool transparent_, const bool solid_, const bool fluid_,
                   const float hardness_, const TintType tint_type_, const std::string &name_,
                   const Model &model_);
#endif
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
        float hardness;
        TintType tint_type;
        std::string m_name;

        std::vector<Model> models;
        std::vector<int> models_weights;
        int weights_sum;
        mutable std::mt19937 random_generator;
        std::uniform_int_distribution<int> random_distrib;

        std::unordered_map<std::string, std::string> variables;

        unsigned int id;
#if PROTOCOL_VERSION < 347
        unsigned char metadata;
#endif
    };
} // Botcraft
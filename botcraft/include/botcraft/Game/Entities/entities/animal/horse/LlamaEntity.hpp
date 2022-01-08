#pragma once

#include "botcraft/Game/Entities/entities/animal/horse/AbstractChestedHorseEntity.hpp"

namespace Botcraft
{
    class LlamaEntity : public AbstractChestedHorseEntity
    {
    protected:
        static constexpr int metadata_count = 3;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = AbstractChestedHorseEntity::metadata_count + AbstractChestedHorseEntity::hierarchy_metadata_count;

    public:
        LlamaEntity();
        virtual ~LlamaEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;
        virtual AABB GetCollider() const override;
        virtual double GetWidth() const override;
        virtual double GetHeight() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual nlohmann::json Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        int GetDataStrengthId() const;
        int GetDataSwagId() const;
        int GetDataVariantId() const;

        void SetDataStrengthId(const int data_strength_id);
        void SetDataSwagId(const int data_swag_id);
        void SetDataVariantId(const int data_variant_id);

    };
}

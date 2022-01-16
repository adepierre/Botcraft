#pragma once

#include "botcraft/Game/Entities/entities/projectile/AbstractArrowEntity.hpp"

namespace Botcraft
{
    class ArrowEntity : public AbstractArrowEntity
    {
    protected:
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = AbstractArrowEntity::metadata_count + AbstractArrowEntity::hierarchy_metadata_count;

    public:
        ArrowEntity();
        virtual ~ArrowEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;
        virtual double GetWidth() const override;
        virtual double GetHeight() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual nlohmann::json Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        int GetIdEffectColor() const;

        void SetIdEffectColor(const int id_effect_color);

    };
}

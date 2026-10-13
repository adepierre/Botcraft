#pragma once

#include "botcraft/Game/Entities/entities/projectile/arrow/AbstractArrowEntity.hpp"

namespace Botcraft
{
    class ArrowEntity : public AbstractArrowEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("id_effect_color"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = AbstractArrowEntity::metadata_count + AbstractArrowEntity::hierarchy_metadata_count;

    public:
        ArrowEntity();
        virtual ~ArrowEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        int GetIdEffectColor() const;

        void SetIdEffectColor(const int id_effect_color);

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}

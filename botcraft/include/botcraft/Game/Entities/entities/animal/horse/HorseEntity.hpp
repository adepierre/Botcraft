#pragma once

#include "botcraft/Game/Entities/entities/animal/horse/AbstractHorseEntity.hpp"

namespace Botcraft
{
    class HorseEntity : public AbstractHorseEntity
    {
    protected:
#if PROTOCOL_VERSION > 404
        static constexpr int metadata_count = 1;
#else
        static constexpr int metadata_count = 2;
#endif
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = AbstractHorseEntity::metadata_count + AbstractHorseEntity::hierarchy_metadata_count;

    public:
        HorseEntity();
        virtual ~HorseEntity();

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

        int GetDataIdTypeVariant() const;
#if PROTOCOL_VERSION < 405
        const std::optional<int>& GetArmorType() const;
#endif

        void SetDataIdTypeVariant(const int data_id_type_variant);
#if PROTOCOL_VERSION < 405
        void SetArmorType(const std::optional<int>& armor_type);
#endif

    };
}

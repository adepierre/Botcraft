#if PROTOCOL_VERSION > 340
#pragma once

#include "botcraft/Game/Entities/entities/animal/AbstractSchoolingFishEntity.hpp"

namespace Botcraft
{
    class TropicalFishEntity : public AbstractSchoolingFishEntity
    {
    protected:
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = AbstractSchoolingFishEntity::metadata_count + AbstractSchoolingFishEntity::hierarchy_metadata_count;

    public:
        TropicalFishEntity();
        virtual ~TropicalFishEntity();

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

        void SetDataIdTypeVariant(const int data_id_type_variant);

    };
}
#endif

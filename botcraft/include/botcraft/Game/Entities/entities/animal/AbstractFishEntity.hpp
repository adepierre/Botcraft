#pragma once

#include "botcraft/Game/Entities/entities/animal/WaterAnimalEntity.hpp"

namespace Botcraft
{
    class AbstractFishEntity : public WaterAnimalEntity
    {
    protected:
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = WaterAnimalEntity::metadata_count + WaterAnimalEntity::hierarchy_metadata_count;

    public:
        AbstractFishEntity();
        virtual ~AbstractFishEntity();

        virtual bool IsAbstractFish() const override;

        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        bool GetFromBucket() const;

        void SetFromBucket(const bool from_bucket);

    };
}

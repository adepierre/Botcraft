#pragma once

#include "botcraft/Game/Entities/entities/animal/fish/WaterAnimalEntity.hpp"

namespace Botcraft
{
    class AbstractFishEntity : public WaterAnimalEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("from_bucket"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = WaterAnimalEntity::metadata_count + WaterAnimalEntity::hierarchy_metadata_count;

    public:
        AbstractFishEntity();
        virtual ~AbstractFishEntity();

        virtual bool IsAbstractFish() const override;

        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        bool GetFromBucket() const;

        void SetFromBucket(const bool from_bucket);

    };
}

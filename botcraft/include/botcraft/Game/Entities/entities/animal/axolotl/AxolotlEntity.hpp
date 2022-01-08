#if PROTOCOL_VERSION > 754
#pragma once

#include "botcraft/Game/Entities/entities/animal/AnimalEntity.hpp"

namespace Botcraft
{
    class AxolotlEntity : public AnimalEntity
    {
    protected:
        static constexpr int metadata_count = 3;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = AnimalEntity::metadata_count + AnimalEntity::hierarchy_metadata_count;

    public:
        AxolotlEntity();
        virtual ~AxolotlEntity();

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

        int GetDataVariant() const;
        bool GetDataPlayingDead() const;
        bool GetFromBucket() const;

        void SetDataVariant(const int data_variant);
        void SetDataPlayingDead(const bool data_playing_dead);
        void SetFromBucket(const bool from_bucket);

    };
}
#endif

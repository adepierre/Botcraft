#if PROTOCOL_VERSION > 340
#pragma once

#include "botcraft/Game/Entities/entities/animal/WaterAnimalEntity.hpp"

namespace Botcraft
{
    class DolphinEntity : public WaterAnimalEntity
    {
    protected:
        static constexpr int metadata_count = 3;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = WaterAnimalEntity::metadata_count + WaterAnimalEntity::hierarchy_metadata_count;

    public:
        DolphinEntity();
        virtual ~DolphinEntity();

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

        const Position& GetTreasurePos() const;
        bool GetGotFish() const;
        int GetMoistnessLevel() const;

        void SetTreasurePos(const Position& treasure_pos);
        void SetGotFish(const bool got_fish);
        void SetMoistnessLevel(const int moistness_level);

    };
}
#endif

#if PROTOCOL_VERSION > 758
#pragma once

#include "botcraft/Game/Entities/entities/PathfinderMobEntity.hpp"

namespace Botcraft
{
    class AllayEntity : public PathfinderMobEntity
    {
    protected:
#if PROTOCOL_VERSION < 760
        static constexpr int metadata_count = 0;
#else
        static constexpr int metadata_count = 2;
        static const std::array<std::string, metadata_count> metadata_names;
#endif
        static constexpr int hierarchy_metadata_count = PathfinderMobEntity::metadata_count + PathfinderMobEntity::hierarchy_metadata_count;

    public:
        AllayEntity();
        virtual ~AllayEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;
        virtual double GetWidth() const override;
        virtual double GetHeight() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();

#if PROTOCOL_VERSION > 759
        virtual nlohmann::json Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        bool GetDataDancing() const;
        bool GetDataCanDuplicate() const;

        void SetDataDancing(const bool data_dancing);
        void SetDataCanDuplicate(const bool data_can_duplicate);
#endif

    };
}
#endif

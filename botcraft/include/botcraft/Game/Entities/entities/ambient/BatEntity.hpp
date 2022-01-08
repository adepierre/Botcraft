#pragma once

#include "botcraft/Game/Entities/entities/ambient/AmbientCreatureEntity.hpp"

namespace Botcraft
{
    class BatEntity : public AmbientCreatureEntity
    {
    protected:
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = AmbientCreatureEntity::metadata_count + AmbientCreatureEntity::hierarchy_metadata_count;

    public:
        BatEntity();
        virtual ~BatEntity();

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

        char GetDataIdFlags() const;

        void SetDataIdFlags(const char data_id_flags);

    };
}

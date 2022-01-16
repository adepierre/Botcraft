#if PROTOCOL_VERSION > 340
#pragma once

#include "botcraft/Game/Entities/entities/FlyingMobEntity.hpp"

namespace Botcraft
{
    class PhantomEntity : public FlyingMobEntity
    {
    protected:
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = FlyingMobEntity::metadata_count + FlyingMobEntity::hierarchy_metadata_count;

    public:
        PhantomEntity();
        virtual ~PhantomEntity();

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

        int GetIdSize() const;

        void SetIdSize(const int id_size);

    };
}
#endif

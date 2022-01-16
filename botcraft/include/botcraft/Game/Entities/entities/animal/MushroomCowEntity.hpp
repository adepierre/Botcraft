#pragma once

#include "botcraft/Game/Entities/entities/animal/CowEntity.hpp"

namespace Botcraft
{
    class MushroomCowEntity : public CowEntity
    {
    protected:
#if PROTOCOL_VERSION > 404
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
#else
        static constexpr int metadata_count = 0;
#endif
        static constexpr int hierarchy_metadata_count = CowEntity::metadata_count + CowEntity::hierarchy_metadata_count;

    public:
        MushroomCowEntity();
        virtual ~MushroomCowEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;
        virtual double GetWidth() const override;
        virtual double GetHeight() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


#if PROTOCOL_VERSION > 404
        virtual nlohmann::json Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        const std::string& GetDataType() const;

        void SetDataType(const std::string& data_type);
#endif

    };
}

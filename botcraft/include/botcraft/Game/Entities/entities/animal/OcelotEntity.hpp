#pragma once

#if PROTOCOL_VERSION > 404
#include "botcraft/Game/Entities/entities/animal/AnimalEntity.hpp"
#else
#include "botcraft/Game/Entities/entities/TamableAnimalEntity.hpp"
#endif

namespace Botcraft
{
#if PROTOCOL_VERSION > 404
    class OcelotEntity : public AnimalEntity
#else
    class OcelotEntity : public TamableAnimalEntity
#endif
    {
    protected:
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = AnimalEntity::metadata_count + AnimalEntity::hierarchy_metadata_count;

    public:
        OcelotEntity();
        virtual ~OcelotEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;
        virtual double GetWidth() const override;
        virtual double GetHeight() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

#if PROTOCOL_VERSION > 404
        bool GetDataTrusting() const;

        void SetDataTrusting(const bool data_trusting);
#else
        int GetDataTypeId() const;

        void SetDataTypeId(const int data_type_id);
#endif

    };
}

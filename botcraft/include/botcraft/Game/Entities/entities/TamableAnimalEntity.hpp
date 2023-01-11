#pragma once

#include "botcraft/Game/Entities/entities/animal/AnimalEntity.hpp"

namespace Botcraft
{
    class TamableAnimalEntity : public AnimalEntity
    {
    protected:
        static constexpr int metadata_count = 2;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = AnimalEntity::metadata_count + AnimalEntity::hierarchy_metadata_count;

    public:
        TamableAnimalEntity();
        virtual ~TamableAnimalEntity();

        virtual bool IsTamableAnimal() const override;

        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        char GetDataFlagsId() const;
        const std::optional<ProtocolCraft::UUID>& GetDataOwneruuidId() const;

        void SetDataFlagsId(const char data_flags_id);
        void SetDataOwneruuidId(const std::optional<ProtocolCraft::UUID>& data_owneruuid_id);

    };
}

#pragma once

#include "botcraft/Game/Entities/entities/animal/AnimalEntity.hpp"

namespace Botcraft
{
    class AbstractHorseEntity : public AnimalEntity
    {
    protected:
        static constexpr int metadata_count = 2;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = AnimalEntity::metadata_count + AnimalEntity::hierarchy_metadata_count;

    public:
        AbstractHorseEntity();
        virtual ~AbstractHorseEntity();

        virtual bool IsAbstractHorse() const override;

        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        char GetDataIdFlags() const;
        const std::optional<ProtocolCraft::UUID>& GetDataIdOwnerUuid() const;

        void SetDataIdFlags(const char data_id_flags);
        void SetDataIdOwnerUuid(const std::optional<ProtocolCraft::UUID>& data_id_owner_uuid);

    };
}

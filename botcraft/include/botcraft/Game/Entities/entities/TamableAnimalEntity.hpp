#pragma once

#include "botcraft/Game/Entities/entities/animal/AnimalEntity.hpp"

namespace Botcraft
{
    class TamableAnimalEntity : public AnimalEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_flags_id"),
            std::string_view("data_owneruuid_id"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = AnimalEntity::metadata_count + AnimalEntity::hierarchy_metadata_count;

    public:
        TamableAnimalEntity();
        virtual ~TamableAnimalEntity();

        virtual bool IsTamableAnimal() const override;

        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        char GetDataFlagsId() const;
        std::optional<ProtocolCraft::UUID> GetDataOwneruuidId() const;

        void SetDataFlagsId(const char data_flags_id);
        void SetDataOwneruuidId(const std::optional<ProtocolCraft::UUID>& data_owneruuid_id);

    };
}

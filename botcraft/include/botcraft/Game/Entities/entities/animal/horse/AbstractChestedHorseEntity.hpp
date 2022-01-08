#pragma once

#include "botcraft/Game/Entities/entities/animal/horse/AbstractHorseEntity.hpp"

namespace Botcraft
{
    class AbstractChestedHorseEntity : public AbstractHorseEntity
    {
    protected:
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = AbstractHorseEntity::metadata_count + AbstractHorseEntity::hierarchy_metadata_count;

    public:
        AbstractChestedHorseEntity();
        virtual ~AbstractChestedHorseEntity();

        virtual bool IsAbstractChestedHorse() const override;

        virtual nlohmann::json Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        bool GetDataIdChest() const;

        void SetDataIdChest(const bool data_id_chest);

    };
}

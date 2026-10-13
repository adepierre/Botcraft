#pragma once

#include "botcraft/Game/Entities/entities/animal/equine/AbstractHorseEntity.hpp"

namespace Botcraft
{
    class AbstractChestedHorseEntity : public AbstractHorseEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_id_chest"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = AbstractHorseEntity::metadata_count + AbstractHorseEntity::hierarchy_metadata_count;

    public:
        AbstractChestedHorseEntity();
        virtual ~AbstractChestedHorseEntity();

        virtual bool IsAbstractChestedHorse() const override;

        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        bool GetDataIdChest() const;

        void SetDataIdChest(const bool data_id_chest);

    };
}

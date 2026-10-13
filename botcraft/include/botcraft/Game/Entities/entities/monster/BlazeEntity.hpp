#pragma once

#include "botcraft/Game/Entities/entities/monster/MonsterEntity.hpp"

namespace Botcraft
{
    class BlazeEntity : public MonsterEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_flags_id"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = MonsterEntity::metadata_count + MonsterEntity::hierarchy_metadata_count;

    public:
        BlazeEntity();
        virtual ~BlazeEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        char GetDataFlagsId() const;

        void SetDataFlagsId(const char data_flags_id);

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}

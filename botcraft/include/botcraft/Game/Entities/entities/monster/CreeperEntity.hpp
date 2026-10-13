#pragma once

#include "botcraft/Game/Entities/entities/monster/MonsterEntity.hpp"

namespace Botcraft
{
    class CreeperEntity : public MonsterEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_swell_dir"),
            std::string_view("data_is_powered"),
            std::string_view("data_is_ignited"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = MonsterEntity::metadata_count + MonsterEntity::hierarchy_metadata_count;

    public:
        CreeperEntity();
        virtual ~CreeperEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        int GetDataSwellDir() const;
        bool GetDataIsPowered() const;
        bool GetDataIsIgnited() const;

        void SetDataSwellDir(const int data_swell_dir);
        void SetDataIsPowered(const bool data_is_powered);
        void SetDataIsIgnited(const bool data_is_ignited);

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}

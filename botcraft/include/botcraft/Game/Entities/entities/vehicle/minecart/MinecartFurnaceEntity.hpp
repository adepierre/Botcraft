#pragma once

#include "botcraft/Game/Entities/entities/vehicle/minecart/AbstractMinecartEntity.hpp"

namespace Botcraft
{
    class MinecartFurnaceEntity : public AbstractMinecartEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_id_fuel"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = AbstractMinecartEntity::metadata_count + AbstractMinecartEntity::hierarchy_metadata_count;

    public:
        MinecartFurnaceEntity();
        virtual ~MinecartFurnaceEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        bool GetDataIdFuel() const;

        void SetDataIdFuel(const bool data_id_fuel);

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}

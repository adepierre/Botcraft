#pragma once

#include "botcraft/Game/Entities/entities/vehicle/minecart/AbstractMinecartEntity.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace Botcraft
{
    class MinecartCommandBlockEntity : public AbstractMinecartEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_id_command_name"),
            std::string_view("data_id_last_output"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = AbstractMinecartEntity::metadata_count + AbstractMinecartEntity::hierarchy_metadata_count;

    public:
        MinecartCommandBlockEntity();
        virtual ~MinecartCommandBlockEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        std::string GetDataIdCommandName() const;
        ProtocolCraft::Chat GetDataIdLastOutput() const;

        void SetDataIdCommandName(const std::string& data_id_command_name);
        void SetDataIdLastOutput(const ProtocolCraft::Chat& data_id_last_output);

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}

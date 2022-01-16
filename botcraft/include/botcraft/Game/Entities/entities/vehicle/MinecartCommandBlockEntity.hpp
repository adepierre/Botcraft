#pragma once

#include "botcraft/Game/Entities/entities/vehicle/AbstractMinecartEntity.hpp"
#include "protocolCraft/Types/Chat.hpp"

namespace Botcraft
{
    class MinecartCommandBlockEntity : public AbstractMinecartEntity
    {
    protected:
        static constexpr int metadata_count = 2;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = AbstractMinecartEntity::metadata_count + AbstractMinecartEntity::hierarchy_metadata_count;

    public:
        MinecartCommandBlockEntity();
        virtual ~MinecartCommandBlockEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;
        virtual double GetWidth() const override;
        virtual double GetHeight() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual nlohmann::json Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        const std::string& GetDataIdCommandName() const;
        const ProtocolCraft::Chat& GetDataIdLastOutput() const;

        void SetDataIdCommandName(const std::string& data_id_command_name);
        void SetDataIdLastOutput(const ProtocolCraft::Chat& data_id_last_output);

    };
}

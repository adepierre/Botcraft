#if PROTOCOL_VERSION > 758
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ChatSender : public NetworkType
    {
    public:
        virtual ~ChatSender() override
        {

        }

        void SetUUID(const UUID& uuid_)
        {
            uuid = uuid_;
        }

        void SetName(const Chat& name_)
        {
            name = name_;
        }

        void SetTeamName(const std::optional<Chat>& team_name_)
        {
            team_name = team_name_;
        }


        const UUID& GetUUID() const
        {
            return uuid;
        }

        const Chat& GetName() const
        {
            return name;
        }

        const std::optional<Chat>& GetTeamName() const
        {
            return team_name;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            uuid = ReadData<UUID>(iter, length);
            name = ReadData<Chat>(iter, length);
            team_name = ReadOptional<Chat>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<UUID>(uuid, container);
            WriteData<Chat>(name, container);
            WriteOptional<Chat>(team_name, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["uuid"] = uuid;
            output["name"] = name.Serialize();
            if (team_name.has_value())
            {
                output["team_name"] = team_name.value().Serialize();
            }


            return output;
        }

    private:
        UUID uuid;
        Chat name;
        std::optional<Chat> team_name;
    };
}
#endif

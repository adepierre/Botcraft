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

        void SetTeamName(const Chat& team_name_)
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

        const Chat& GetTeamName() const
        {
            return team_name;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            uuid = ReadData<UUID>(iter, length);
            name.Read(iter, length);
            const bool has_team_name = ReadData<bool>(iter, length);
            if (has_team_name)
            {
                team_name.Read(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<UUID>(uuid, container);
            name.Write(container);
            if (!team_name.GetRawText().empty())
            {
                team_name.Write(container);
            }
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["uuid"] = uuid;
            output["name"] = name.Serialize();
            if (!team_name.GetRawText().empty())
            {
                output["team_name"] = team_name.Serialize();
            }


            return output;
        }

    private:
        UUID uuid;
        Chat name;
        Chat team_name;
    };
}
#endif

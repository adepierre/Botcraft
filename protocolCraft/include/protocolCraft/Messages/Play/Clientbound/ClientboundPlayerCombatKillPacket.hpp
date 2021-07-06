#pragma once

#if PROTOCOL_VERSION > 754
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundPlayerCombatKillPacket : public BaseMessage<ClientboundPlayerCombatKillPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x35;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Player Combat Kill";
        }

        virtual ~ClientboundPlayerCombatKillPacket() override
        {

        }


        void SetPlayerId(const int player_id_)
        {
            player_id = player_id_;
        }

        void SetKillerId(const int killer_id_)
        {
            killer_id = killer_id_;
        }

        void SetMessage(const Chat& message_)
        {
            message = message_;
        }



        const int GetPlayerId() const
        {
            return player_id;
        }

        const int GetKillerId() const
        {
            return killer_id;
        }

        const Chat& GetMessage() const
        {
            return message;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            player_id = ReadVarInt(iter, length);
            killer_id = ReadData<int>(iter, length);
            message.Read(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(player_id, container);
            WriteData<int>(killer_id, container);
            message.Write(container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["player_id"] = picojson::value((double)player_id);
            object["killer_id"] = picojson::value((double)killer_id);
            object["message"] = message.Serialize();

            return value;
        }

    private:
        int player_id;
        int killer_id;
        Chat message;

    };
} //ProtocolCraft
#endif
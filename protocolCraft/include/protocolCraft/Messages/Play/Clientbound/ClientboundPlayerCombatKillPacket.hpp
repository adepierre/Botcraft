#pragma once

#if PROTOCOL_VERSION > 754
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundPlayerCombatKillPacket : public BaseMessage<ClientboundPlayerCombatKillPacket>
    {
    public:
#if PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x35;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x35;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x33;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x36;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x34;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Player Combat Kill";

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
            player_id = ReadData<VarInt>(iter, length);
            killer_id = ReadData<int>(iter, length);
            message = ReadData<Chat>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(player_id, container);
            WriteData<int>(killer_id, container);
            WriteData<Chat>(message, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["player_id"] = player_id;
            output["killer_id"] = killer_id;
            output["message"] = message.Serialize();

            return output;
        }

    private:
        int player_id;
        int killer_id;
        Chat message;

    };
} //ProtocolCraft
#endif

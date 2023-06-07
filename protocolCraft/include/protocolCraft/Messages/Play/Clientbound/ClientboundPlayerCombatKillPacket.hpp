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
#elif PROTOCOL_VERSION == 762 // 1.19.4
        static constexpr int packet_id = 0x38;
#elif PROTOCOL_VERSION == 763 // 1.20
        static constexpr int packet_id = 0x38;
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

#if PROTOCOL_VERSION < 763
        void SetKillerId(const int killer_id_)
        {
            killer_id = killer_id_;
        }
#endif

        void SetMessage(const Chat& message_)
        {
            message = message_;
        }



        int GetPlayerId() const
        {
            return player_id;
        }

#if PROTOCOL_VERSION < 763
        int GetKillerId() const
        {
            return killer_id;
        }
#endif

        const Chat& GetMessage() const
        {
            return message;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            player_id = ReadData<VarInt>(iter, length);
#if PROTOCOL_VERSION < 763
            killer_id = ReadData<int>(iter, length);
#endif
            message = ReadData<Chat>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(player_id, container);
#if PROTOCOL_VERSION < 763
            WriteData<int>(killer_id, container);
#endif
            WriteData<Chat>(message, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["player_id"] = player_id;
#if PROTOCOL_VERSION < 763
            output["killer_id"] = killer_id;
#endif
            output["message"] = message;

            return output;
        }

    private:
        int player_id;
#if PROTOCOL_VERSION < 763
        int killer_id;
#endif
        Chat message;

    };
} //ProtocolCraft
#endif

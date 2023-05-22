#pragma once

#if PROTOCOL_VERSION > 754
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundPlayerCombatEnterPacket : public BaseMessage<ClientboundPlayerCombatEnterPacket>
    {
    public:
#if PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x34;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x34;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x32;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x35;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x33;
#elif PROTOCOL_VERSION == 762 // 1.19.4
        static constexpr int packet_id = 0x37;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Player Combat Enter";

        virtual ~ClientboundPlayerCombatEnterPacket() override
        {

        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {

        }

        virtual void WriteImpl(WriteContainer& container) const override
        {

        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;


            return output;
        }

    private:
    };
} //ProtocolCraft
#endif

#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Identifier.hpp"

#include <vector>

namespace ProtocolCraft
{
    class ClientboundStoreCookieConfigurationPacket : public BaseMessage<ClientboundStoreCookieConfigurationPacket>
    {
    public:
        static constexpr int packet_id = 0x0A;
        static constexpr std::string_view packet_name = "Store Cookie (Configuration)";

        DECLARE_FIELDS(
            (Identifier, std::vector<unsigned char>),
            (Key,        Payload)
        );
        DECLARE_SERIALIZE;

        GETTER_SETTER(Key);
        GETTER_SETTER(Payload);

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            SetKey(ReadData<Identifier>(iter, length));
            SetPayload(ReadByteArray(iter, length, length));
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<Identifier>(GetKey(), container);
            WriteByteArray(GetPayload(), container);
        }
    };
}
#endif

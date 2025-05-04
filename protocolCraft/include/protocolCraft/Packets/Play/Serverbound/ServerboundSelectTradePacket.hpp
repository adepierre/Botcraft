#if PROTOCOL_VERSION > 385 /* > 1.12.2 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ServerboundSelectTradePacket : public BasePacket<ServerboundSelectTradePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Select Trade";

        SERIALIZED_FIELD(Item, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif

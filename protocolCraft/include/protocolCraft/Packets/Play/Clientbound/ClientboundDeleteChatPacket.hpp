#if PROTOCOL_VERSION > 759 /* > 1.19 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
#include "protocolCraft/Types/Holder.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundDeleteChatPacket : public BasePacket<ClientboundDeleteChatPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Delete Chat";

#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        SERIALIZED_FIELD(MessageSignature, std::vector<unsigned char>);
#else
        SERIALIZED_FIELD(MessageSignature, Holder<std::array<unsigned char, 256>>);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif

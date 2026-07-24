#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include <array>
#include <string>
#include <vector>

#include "protocolCraft/BasePacket.hpp"

#include "protocolCraft/Types/Chat/LastSeenMessagesUpdate.hpp"

namespace ProtocolCraft
{
    class ServerboundChatCommandSignedPacket : public BasePacket<ServerboundChatCommandSignedPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Chat Command Signed";

        SERIALIZED_FIELD(Command, std::string);
        SERIALIZED_FIELD(Timestamp, long long int);
        SERIALIZED_FIELD(Salt, long long int);
        SERIALIZED_FIELD(ArgumentSignatures, std::vector<std::pair<std::string, std::array<unsigned char, 256>>>);
        SERIALIZED_FIELD(LastSeenMessages, LastSeenMessagesUpdate);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif

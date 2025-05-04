#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#pragma once

#include <string>
#include <map>
#include <vector>

#include "protocolCraft/BasePacket.hpp"

#if PROTOCOL_VERSION > 759 /* > 1.19 */
#include "protocolCraft/Types/Chat/LastSeenMessagesUpdate.hpp"
#endif

namespace ProtocolCraft
{
    class ServerboundChatCommandPacket : public BasePacket<ServerboundChatCommandPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Chat Command";

#if PROTOCOL_VERSION < 760 /* < 1.19.1 */
        SERIALIZED_FIELD(Command, std::string);
        SERIALIZED_FIELD(Timestamp, long long int);
        SERIALIZED_FIELD(ArgumentSignatures, std::map<std::string, std::vector<unsigned char>>);
        SERIALIZED_FIELD(SignedPreview, bool);
#elif PROTOCOL_VERSION < 761 /* < 1.19.3 */
        SERIALIZED_FIELD(Command, std::string);
        SERIALIZED_FIELD(Timestamp, long long int);
        SERIALIZED_FIELD(Salt, long long int);
        SERIALIZED_FIELD(ArgumentSignatures, std::map<std::string, std::vector<unsigned char>>);
        SERIALIZED_FIELD(SignedPreview, bool);
        SERIALIZED_FIELD(LastSeenMessages, LastSeenMessagesUpdate);
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
        SERIALIZED_FIELD(Command, std::string);
        SERIALIZED_FIELD(Timestamp, long long int);
        SERIALIZED_FIELD(Salt, long long int);
        SERIALIZED_FIELD(ArgumentSignatures, std::map<std::string, std::vector<unsigned char>>);
        SERIALIZED_FIELD(LastSeenMessages, LastSeenMessagesUpdate);
#else
        SERIALIZED_FIELD(Command, std::string);
#endif
        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif

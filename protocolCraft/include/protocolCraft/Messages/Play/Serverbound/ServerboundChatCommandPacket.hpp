#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#pragma once

#include <string>
#include <map>
#include <vector>

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION > 759 /* > 1.19 */
#include "protocolCraft/Types/Chat/LastSeenMessagesUpdate.hpp"
#endif

namespace ProtocolCraft
{
    class ServerboundChatCommandPacket : public BaseMessage<ServerboundChatCommandPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Chat Command";

#if PROTOCOL_VERSION < 760 /* < 1.19.1 */
        DECLARE_FIELDS(
            (std::string, long long int, std::map<std::string, std::vector<unsigned char>>, bool),
            (Command,     Timestamp,     ArgumentSignatures,                                SignedPreview)
        );
#elif PROTOCOL_VERSION < 761 /* < 1.19.3 */
        DECLARE_FIELDS(
            (std::string, long long int, long long int, std::map<std::string, std::vector<unsigned char>>, bool,          LastSeenMessagesUpdate),
            (Command,     Timestamp,     Salt,          ArgumentSignatures,                                SignedPreview, LastSeenMessages)
        );
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
        DECLARE_FIELDS(
            (std::string, long long int, long long int, std::map<std::string, std::vector<unsigned char>>, LastSeenMessagesUpdate),
            (Command,     Timestamp,     Salt,          ArgumentSignatures,                                LastSeenMessages)
        );
#else
        DECLARE_FIELDS(
            (std::string),
            (Command)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Command);
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        GETTER_SETTER(Timestamp);
        GETTER_SETTER(ArgumentSignatures);
#endif
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        GETTER_SETTER(SignedPreview);
#endif
#if PROTOCOL_VERSION > 759 /* > 1.19 */ && PROTOCOL_VERSION < 766 /* < 1.20.5 */
        GETTER_SETTER(Salt);
        GETTER_SETTER(LastSeenMessages);
#endif
    };
} //ProtocolCraft
#endif

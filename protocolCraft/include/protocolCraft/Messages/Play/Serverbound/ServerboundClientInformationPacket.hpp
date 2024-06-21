#pragma once

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/Types/ClientInformation.hpp"
#endif


namespace ProtocolCraft
{
    class ServerboundClientInformationPacket : public BaseMessage<ServerboundClientInformationPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Client Information";

#if PROTOCOL_VERSION < 755 /* < 1.17 */
        DECLARE_FIELDS(
            (std::string, char,         VarInt,         bool,       unsigned char,      VarInt),
            (Language,    ViewDistance, ChatVisibility, ChatColors, ModelCustomisation, MainHand)
        );
#elif PROTOCOL_VERSION < 757 /* < 1.18 */
        DECLARE_FIELDS(
            (std::string, char,         VarInt,         bool,       unsigned char,      VarInt,   bool),
            (Language,    ViewDistance, ChatVisibility, ChatColors, ModelCustomisation, MainHand, TextFilteringEnabled)
        );
#elif PROTOCOL_VERSION < 764 /* < 1.20.2 */
        DECLARE_FIELDS(
            (std::string, char,         VarInt,         bool,       unsigned char,      VarInt,   bool,                 bool),
            (Language,    ViewDistance, ChatVisibility, ChatColors, ModelCustomisation, MainHand, TextFilteringEnabled, AllowListing)
        );
#else
        DECLARE_FIELDS(
            (ClientInformation),
            (ClientInformation)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        GETTER_SETTER(Language);
        GETTER_SETTER(ViewDistance);
        GETTER_SETTER(ChatVisibility);
        GETTER_SETTER(ChatColors);
        GETTER_SETTER(ModelCustomisation);
        GETTER_SETTER(MainHand);
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
        GETTER_SETTER(TextFilteringEnabled);
#endif
#if PROTOCOL_VERSION > 756 /* > 1.17.1 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
        GETTER_SETTER(AllowListing);
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
        GETTER_SETTER(ClientInformation);
#endif
    };
} //ProtocolCraft

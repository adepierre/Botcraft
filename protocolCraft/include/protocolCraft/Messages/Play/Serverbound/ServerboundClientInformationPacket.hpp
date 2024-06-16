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
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */ || PROTOCOL_VERSION == 393 /* 1.13 */ ||  \
      PROTOCOL_VERSION == 401 /* 1.13.1 */ || PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x04;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */ || PROTOCOL_VERSION == 573 /* 1.15 */ ||  \
      PROTOCOL_VERSION == 575 /* 1.15.1 */ || PROTOCOL_VERSION == 578 /* 1.15.2 */ ||  \
      PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */ ||  \
      PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */ || PROTOCOL_VERSION == 755 /* 1.17 */ ||  \
      PROTOCOL_VERSION == 756 /* 1.17.1 */ || PROTOCOL_VERSION == 757 /* 1.18/.1 */ ||  \
      PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x05;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x07;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x08;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x07;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x08;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x09;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x0A;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Client Information";

#if PROTOCOL_VERSION < 755 /* < 1.17 */
        DECLARE_FIELDS_TYPES(std::string, char,         VarInt,         bool,       unsigned char,      VarInt);
        DECLARE_FIELDS_NAMES(Language,    ViewDistance, ChatVisibility, ChatColors, ModelCustomisation, MainHand);
#elif PROTOCOL_VERSION < 757 /* < 1.18 */
        DECLARE_FIELDS_TYPES(std::string, char,         VarInt,         bool,       unsigned char,      VarInt,   bool);
        DECLARE_FIELDS_NAMES(Language,    ViewDistance, ChatVisibility, ChatColors, ModelCustomisation, MainHand, TextFilteringEnabled);
#elif PROTOCOL_VERSION < 764 /* < 1.20.2 */
        DECLARE_FIELDS_TYPES(std::string, char,         VarInt,         bool,       unsigned char,      VarInt,   bool,                 bool);
        DECLARE_FIELDS_NAMES(Language,    ViewDistance, ChatVisibility, ChatColors, ModelCustomisation, MainHand, TextFilteringEnabled, AllowListing);
#else
        DECLARE_FIELDS_TYPES(ClientInformation);
        DECLARE_FIELDS_NAMES(ClientInformation);
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

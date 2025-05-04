#pragma once

#include "protocolCraft/BasePacket.hpp"

#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/Types/ClientInformation.hpp"
#endif


namespace ProtocolCraft
{
    class ServerboundClientInformationPacket : public BasePacket<ServerboundClientInformationPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Client Information";


#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        SERIALIZED_FIELD(Language, std::string);
        SERIALIZED_FIELD(ViewDistance, char);
        SERIALIZED_FIELD(ChatVisibility, VarInt);
        SERIALIZED_FIELD(ChatColors, bool);
        SERIALIZED_FIELD(ModelCustomisation, unsigned char);
        SERIALIZED_FIELD(MainHand, VarInt);
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
        SERIALIZED_FIELD(TextFilteringEnabled, bool);
#endif
#if PROTOCOL_VERSION > 756 /* > 1.17.1 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
        SERIALIZED_FIELD(AllowListing, bool);
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
        SERIALIZED_FIELD(ClientInformation, ProtocolCraft::ClientInformation);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft

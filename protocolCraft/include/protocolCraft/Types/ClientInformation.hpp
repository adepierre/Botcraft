#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class ClientInformation : public NetworkType
    {
        SERIALIZED_FIELD(Language, std::string);
        SERIALIZED_FIELD(ViewDistance, char);
        SERIALIZED_FIELD(ChatVisibility, VarInt);
        SERIALIZED_FIELD(ChatColors, bool);
        SERIALIZED_FIELD(ModelCustomisation, unsigned char);
        SERIALIZED_FIELD(MainHand, VarInt);
        SERIALIZED_FIELD(TestFilteringEnabled, bool);
        SERIALIZED_FIELD(AllowsListing, bool);
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        SERIALIZED_FIELD(ParticleStatus, VarInt);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif

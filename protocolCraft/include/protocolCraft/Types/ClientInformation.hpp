#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class ClientInformation : public NetworkType
    {
        DECLARE_FIELDS(
            (std::string, char,         VarInt,         bool,       unsigned char,      VarInt,   bool,                 bool),
            (Language,    ViewDistance, ChatVisibility, ChatColors, ModelCustomisation, MainHand, TestFilteringEnabled, AllowsListing)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Language);
        GETTER_SETTER(ViewDistance);
        GETTER_SETTER(ChatVisibility);
        GETTER_SETTER(ChatColors);
        GETTER_SETTER(ModelCustomisation);
        GETTER_SETTER(MainHand);
        GETTER_SETTER(TestFilteringEnabled);
        GETTER_SETTER(AllowsListing);
    };
}
#endif

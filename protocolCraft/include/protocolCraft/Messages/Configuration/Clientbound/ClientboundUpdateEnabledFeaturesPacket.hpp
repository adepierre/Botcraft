#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

#include <vector>
#include <string>

namespace ProtocolCraft
{
    class ClientboundUpdateEnabledFeaturesPacket : public BaseMessage<ClientboundUpdateEnabledFeaturesPacket>
    {
    public:
#if   PROTOCOL_VERSION < 765 /* < 1.20.3 */
        static constexpr int packet_id = 0x07;
#elif PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x08;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x0C;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Update Enabled Features";

        DECLARE_FIELDS(
            (std::vector<std::string>),
            (Features)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Features);
    };
} //ProtocolCraft
#endif

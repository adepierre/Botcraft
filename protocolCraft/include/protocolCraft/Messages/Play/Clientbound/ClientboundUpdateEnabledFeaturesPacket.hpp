#if PROTOCOL_VERSION > 760 /* > 1.19.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Identifier.hpp"

#include <vector>

namespace ProtocolCraft
{
    class ClientboundUpdateEnabledFeaturesPacket : public BaseMessage<ClientboundUpdateEnabledFeaturesPacket>
    {
    public:
#if   PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x67;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x6B;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Update Enabled Features";

        DECLARE_FIELDS(
            (std::vector<Identifier>),
            (Features)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Features);
    };
} //ProtocolCraft
#endif

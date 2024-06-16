#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/BlockEntityTag.hpp"

namespace ProtocolCraft
{
    class ClientboundUpdateTagsConfigurationPacket : public BaseMessage<ClientboundUpdateTagsConfigurationPacket>
    {
    public:
#if   PROTOCOL_VERSION < 765 /* < 1.20.3 */
        static constexpr int packet_id = 0x08;
#elif PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x09;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x0D;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Update Tags (Configuration)";

        DECLARE_FIELDS_TYPES(std::map<Identifier, std::vector<BlockEntityTag>>);
        DECLARE_FIELDS_NAMES(Tags);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Tags);
    };
} //ProtocolCraft
#endif

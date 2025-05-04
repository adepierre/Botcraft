#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/BlockEntityTag.hpp"

namespace ProtocolCraft
{
    class ClientboundUpdateTagsConfigurationPacket : public BasePacket<ClientboundUpdateTagsConfigurationPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Update Tags (Configuration)";

        SERIALIZED_FIELD(Tags, std::map<Identifier, std::vector<BlockEntityTag>>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif

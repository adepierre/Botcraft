#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/BlockEntityTag.hpp"

namespace ProtocolCraft
{
    class ClientboundUpdateTagsConfigurationPacket : public BaseMessage<ClientboundUpdateTagsConfigurationPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Update Tags (Configuration)";

        DECLARE_FIELDS(
            (std::map<Identifier, std::vector<BlockEntityTag>>),
            (Tags)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Tags);
    };
} //ProtocolCraft
#endif

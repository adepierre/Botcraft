#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSelectAdvancementsTabPacket : public BaseMessage<ClientboundSelectAdvancementsTabPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Select Advancement Tab";

        DECLARE_FIELDS(
            (std::optional<std::string>),
            (Tab)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Tab);
    };
} //ProtocolCraft

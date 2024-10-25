#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSelectAdvancementsTabPacket : public BaseMessage<ClientboundSelectAdvancementsTabPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Select Advancement Tab";

        SERIALIZED_FIELD(Tab, std::optional<std::string>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft

#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

#include "protocolCraft/Types/NBT/NBT.hpp"

namespace ProtocolCraft
{
    class ClientboundShowDialogConfigurationPacket : public BasePacket<ClientboundShowDialogConfigurationPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Show Dialog (Configuration)";

        SERIALIZED_FIELD(Dialog, NBT::UnnamedValue);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif

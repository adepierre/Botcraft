#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

#include "protocolCraft/Types/Holder.hpp"
#include "protocolCraft/Types/NBT/NBT.hpp"

namespace ProtocolCraft
{
    class ClientboundShowDialogPacket : public BasePacket<ClientboundShowDialogPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Show Dialog";

        SERIALIZED_FIELD(Dialog, Internal::DiffType<Holder<NBT::Value>, Holder<NBT::UnnamedValue>>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif

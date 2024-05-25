#pragma once

#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/NBT/NBT.hpp"

namespace ProtocolCraft
{
    class BlockEntityInfo : public NetworkType
    {
        DECLARE_FIELDS_TYPES(unsigned char, short, VarInt, NBT::UnnamedValue);
        DECLARE_FIELDS_NAMES(PackedXZ,      Y,     Type,   Tag);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(PackedXZ);
        GETTER_SETTER(Y);
        GETTER_SETTER(Type);
        GETTER_SETTER(Tag);
    };
} // ProtocolCraft
#endif

#pragma once

#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/NBT/NBT.hpp"

namespace ProtocolCraft
{
    class BlockEntityInfo : public NetworkType
    {
        SERIALIZED_FIELD(PackedXZ, unsigned char);
        SERIALIZED_FIELD(Y, short);
        SERIALIZED_FIELD(Type, VarInt);
        SERIALIZED_FIELD(Tag, NBT::UnnamedValue);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
#endif

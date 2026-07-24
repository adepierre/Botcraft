#if PROTOCOL_VERSION > 766 /* > 1.20.5 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/NBT/NBT.hpp"

#include <string>
#include <vector>

namespace ProtocolCraft
{
    class ChatTypeDecoration : public NetworkType
    {
        SERIALIZED_FIELD(TranslationKey, std::string);
        SERIALIZED_FIELD(Parameters, std::vector<VarInt>);
        SERIALIZED_FIELD(Style, NBT::UnnamedValue);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif

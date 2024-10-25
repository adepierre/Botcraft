#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/HolderSet.hpp"

#include <optional>

namespace ProtocolCraft
{
    namespace Components
    {
        class ToolRule : public NetworkType
        {
            SERIALIZED_FIELD(Blocks, HolderSet);
            SERIALIZED_FIELD(Speed, std::optional<float>);
            SERIALIZED_FIELD(CorrectForDrop, std::optional<bool>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif

#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/HolderSet.hpp"

#include <optional>
#include <vector>

namespace ProtocolCraft
{
    namespace Components
    {
        class ToolRule : public NetworkType
        {
            DECLARE_FIELDS(
                (HolderSet, std::optional<float>, std::optional<bool>),
                (Blocks,    Speed,                CorrectForDrop)
            );
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(Blocks);
            GETTER_SETTER(Speed);
            GETTER_SETTER(CorrectForDrop);
        };
    }
}
#endif

#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"

#if PROTOCOL_VERSION < 777 /* < 26.3 */
#include <vector>
#else
#include "protocolCraft/Types/Item/Slot.hpp"
#include <optional>
#endif

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypePotDecorations : public DataComponentType
        {
#if PROTOCOL_VERSION < 777 /* < 26.3 */
            SERIALIZED_FIELD(Sides, std::vector<VarInt>);
#else
            SERIALIZED_FIELD(Back, std::optional<Slot>);
            SERIALIZED_FIELD(Left, std::optional<Slot>);
            SERIALIZED_FIELD(Right, std::optional<Slot>);
            SERIALIZED_FIELD(Front, std::optional<Slot>);
#endif

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif

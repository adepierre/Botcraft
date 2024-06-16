#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeHolderInstrument : public DataComponentType
        {
            DECLARE_FIELDS(
                (VarInt),
                (InstrumentId)
            );
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(InstrumentId);
        };
    }
}
#endif

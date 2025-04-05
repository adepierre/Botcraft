#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Holder.hpp"
#include "protocolCraft/Types/Sound/SoundEvent.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeBreakSound : public DataComponentType
        {
            SERIALIZED_FIELD(SoundEvent, Holder<ProtocolCraft::SoundEvent>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif

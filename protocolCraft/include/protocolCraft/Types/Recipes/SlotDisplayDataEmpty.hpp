#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/Types/Recipes/SlotDisplayData.hpp"

namespace ProtocolCraft
{
    class SlotDisplayDataEmpty : public SlotDisplayData
    {
        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif

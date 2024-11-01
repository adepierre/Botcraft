#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/Types/Recipes/SlotDisplayData.hpp"
#include "protocolCraft/Types/Recipes/SlotDisplay.hpp"

#include <vector>

namespace ProtocolCraft
{
    class CompositeSlotDisplay : public SlotDisplayData
    {
        SERIALIZED_FIELD(Contents, std::vector<SlotDisplay>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif

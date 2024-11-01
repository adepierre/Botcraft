#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Recipes/SlotDisplay.hpp"

namespace ProtocolCraft
{
    class SelectableRecipe : public NetworkType
    {
        SERIALIZED_FIELD(OptionDisplay, SlotDisplay);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif

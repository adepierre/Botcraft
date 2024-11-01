#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/Types/Recipes/RecipeDisplayData.hpp"
#include "protocolCraft/Types/Recipes/SlotDisplay.hpp"

namespace ProtocolCraft
{
    class StonecutterRecipeDisplay : public RecipeDisplayData
    {
        SERIALIZED_FIELD(Input, SlotDisplay);
        SERIALIZED_FIELD(Result, SlotDisplay);
        SERIALIZED_FIELD(CraftingStation, SlotDisplay);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif

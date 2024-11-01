#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/Types/Recipes/RecipeDisplayData.hpp"
#include "protocolCraft/Types/Recipes/SlotDisplay.hpp"

namespace ProtocolCraft
{
    class SmithingRecipeDisplay : public RecipeDisplayData
    {
        SERIALIZED_FIELD(Template, SlotDisplay);
        SERIALIZED_FIELD(Base, SlotDisplay);
        SERIALIZED_FIELD(Addition, SlotDisplay);
        SERIALIZED_FIELD(Result, SlotDisplay);
        SERIALIZED_FIELD(CraftingStation, SlotDisplay);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif

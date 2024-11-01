#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/Types/Recipes/RecipeDisplayData.hpp"
#include "protocolCraft/Types/Recipes/SlotDisplay.hpp"

#include <vector>

namespace ProtocolCraft
{
    class ShapedCraftingRecipeDisplay : public RecipeDisplayData
    {
        SERIALIZED_FIELD(Width, VarInt);
        SERIALIZED_FIELD(Height, VarInt);
        SERIALIZED_FIELD(Ingredients, std::vector<SlotDisplay>);
        SERIALIZED_FIELD(Result, SlotDisplay);
        SERIALIZED_FIELD(CraftingStation, SlotDisplay);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif

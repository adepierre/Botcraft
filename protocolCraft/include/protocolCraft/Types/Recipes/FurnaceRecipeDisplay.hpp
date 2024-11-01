#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/Types/Recipes/RecipeDisplayData.hpp"
#include "protocolCraft/Types/Recipes/SlotDisplay.hpp"

namespace ProtocolCraft
{
    class FurnaceRecipeDisplay : public RecipeDisplayData
    {
        SERIALIZED_FIELD(Ingredient, SlotDisplay);
        SERIALIZED_FIELD(Fuel, SlotDisplay);
        SERIALIZED_FIELD(Result, SlotDisplay);
        SERIALIZED_FIELD(CraftingStation, SlotDisplay);
        SERIALIZED_FIELD(Duration, VarInt);
        SERIALIZED_FIELD(Experience, float);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif

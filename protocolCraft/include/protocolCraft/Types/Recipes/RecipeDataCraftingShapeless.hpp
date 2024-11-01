#if PROTOCOL_VERSION > 347 /* > 1.12.2 */ && PROTOCOL_VERSION < 768 /* < 1.21.2 */
#pragma once

#include "protocolCraft/Types/Recipes/RecipeData.hpp"
#include "protocolCraft/Types/Recipes/Ingredient.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"

namespace ProtocolCraft
{
    class RecipeDataCraftingShapeless : public RecipeData
    {
        SERIALIZED_FIELD(Group, std::string);
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
        SERIALIZED_FIELD(CookingBookCategory, VarInt);
#endif
        SERIALIZED_FIELD(Ingredients, std::vector<Ingredient>);
        SERIALIZED_FIELD(Result, Slot);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif

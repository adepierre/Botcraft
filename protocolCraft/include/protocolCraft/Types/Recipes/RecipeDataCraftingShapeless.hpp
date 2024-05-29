#pragma once
#if PROTOCOL_VERSION > 347 /* > 1.12.2 */

#include "protocolCraft/Types/Recipes/RecipeData.hpp"
#include "protocolCraft/Types/Recipes/Ingredient.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"

namespace ProtocolCraft
{
    class RecipeDataCraftingShapeless : public RecipeData
    {
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        DECLARE_FIELDS_TYPES(std::string, std::vector<Ingredient>, Slot);
        DECLARE_FIELDS_NAMES(Group,       Ingredients,             Result);
#else
        DECLARE_FIELDS_TYPES(std::string, VarInt,              std::vector<Ingredient>, Slot);
        DECLARE_FIELDS_NAMES(Group,       CookingBookCategory, Ingredients,             Result);
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Group);
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
        GETTER_SETTER(CookingBookCategory);
#endif
        GETTER_SETTER(Ingredients);
        GETTER_SETTER(Result);
    };
}
#endif

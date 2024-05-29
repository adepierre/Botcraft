#if PROTOCOL_VERSION > 732 /* > 1.15.2 */ && PROTOCOL_VERSION < 763 /* < 1.20 */
#pragma once

#include "protocolCraft/Types/Recipes/RecipeData.hpp"
#include "protocolCraft/Types/Recipes/Ingredient.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"

namespace ProtocolCraft
{
    class RecipeDataSmithing : public RecipeData
    {
        DECLARE_FIELDS_TYPES(Ingredient, Ingredient, Slot);
        DECLARE_FIELDS_NAMES(Base,       Ingredient, Result);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Base);
        GETTER_SETTER(Ingredient);
        GETTER_SETTER(Result);
    };
}
#endif

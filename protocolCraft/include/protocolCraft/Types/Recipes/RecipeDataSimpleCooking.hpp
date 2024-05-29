#if PROTOCOL_VERSION > 347 /* > 1.12.2 */
#pragma once

#include "protocolCraft/Types/Recipes/RecipeData.hpp"
#include "protocolCraft/Types/Recipes/Ingredient.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"

namespace ProtocolCraft
{
    class RecipeDataSimpleCooking : public RecipeData
    {
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        DECLARE_FIELDS_TYPES(std::string, Ingredient, Slot,   float,      VarInt);
        DECLARE_FIELDS_NAMES(Group,       Ingredient, Result, Experience, CookingTime);
#else
        DECLARE_FIELDS_TYPES(std::string, VarInt,              Ingredient, Slot,   float,      VarInt);
        DECLARE_FIELDS_NAMES(Group,       CookingBookCategory, Ingredient, Result, Experience, CookingTime);
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Group);
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
        GETTER_SETTER(CookingBookCategory);
#endif
        GETTER_SETTER(Ingredient);
        GETTER_SETTER(Result);
        GETTER_SETTER(Experience);
        GETTER_SETTER(CookingTime);
    };
}
#endif

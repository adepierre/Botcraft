#if PROTOCOL_VERSION > 347 /* > 1.12.2 */ && PROTOCOL_VERSION < 768 /* < 1.21.2 */
#pragma once

#include "protocolCraft/Types/Recipes/RecipeData.hpp"
#include "protocolCraft/Types/Recipes/Ingredient.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"

namespace ProtocolCraft
{
    class RecipeDataSimpleCooking : public RecipeData
    {
        SERIALIZED_FIELD(Group, std::string);
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
        SERIALIZED_FIELD(CookingBookCategory, VarInt);
#endif
        SERIALIZED_FIELD(Ingredient, ProtocolCraft::Ingredient);
        SERIALIZED_FIELD(Result, Slot);
        SERIALIZED_FIELD(Experience, float);
        SERIALIZED_FIELD(CookingTime, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif

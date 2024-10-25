#if PROTOCOL_VERSION > 732 /* > 1.15.2 */ && PROTOCOL_VERSION < 763 /* < 1.20 */
#pragma once

#include "protocolCraft/Types/Recipes/RecipeData.hpp"
#include "protocolCraft/Types/Recipes/Ingredient.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"

namespace ProtocolCraft
{
    class RecipeDataSmithing : public RecipeData
    {
        SERIALIZED_FIELD(Base, ProtocolCraft::Ingredient);
        SERIALIZED_FIELD(Ingredient, ProtocolCraft::Ingredient);
        SERIALIZED_FIELD(Result, Slot);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
